import { Fetch } from '../../../core/libs/fetch';
import { Movie } from '../types/movie';

export abstract class MovieApi
{
	private static readonly PATH = '/movies';

	public static async top()
	{
		const response = await Fetch.get( `${ MovieApi.PATH }/top` );

		if ( ! response.ok )
		{
			throw response;
		}

		return response.json();
	}

	public static async search(
		search?: string,
		page: number = 1,
	)
		: Promise< Movie[] >
	{
		const params = new URLSearchParams();
		params.set('page', page.toString());

		if ( search )
		{
			params.set('title', search);
		}

		const response = await Fetch.get( `${ MovieApi.PATH }?${ params.toString() }` );

		if ( ! response.ok )
		{
			throw response;
		}

		return response.json();
	}

	public static async get(
		imdbId: Movie['imdb_id'],
	)
		: Promise< Movie >
	{
		const response = await Fetch.get( `${ MovieApi.PATH }/${ imdbId }` );

		if ( ! response.ok )
		{
			throw response;
		}

		return response.json();
	}

}
