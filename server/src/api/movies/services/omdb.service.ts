import { Injectable } from '@nestjs/common';

export type MovieDetails =
{
	imdb_id: string;
	imdb_rating: number;
	title: string;
	year: number;
	runtime: string;
	description: string;
	genres: string[];
	poster: string;
};

@Injectable()
export class OmdbService
{

	private static BASE_URL = 'http://www.omdbapi.com';

	public constructor()
	{
	}

	public async search(
		search: { imdb_id: string } | { title: string },
	)
		: Promise< MovieDetails | null >
	{
		const url = new URL(`${ OmdbService.BASE_URL }`);
		url.searchParams.set('apikey', process.env.OMDB_API_KEY!);

		if ( 'title' in search )
		{
			url.searchParams.set('t', encodeURI(search.title));
		}
		else
		{
			url.searchParams.set('i', encodeURI(search.imdb_id));
		}

		try
		{
			const response = await fetch(url);
			const json = await response.json();

			return {
				imdb_id: json['imdbId'],
				imdb_rating: +json['imdbRating'],
				title: json['Title'],
				year: +json['Year'],
				description: json['Plot'],
				runtime: json['Runtime'],
				genres: (json['Genre'] as string).split(', '),
				poster: json['Poster'],
			};
		}
		catch ( err: unknown )
		{
			return null;
		}
	}

}
