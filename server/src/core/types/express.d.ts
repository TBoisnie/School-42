import { Request } from 'express';
import { CookiePayload } from '../../api/auth/types/token-payload.type.js';

declare module 'express' {
    export interface Request {
        user?: CookiePayload;
    }
}
