import { Controller, Post, Res, UseGuards, Logger, HttpStatus, HttpCode } from '@nestjs/common';
import {  Response } from 'express';
import { AuthService } from '../services/auth.service.js';
import { ConfigService } from '@nestjs/config';
import { CookieGuard } from '../guards/cookie.guard.js';
import { LoginDto } from '../dtos/login.dto.js';
import { ResetDto } from '../dtos/reset.dto.js';
import { ConfirmDto } from '../dtos/confirm.dto.js';
import { ValidateBody } from '../../../core/decorators/validate-body.decorator.js';
import { ValidateCode } from '../../../core/decorators/validate-code.decorator.js';
import { GetIp } from '../../../core/decorators/get-ip.decorator.js';

interface CookieOptions {
  httpOnly: boolean;
  secure: boolean;
  sameSite: 'lax' | 'strict' | 'none' | undefined;
  maxAge: number;
  signed: boolean;
  path: string;
}

@Controller('auth')
export class AuthController {
  private cookieOptions: CookieOptions;
  private readonly logger = new Logger();

  constructor(
    private readonly authService: AuthService,
    private readonly configService: ConfigService,
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

  @Post('login')
  @HttpCode(HttpStatus.OK)
  async login(
    @ValidateBody(LoginDto) body: LoginDto,
    @Res({ passthrough: true }) res: Response,
    @GetIp() ip: string
  ): Promise<void> {
    const cookie = await this.authService.login(body.email, body.password);
    res.cookie('auth', cookie, this.cookieOptions);
    res.cookie('login', true);
    this.logger.log(`Has logged in`, ip);
  }

  @Post('logout')
  @HttpCode(HttpStatus.OK)
  @UseGuards(CookieGuard)
  async logout(
    @Res({ passthrough: true }) res: Response,
    @GetIp() ip: string
  ): Promise<void> {
    res.clearCookie('auth');
    res.cookie('login', false);
    this.logger.log(`Has logged out`, ip);
  }

  @Post('reset')
  @HttpCode(HttpStatus.OK)
  async reset(
    @ValidateBody(ResetDto) body: ResetDto,
    @GetIp() ip: string,
  ): Promise<void> {
    await this.authService.reset(body.email);
    this.logger.log(`Has asked for a password reset for ${body.email}`, ip);
  }

  @Post('confirm')
  @HttpCode(HttpStatus.OK)
  async confirm(
    @ValidateCode() code: string,
    @ValidateBody(ConfirmDto) body: ConfirmDto,
    @GetIp() ip: string,
  ): Promise<void> {
    await this.authService.resetConfirm(code, body.password);
    this.logger.log(`Has confirmed the password reset`, ip);
  }
}
