import { Injectable } from '@nestjs/common';
import { Page } from '../../../core/decorators/pagination.decorator.js';
import { FilteredBy } from '../../movies/types/filtered-by.type.js';
import { SortedBy } from '../../movies/types/sorted-by.type.js';
import { ScrapedMovie } from '../interfaces/scraped-movie.interface.js';
import { YtsProvider } from '../providers/yts.provider.js';
import { TpbProvider } from '../providers/tpb.provider.js';

@Injectable()
export class SearchService
{

	public async movies(
		filters: FilteredBy,
		sorts: SortedBy,
		page: Page,
	)
		: Promise< ScrapedMovie[] >
	{
		const results = await Promise.allSettled([
			new YtsProvider().searchMovies( filters, sorts, page ),
			new TpbProvider().searchMovies( filters, sorts, page ),
		]);

		return results
			.filter( result => result.status == 'fulfilled' )
			.map( result => result.value )
			.reduce( ( movies, result ) =>
			{
				for ( const movie of result )
				{
					const found = movies.find( ( m ) => m.infos.imdb_id === movie.infos.imdb_id );

					if ( found )
					{
						this.merge( found, movie );
					}
					else
					{
						movies.push( movie );
					}
				}

				return  movies;
			}, [] )
			.filter( ( movie ) => movie.torrents.length > 0 )
		;
	}

	public async movie(
		where: Pick< Required< ScrapedMovie['infos'] >, 'imdb_id' >,
	)
		: Promise< ScrapedMovie | null >
	{
		const results = await Promise.allSettled([
			new YtsProvider().searchMovie( where ),
			new TpbProvider().searchMovie( where ),
		]);

		return results
			.filter( result => result.status == 'fulfilled' )
			.map( result => result.value )
			.reduce( ( movie, result ) =>
			{
				if ( ! movie || ! result )
				{
					return movie ?? result;
				}

				this.merge( movie, result );

				return movie;
			}, null );
	}

	private merge(
		dst: ScrapedMovie,
		src: ScrapedMovie,
	)
		: void
	{
		if ( ! dst.infos.title )
		{
			dst.infos.title = src.infos.title;
		}

		for ( const torrent of src.torrents )
		{
			if ( ! dst.torrents.find( ( t ) => t.hash === torrent.hash ) )
			{
				dst.torrents.push( torrent );
			}
		}
	}

}
