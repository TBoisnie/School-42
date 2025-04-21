import { Injectable, NestMiddleware } from '@nestjs/common';
import * as express from 'express';

@Injectable()
export class JsonMiddleware implements NestMiddleware {
    use(req: express.Request, res: express.Response, next: express.NextFunction) {
        express.json()(req, res, next);
    }
}
