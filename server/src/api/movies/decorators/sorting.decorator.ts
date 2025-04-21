import { createParamDecorator, ExecutionContext } from '@nestjs/common';
import { Request } from 'express';
import { isValueOf } from '../../../core/utilities/typing/is-value-of.utility.js';
import { SortedBy, Types, Orders } from '../types/sorted-by.type.js';

export { SortedBy };

export const Sorting = createParamDecorator((
	_: unknown,
	ctx: ExecutionContext
)
	: SortedBy =>
{
	const query = ( ctx.switchToHttp().getRequest() as Request ).query;

	const type  = ( typeof query[ 'sort' ]  === 'string' ) ? query[ 'sort' ]  : undefined;
	const order = ( typeof query[ 'order' ] === 'string' ) ? query[ 'order' ] : undefined;

	return {
		type:  ( isValueOf( Types, type ) )   ? type  : undefined,
		order: ( isValueOf( Orders, order ) ) ? order : undefined,
	};
})
