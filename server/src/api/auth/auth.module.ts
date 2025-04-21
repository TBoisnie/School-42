import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { PassportModule } from '@nestjs/passport';
import { Users } from '../users/entities/users.entity.js';
import { AuthController } from './controllers/auth.controller.js';
import { OAuthController } from './controllers/oauth.controller.js';
import { AuthService } from './services/auth.service.js';
import { FortyTwoStrategy } from './strategies/fortytwo.strategy.js';
import { GoogleStrategy } from './strategies/google.strategy.js';
import { UsersService } from '../users/services/users.service.js';
import { CookieGuard } from './guards/cookie.guard.js';
import { GithubStrategy } from './strategies/github.strategy.js';

@Module({
    imports: [
        PassportModule.register({ session: false }),
        TypeOrmModule.forFeature([Users]),
    ],
    controllers: [
        AuthController,
        OAuthController,
    ],
    providers: [
        AuthService,
        FortyTwoStrategy,
        GoogleStrategy,
        GithubStrategy,
        UsersService,
        CookieGuard
    ],
    exports: [
        CookieGuard,
        AuthService,
        UsersService
    ]
})
export class AuthModule { }
