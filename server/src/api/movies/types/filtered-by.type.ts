
export const Genres = [
	'Action', 'Adventure', 'Animation', 'Biography', 'Comedy', 'Crime',
	'Documentary', 'Drama', 'Family', 'Fantasy', 'Film-Noir', 'History',
	'Horror', 'Music', 'Musical', 'Mystery', 'Romance', 'Sci-Fi', 'Sport',
	'Talk-Show', 'Thriller', 'War', 'Western',
] as const;

export type FilteredBy =
{
	title?: string;
	year?: number;
	rating?: number;
	genre?: typeof Genres[ number ];
};
