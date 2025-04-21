import { Movie } from './movie';

export const SortsBy: (keyof Pick<Movie, 'title'|'runtime'|'year'>)[] =
[
	'title',
	'year',
	'runtime'
] as const;

export type SortBy =
	keyof Pick<Movie, 'title'|'runtime'|'year'>
;

export const SortsOrder =
[
	'asc',
	'desc'
] as const;

export type SortOrder =
	typeof SortsOrder[ number ]
;
