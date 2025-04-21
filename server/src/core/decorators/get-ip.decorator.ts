import { createParamDecorator, ExecutionContext, HttpException, HttpStatus } from '@nestjs/common';
import { CookiePayload } from '../../api/auth/types/token-payload.type.js';

export const GetIp = createParamDecorator(
	(_: unknown, ctx: ExecutionContext): CookiePayload => {
		const request = ctx.switchToHttp().getRequest();
		const ip = request.ip;
		if (!ip) {
			throw new HttpException('IP not found in the request', HttpStatus.UNAUTHORIZED);
		}
		return ip;
	}
);
