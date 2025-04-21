import { Injectable } from '@nestjs/common';
import { Movie } from '../entities/movie.entity.js';
import { OmdbService } from '../services/omdb.service.js';
import { Users } from '../../../api/users/entities/users.entity.js';

export type JsonMovie =
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
	seen: boolean|undefined;
};

@Injectable()
export class JsonMoviePresenter
{

	public constructor(
		private readonly omdb: OmdbService,
	)
	{
	}

	public async format(
		user: Users|undefined,
		movie: Movie,
	)
		: Promise< JsonMovie >
	{
		const details = await this.omdb.search({ imdb_id: movie.imdb_id });

		return {
			imdb_id: movie.imdb_id,
			imdb_rating: details?.imdb_rating,
			title: details?.title ?? movie.title,
			runtime: details?.runtime,
			year: details?.year,
			genres: details?.genres,
			poster: details?.poster,
			description: details?.description,
			torrents: movie.torrents.map( ( torrent ) => ({
				hash: torrent.hash,
				quality: torrent.quality,
			})),
			seen: user && (await user.seen_movies ?? []).some(( view ) => view.movie.imdb_id === movie.imdb_id)
		};
	}

}
