// github strategy
import { PassportStrategy } from '@nestjs/passport';
import { Strategy as PassportGithubStrategy } from 'passport-github2';
import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { AuthService } from '../services/auth.service.js';
import { UsersService } from '../../users/services/users.service.js';

@Injectable()
export class GithubStrategy extends PassportStrategy(PassportGithubStrategy) {
  constructor(
    private readonly authService: AuthService,
    private readonly usersService: UsersService,
    private readonly configService: ConfigService,
  ) {
    super({
      clientID: configService.get<string>('GITHUB_CLIENT_ID'),
      clientSecret: configService.get<string>('GITHUB_CLIENT_SECRET'),
      callbackURL: configService.get<string>('GITHUB_CALLBACK_URL'),
      scope: ['user:email'],
    });
  }

  async validate(access_token: string, refresh_token: string, profile: any): Promise<{ accessToken: string; refreshToken: string; id: number }> {
    const userId = await this.usersService.registerByProvider(profile);
    const { accessToken, refreshToken } = await this.authService.generateTokens(userId);
    return { accessToken, refreshToken, id: userId };
  }
}
