import { Injectable, NestMiddleware } from '@nestjs/common';
import cookieParser from 'cookie-parser';
import { Request, Response } from 'express';
import { ConfigService } from '@nestjs/config';

@Injectable()
export class CookieMiddleware implements NestMiddleware {
    private readonly configService: ConfigService;

    constructor(configService: ConfigService) {
        this.configService = configService;
    }

    use(req: Request, res: Response, next: () => void) {
        cookieParser(this.configService.get<string>('COOKIE_SECRET') as string)(req, res, next);
    }
}
