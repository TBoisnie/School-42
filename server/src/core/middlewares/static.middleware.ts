import { Injectable, NestMiddleware } from '@nestjs/common';
import { Request, Response, NextFunction } from 'express';
import * as express from 'express';
import * as path from 'path';
import { fileURLToPath } from 'url';
import { dirname } from 'path';


// Not needed in production
@Injectable()
export class StaticMiddleware implements NestMiddleware {
    private readonly staticDistPath = path.join(dirname(fileURLToPath(import.meta.url)), '..', '..', '..', 'client', 'dist');

    use(req: Request, res: Response, next: NextFunction) {
        express.static(this.staticDistPath)(req, res, next);
    }
}
