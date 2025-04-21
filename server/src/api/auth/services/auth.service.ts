import { Injectable, HttpException, HttpStatus } from '@nestjs/common';
import bcrypt from 'bcrypt';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { ConfigService } from '@nestjs/config';
import nodemailer from 'nodemailer';
import { Users } from '../../users/entities/users.entity.js';

@Injectable()
export class AuthService {
    constructor(
        @InjectRepository(Users)
        private readonly usersRepository: Repository<Users>,
        private readonly configService: ConfigService,
    ) { }

    // Generate new access and refresh tokens using the user id
    async generateTokens(userId: number): Promise<{ accessToken: string, refreshToken: string }> {
        const maxAge = Number(this.configService.get<string>('COOKIE_MAX_AGE'));
        const refreshTokenExpiration = new Date().getTime() + maxAge;
        const accessTokenExpiration = new Date().getTime() + (maxAge / 100);
        return {
            refreshToken: Buffer.from(`${userId}:${new Date().getTime() + refreshTokenExpiration}`).toString('base64'),
            accessToken: Buffer.from(`${userId}:${new Date().getTime() + accessTokenExpiration}`).toString('base64')
        };
    }

    // Verify the access token using the provider
    async verifyAccesToken(accessToken: string): Promise<boolean> {

        const decoded = Buffer.from(accessToken, 'base64').toString('ascii').split(':');
        if (decoded.length !== 2) {
            return false;
        }

        const id = decoded[0];
        const user = await this.usersRepository.findOne({ where: { id: Number(id) } });
        if (!user) {
            return false;
        }

        const expiry = Number(decoded[1]);
        if (expiry < new Date().getTime()) {
            return false;
        }
        return true;
    }

    // Verify the authorization using the access and refresh tokens
    async verifyAuthorization(accessToken: string, refreshToken: string): Promise<{ accessToken: string, refreshToken: string }> {

        const isAccessTokenValid = await this.verifyAccesToken(accessToken);
        if (isAccessTokenValid) {
            return { accessToken, refreshToken };
        }
        const tokens = await this.refreshAccesToken(refreshToken);
        return tokens;
    }

    // Generate new access and refresh tokens using the refresh token
    async refreshAccesToken(refreshToken: string): Promise<{ accessToken: string, refreshToken: string }> {
        
        const decoded = Buffer.from(refreshToken, 'base64').toString('ascii').split(':');
        if (decoded.length !== 2) {
            throw new HttpException('Invalid refresh token', HttpStatus.UNAUTHORIZED);
        }

        const id = decoded[0];
        const user = await this.usersRepository.findOne({ where: { id: Number(id) } });
        if (!user) {
            throw new HttpException('Invalid refresh token', HttpStatus.UNAUTHORIZED);
        }

        const expiry = Number(decoded[1]);
        if (expiry < new Date().getTime()) {
            throw new HttpException('Refresh token expired', HttpStatus.UNAUTHORIZED);
        }
        return this.generateTokens(user.id);
    }

    // Login using email and password
    async login(email: string, password: string): Promise<{ accessToken: string; refreshToken: string, id: number }> {

        const user = await this.usersRepository.findOne({ where: { email: email } });
        if (!user) {
            throw new HttpException('Email not found', HttpStatus.NOT_FOUND);
        }

        if (!(await bcrypt.compare(password, user.password as string))) {
            throw new HttpException('Invalid password', HttpStatus.UNAUTHORIZED);
        }
        const { accessToken, refreshToken } = await this.generateTokens(user.id);
        return { accessToken, refreshToken, id: user.id };
    }

    // Reset the password using the email
    async reset(email: string): Promise<void> {

        const user = await this.usersRepository.findOne({ where: { email: email } });
        if (!user) {
            throw new HttpException('Email not found', HttpStatus.NOT_FOUND);
        }

        // Send the reset link using nodemailer and google OAuth2
        const transporter = nodemailer.createTransport({
            service: 'gmail',
            auth: {
                type: 'OAuth2',
                user: this.configService.get<string>('GMAIL_USER'),
                clientId: this.configService.get<string>('GOOGLE_CLIENT_ID'),
                clientSecret: this.configService.get<string>('GOOGLE_CLIENT_SECRET'),
                refreshToken: this.configService.get<string>('GMAIL_REFRESH_TOKEN'),
            },
        });

        const token = Buffer.from(`${email}:${new Date().getTime() + 3600000}`).toString('base64');
        await transporter.sendMail({
            from: this.configService.get<string>('GMAIL_USER'),
            to: email,
            subject: 'Password Reset',
            text: `Click the link to reset your password: https://localhost:5173/auth/confirm?token=${token}`,
        });
    }

    // Confirm the password reset using the token and the new password
    async resetConfirm(token: string, password: string): Promise<void> {

        const decoded = Buffer.from(token, 'base64').toString('utf-8').split(':');
        if (decoded.length !== 2) {
            throw new HttpException('Invalid token1', HttpStatus.UNAUTHORIZED);
        }

        const email = decoded[0];
        const user = await this.usersRepository.findOne({ where: { email: email } });
        if (!user) {
            throw new HttpException('Invalid token2', HttpStatus.UNAUTHORIZED);
        }

        const expiry = Number(decoded[1]);
        if (expiry < new Date().getTime()) {
            throw new HttpException('Token expired', HttpStatus.UNAUTHORIZED);
        }

        user.password = password;
        await this.usersRepository.save(user);
    }
}
