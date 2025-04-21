import { Page } from '../../../core/decorators/pagination.decorator.js';
import { FilteredBy } from '../../movies/types/filtered-by.type.js';
import { SortedBy } from '../../movies/types/sorted-by.type.js';
import { ScrapedMovie } from '../interfaces/scraped-movie.interface.js';

//
// Documentation: https://yts.mx/api
//
export class YtsProvider
{
	private static readonly BASE_URL = 'https://yts.mx/api/v2' as const;

	public async searchMovies(
		filters?: FilteredBy,
		sorts?: SortedBy,
		page?: Page,
	)
		: Promise< ScrapedMovie[] >
	{
		const url = new URL( `${ YtsProvider.BASE_URL }/list_movies.json` );

		if ( filters?.title )  url.searchParams.set( 'query_term', filters.title );
		if ( filters?.rating ) url.searchParams.set( 'minimum_rating', `${ filters.rating }` );
		if ( filters?.genre )  url.searchParams.set( 'genre', `${ filters.genre }` );
		                       url.searchParams.set( 'order_by', sorts?.order ?? 'desc' );
		                       url.searchParams.set( 'sort_by', sorts?.type ?? 'download_count' );
		if ( page )            url.searchParams.set( 'page', `${ page.index }` );

		try
		{
			// console.log('Fetching: ', url.toString())
			const response = await fetch( url );

			if ( ! response.ok )
			{
				throw undefined;
			}

			const { status, data } = await response.json();

			if ( status != 'ok' || data.movie_count == 0 )
			{
				throw undefined;
			}

			return data.movies.map( this._format );
		}
		catch ( err: unknown )
		{
			return [];
		}
	}

	public async searchMovie(
		where: Pick< Required< ScrapedMovie['infos'] >, 'imdb_id' >,
	)
		: Promise< ScrapedMovie | null >
	{
		const url = new URL( `${ YtsProvider.BASE_URL }/movie_details.json` );
		url.searchParams.set( 'imdb_id', where.imdb_id );

		try
		{
			const response = await fetch( url );

			if ( ! response.ok )
			{
				throw undefined;
			}

			const { status, data } = await response.json();

			if ( status != 'ok' || data.movie?.id == 0 )
			{
				throw undefined;
			}

			return this._format( data.movie );
		}
		catch ( err: unknown )
		{
			return null;
		}
	}

	private _format(
		movie: {
			imdb_code: string;
			title: string;
			torrents: { hash: string; quality: string; seeds: number; }[];
		}
	)
		: ScrapedMovie
	{
		return {
			infos: {
				title: movie.title,
				imdb_id: movie.imdb_code,
			},
			torrents: movie.torrents
				.filter( ( torrent ) => +torrent.seeds > 5 )
				.map( ( torrent ) => ({ hash: torrent.hash, quality: torrent.quality })),
		};
	}
}
