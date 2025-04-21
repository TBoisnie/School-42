
export type Movie =
{
	imdb_id: string;
	imdb_rating?: number;
	title: string;
	year?: number;
	runtime?: string;
	genres?: string[];
	poster?: string;
	description?: string;
	torrents: {
		hash: string;
		quality?: string;
	}[];
	seen: boolean;
};
