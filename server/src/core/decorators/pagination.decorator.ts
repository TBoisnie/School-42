import { createParamDecorator, ExecutionContext } from '@nestjs/common';
import { Request } from 'express';
import { clamp } from '../utilities/math/clamp.utility.js';
import { toSafeInt } from '../utilities/string/to-safe-int.utility.js';

export type Page =
{
	index: number;
	size: number;
};

export const Pagination = createParamDecorator((
	_: unknown,
	ctx: ExecutionContext
)
	: Page =>
{
	const INDEX = { MIN: 1, MAX: Number.MAX_SAFE_INTEGER, DEFAULT: 1 } as const;
	const SIZE  = { MIN: 10, MAX: 50, DEFAULT: 10 } as const;

	const query = ( ctx.switchToHttp().getRequest() as Request ).query;

	return {
		index: clamp( toSafeInt( ( query[ 'page' ]  ?? '' ).toString(), INDEX.DEFAULT ), INDEX.MIN, INDEX.MAX ),
		size:  clamp( toSafeInt( ( query[ 'limit' ] ?? '' ).toString(),  SIZE.DEFAULT ),  SIZE.MIN,  SIZE.MAX ),
	};
})
