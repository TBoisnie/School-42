
import { Fetch } from '../../../core/libs/fetch';
import { Movie } from '../../movies';
import { Comment } from '../types/comment';

export abstract class CommentApi
{

	public static async movie(
		movie_id: Movie['imdb_id'],
		page: number = 1,
	)
		: Promise< Comment[] >
	{
		const params = new URLSearchParams();
		params.set('page', page.toString());

		const response = await Fetch.get( `/movies/${ movie_id }/comments?${ params.toString() }` );

		if ( ! response.ok )
		{
			throw response;
		}

		return response.json();
	}

	public static async create(
		movie_id: Movie['imdb_id'],
		content: string,
	)
		: Promise< Comment >
	{
		const response = await Fetch.post( `/movies/${ movie_id }/comments`, {
			headers: {
				'Accept': 'application/json',
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({ content })
		} );

		if ( ! response.ok )
		{
			throw response;
		}

		return response.json();
	}

	public static async delete(
		id: number,
	)
		: Promise< boolean >
	{
		const response = await Fetch.delete( `/comments/${ id }` );

		return response.ok;
	}

}
