import { PassportStrategy } from '@nestjs/passport';
import { OAuth2Strategy as PassportGoogleStrategy } from 'passport-google-oauth';
import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { AuthService } from '../services/auth.service.js';
import { UsersService } from '../../users/services/users.service.js';

@Injectable()
export class GoogleStrategy extends PassportStrategy(PassportGoogleStrategy) {
  constructor(
    private readonly authService: AuthService,
    private readonly usersService: UsersService,
    private readonly configService: ConfigService,
  ) {
    super({
      clientID: configService.get<string>('GOOGLE_CLIENT_ID'),
      clientSecret: configService.get<string>('GOOGLE_CLIENT_SECRET'),
      callbackURL: configService.get<string>('GOOGLE_CALLBACK_URL'),
      scope: ['email', 'profile'],
    });
  }

  authorizationParams(): { [key: string]: string; } {
    return ({
      access_type: 'offline'
    });
  };

  async validate(access_token: string, refresh_token: string, profile: any): Promise<{ accessToken: string, refreshToken: string, id: number }> {
    const userId = await this.usersService.registerByProvider(profile);
    const { accessToken, refreshToken } = await this.authService.generateTokens(userId);
    return { accessToken, refreshToken, id: userId };
  }
}
