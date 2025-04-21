import { CanActivate, ExecutionContext, HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { AuthService } from '../services/auth.service.js';
import e, { CookieOptions } from 'express';
import { ConfigService } from '@nestjs/config';
import { UsersService } from '../../users/services/users.service.js';

@Injectable()
export class CookieGuard implements CanActivate {
    private readonly cookieOptions: CookieOptions;

    constructor(
        private readonly authService: AuthService,
        private readonly usersService: UsersService,
        private readonly configService: ConfigService
    ) {
        this.cookieOptions = {
            httpOnly: this.configService.get<string>('COOKIE_HTTP_ONLY') === 'true',
            secure: this.configService.get<string>('COOKIE_SECURE') === 'true',
            sameSite: this.configService.get<string>('COOKIE_SAME_SITE') as CookieOptions['sameSite'],
            maxAge: Number(this.configService.get<string>('COOKIE_MAX_AGE')),
            signed: this.configService.get<string>('COOKIE_SIGNED') === 'true',
            path: this.configService.get<string>('COOKIE_PATH') as string
        };
    }

    async canActivate(context: ExecutionContext): Promise<boolean> {
        const request = context.switchToHttp().getRequest();
        const response = context.switchToHttp().getResponse();

        const cookie = request.signedCookies['auth'];

        if (cookie) {
            try {
                const { accessToken, refreshToken } = await this.authService.verifyAuthorization(cookie.accessToken, cookie.refreshToken);
                const updatedCookie = {
                    accessToken: accessToken,
                    refreshToken: refreshToken,
                    id: cookie.id
                };
                response.cookie('auth', updatedCookie, this.cookieOptions);
                request.user = updatedCookie;

                // For an optional admin system, todo: implement
                // const user = await this.usersService.getUserById(cookie.id);
                // request.user.admin = user.admin;

                return true;
            } catch (error) {
                response.clearCookie('auth');
                response.cookie('login', false);
                throw error;
            }
        }
        response.cookie('login', false);
        throw new HttpException('Missing or invalid cookie', HttpStatus.UNAUTHORIZED);
    }
}
