import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { MovieView } from '../entities/view.entity.js';
import { Users } from '../../../api/users/entities/users.entity.js';
import { Movie } from '../entities/movie.entity.js';

@Injectable()
export class ViewsService
{

	constructor(
		@InjectRepository( MovieView )
		private readonly repository: Repository< MovieView >,
	)
	{
	}

	public async add(
		user: Pick< Users, 'id' >,
		movie: Pick< Movie, 'imdb_id' >
	)
		: Promise< MovieView >
	{
		return this.repository.save({ movie, user });
	}

}
