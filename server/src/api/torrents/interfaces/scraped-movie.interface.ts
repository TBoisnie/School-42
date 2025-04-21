
export interface ScrapedMovie
{
	infos:
	{
		title: string;
		imdb_id: string;
	};
	torrents:
	{
		hash: string;
		quality: string;
	}[];
};
