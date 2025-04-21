import { PassportStrategy } from '@nestjs/passport';
import PassportFortyTwoStrategy from 'passport-42';
import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { AuthService } from '../services/auth.service.js';
import { UsersService } from '../../users/services/users.service.js';

@Injectable()
export class FortyTwoStrategy extends PassportStrategy(PassportFortyTwoStrategy) {
  constructor(
    private readonly authService: AuthService,
    private readonly usersService: UsersService,
    private readonly configService: ConfigService,

  ) {
    super({
      clientID: configService.get<string>('FORTYTWO_CLIENT_ID') as string,
      clientSecret: configService.get<string>('FORTYTWO_CLIENT_SECRET') as string,
      callbackURL: configService.get<string>('FORTYTWO_CALLBACK_URL') as string,
      scope: ['public'],
    });
  }

  async validate(access_token: string, refresh_token: string, profile: any): Promise<{ accessToken: string, refreshToken: string, id: number }> {

    const userId = await this.usersService.registerByProvider(profile);
    const { accessToken, refreshToken } = await this.authService.generateTokens(userId);
    return { accessToken, refreshToken, id: userId };
  }
}
