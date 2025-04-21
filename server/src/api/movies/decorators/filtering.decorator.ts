import { createParamDecorator, ExecutionContext } from '@nestjs/common';
import { Request } from 'express';
import { isValueOf } from '../../../core/utilities/typing/is-value-of.utility.js';
import { toSafeInt } from '../../../core/utilities/string/to-safe-int.utility.js';
import { FilteredBy, Genres } from '../types/filtered-by.type.js';

export { FilteredBy };

export const Filtering = createParamDecorator((
	_: unknown,
	ctx: ExecutionContext,
)
	: FilteredBy =>
{
	const RATING = { MIN: 1, MAX: 9, DEFAULT: 0 } as const;
	const YEAR   = { MIN: 1, MAX: new Date(Date.now()).getFullYear(), DEFAULT: 0 } as const;

	const query = ( ctx.switchToHttp().getRequest() as Request ).query;

	const title  = ( query[ 'title' ] )  ? decodeURI( query[ 'title' ].toString() )  : undefined;
	const genre  = ( query[ 'genre' ] )  ? query[ 'genre' ].toString()  : undefined;
	const year   = ( query[ 'year' ] )   ? toSafeInt( query[ 'year' ].toString(),   YEAR.DEFAULT )   : undefined;
	const rating = ( query[ 'rating' ] ) ? toSafeInt( query[ 'rating' ].toString(), RATING.DEFAULT ) : undefined;

	return {
		title,
		year:   ( year   && YEAR.MIN   <= year   && year   <= YEAR.MAX )   ? year   : undefined,
		rating: ( rating && RATING.MIN <= rating && rating <= RATING.MAX ) ? rating : undefined,
		genre:  ( isValueOf( Genres, genre ) ) ? genre : undefined,
	};
})
