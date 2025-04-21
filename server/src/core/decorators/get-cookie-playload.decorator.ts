import { createParamDecorator, ExecutionContext, HttpException, HttpStatus } from '@nestjs/common';
import { CookiePayload as CookiePayload } from '../../api/auth/types/token-payload.type.js';

export const GetCookiePayload = createParamDecorator(
	(_: unknown, ctx: ExecutionContext): CookiePayload => {
		const request = ctx.switchToHttp().getRequest();
		const user = request.user;
		if (!user) {
			throw new HttpException('User not found in the request', HttpStatus.UNAUTHORIZED);
		}
		return user;
	}
);
