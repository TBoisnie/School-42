import { Page } from '../../../core/decorators/pagination.decorator.js';
import { FilteredBy } from '../../movies/types/filtered-by.type.js';
import { SortedBy } from '../../movies/types/sorted-by.type.js';
import { ScrapedMovie } from '../interfaces/scraped-movie.interface.js';

//
// ThePirateBay - Pseudo Api
//
export class TpbProvider
{
	private static readonly BASE_URL = 'https://apibay.org' as const;

	public async getTopMovies(
		page: Page,
	)
		: Promise< ScrapedMovie[] >
	{
		return this.searchMovies( { title: ' ' }, {}, page );
	}

	public async searchMovie(
		where: Pick< Required< ScrapedMovie['infos'] >, 'imdb_id' >,
	)
		: Promise< ScrapedMovie | null >
	{
		const movies = await this.searchMovies({ title: where.imdb_id }, {}, { index: 1, size: 1 } );

		if ( ! movies.length )
		{
			return null;
		}

		return movies[0];
	}

	public async searchMovies(
		filters: FilteredBy,
		sorts: SortedBy,
		page: Page,
	)
		: Promise< ScrapedMovie[] >
	{
		if ( page.index > 1 )
		{
			return [];
		}

		const url = new URL( `${ TpbProvider.BASE_URL }/q.php` );

		url.searchParams.set( 'q', filters?.title || ' ' );
		url.searchParams.set( 'cat', '207' );

		try
		{
			const response = await fetch( url );

			if ( ! response.ok )
			{
				throw undefined;
			}

			const torrents = await response.json();

			const movies = torrents
				.filter( ( d: any ) => ( d.imdb && +d.seeders > 5 ) )
				.reduce( ( dict: Record<string, ScrapedMovie>, torrent: any ) =>
				{
					if ( ! dict[torrent.imdb] )
					{
						dict[torrent.imdb] = {
							infos:{
								title: torrent.name,
								imdb_id: torrent.imdb,
							},
							torrents: []
						};
					}

					dict[torrent.imdb]['torrents'].push({
						hash: torrent.info_hash,
						quality: (torrent.name.match(/(720|1080|1440|2160|4320)p/))[0]
					});

					return dict;
				}, {})
			;

			return Object.values(movies);
		}
		catch ( err: unknown )
		{
			return [];
		}
	}

}
