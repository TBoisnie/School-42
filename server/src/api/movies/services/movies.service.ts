import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { Movie } from '../entities/movie.entity.js';
import { ScrapedMovie } from '../../torrents/interfaces/scraped-movie.interface.js';

@Injectable()
export class MoviesService
{
	private readonly unallowedMovies: string[] = [];

	constructor(
		@InjectRepository( Movie )
		private readonly repository: Repository< Movie >,
	)
	{
	}

	public async save(
		data: ScrapedMovie,
	)
		: Promise< Movie >
	{
		return this.repository.save({
			imdb_id: data.infos.imdb_id,
			title: data.infos.title,
			torrents: data.torrents.map(( torrent ) => ({
				hash: torrent.hash,
				quality: torrent.quality,
			})),
		});
	}

	public async saveBulk(
		data: ScrapedMovie[],
	)
		: Promise< Movie[] >
	{
		return Promise.all( data.map( this.save.bind(this) ) );
	}

	public async find(
		by: Pick< Movie, 'imdb_id' >,
	)
		: Promise< Movie | null >
	{
		return this.repository.findOneBy( by );
	}

	public async delete(
		imdb_id: string,
	)
		: Promise< void >
	{
		const movie = this.unallowedMovies.find(( id ) => id === imdb_id);
		if (!movie) {	
			this.unallowedMovies.push(imdb_id);
		} else {
			throw new Error('Movie already unallowed');
		}
	}

}
