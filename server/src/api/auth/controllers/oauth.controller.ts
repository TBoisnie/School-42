import { Controller, Get, Post, Body, Res, UseGuards, Logger, HttpCode } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { CookieOptions, Response } from 'express';
import { ConfigService } from '@nestjs/config';
import { GetCookiePayload } from '../../../core/decorators/get-cookie-playload.decorator.js';
import { GetIp } from '../../../core/decorators/get-ip.decorator.js';
import { CookiePayload as CookiePayload } from '../types/token-payload.type.js';

@Controller('oauth')
export class OAuthController {
  private cookieOptions: CookieOptions;
  private readonly logger = new Logger();

  constructor(
    private readonly configService: ConfigService
  ) {
    this.cookieOptions = {
      httpOnly: this.configService.get<string>('COOKIE_HTTP_ONLY') === 'true',
      secure: this.configService.get<string>('COOKIE_SECURE') === 'true',
      sameSite: this.configService.get<string>('COOKIE_SAME_SITE') as CookieOptions['sameSite'],
      maxAge: Number(this.configService.get<string>('COOKIE_MAX_AGE')),
      signed: this.configService.get<string>('COOKIE_SIGNED') === 'true',
    };
  }

  @Post('/token')
  async token(
    @Body() body: { client_id: string, client_secret: string }
  ) {
    // I guess they want us to implement an endpoint that takes a 
    // API key and secret that returns a auth token
    // to be used as "admin" for full access to the API
  }

  @Get('42/authorize')
  @HttpCode(302)
  @UseGuards(AuthGuard('42'))
  async fortyTwoAuthorize(
    @GetIp() ip: string,
  ) {
    this.logger.log('Redirecting to 42 for authentication', ip);
  }

  @Get('42/callback')
  @HttpCode(200)
  @UseGuards(AuthGuard('42'))
  async fortyTwoCallback(
    @GetCookiePayload() cookie: CookiePayload,
    @Res({ passthrough: true }) res: Response,
    @GetIp() ip: string
  ) {
    res.cookie('auth', cookie, this.cookieOptions);
    res.cookie('login', true);
    this.logger.log('Has authenticated with 42', ip);
  }

  @Get('google/authorize')
  @HttpCode(302)
  @UseGuards(AuthGuard('google'))
  async googleAuthorize(
    @GetIp() ip: string,
  ) {
    this.logger.log('Redirecting to Google for authentication', ip);
  }

  @Get('google/callback')
  @HttpCode(200)
  @UseGuards(AuthGuard('google'))
  async googleCallback(
    @GetCookiePayload() cookie: CookiePayload,
    @Res({ passthrough: true }) res: Response,
    @GetIp() ip: string
  ) {
    res.cookie('auth', cookie, this.cookieOptions);
    res.cookie('login', true);
    this.logger.log('Has authenticated with Google', ip);
  }

  @Get('github/authorize')
  @HttpCode(302)
  @UseGuards(AuthGuard('github'))
  async githubAuthorize(
    @GetIp() ip: string,
  ) {
    this.logger.log('Redirecting to Github for authentication', ip);
  }

  @Get('github/callback')
  @HttpCode(200)
  @UseGuards(AuthGuard('github'))
  async githubCallback(
    @GetCookiePayload() cookie: CookiePayload,
    @Res({ passthrough: true }) res: Response,
    @GetIp() ip: string
  ) {
    res.cookie('auth', cookie, this.cookieOptions);
    res.cookie('login', true);
    this.logger.log('Has authenticated with Github', ip);
  }
}