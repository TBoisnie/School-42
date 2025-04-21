
// Note: Keys matches translations, values matches backend returned values
export const Genres = {
	action: 'Action',
	adventure: 'Adventure',
	animation: 'Animation',
	biography: 'Biography',
	comedy: 'Comedy',
	crime: 'Crime',
	documentary: 'Documentary',
	drama: 'Drama',
	family: 'Family',
	fantasy: 'Fantasy',
	noir: 'Film-Noir',
	history: 'History',
	horror: 'Horror',
	music: 'Music',
	musical: 'Musical',
	mystery: 'Mystery',
	romance: 'Romance',
	scifi: 'Sci-Fi',
	sport: 'Sport',
	thriller: 'Thriller',
	war: 'War',
	western: 'Western',
} as const;

export type Genre =
	keyof typeof Genres
;
