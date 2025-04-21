
export const Types = [ 'title', 'year', 'rating', 'seeds' ] as const;
export const Orders = [ 'asc', 'desc' ] as const;

export type SortedBy =
{
	type?: typeof Types[ number ];
	order?: typeof Orders[ number ];
};
