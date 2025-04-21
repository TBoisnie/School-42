import { Injectable, NestMiddleware } from '@nestjs/common';
import * as express from 'express';

@Injectable()
export class UrlencodedMiddleware implements NestMiddleware {
    use(req: express.Request, res: express.Response, next: express.NextFunction) {
        express.urlencoded({ extended: true })(req, res, next);
    }
}
