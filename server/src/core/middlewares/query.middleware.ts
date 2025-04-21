import { Injectable, NestMiddleware, Logger } from '@nestjs/common';
import { Request, Response, NextFunction } from 'express';

@Injectable()
export class QueryMiddleware implements NestMiddleware {
  private readonly logger = new Logger();

  use(req: Request, res: Response, next: NextFunction) {
    if (req.query.error) {
      this.logger.error(`Query error: ${req.query.error}`, req.ip);
      return res.redirect('/');
    }

    this.logger.log(`${req.method} ${req.path}`, req.ip);
    next();
  }
}