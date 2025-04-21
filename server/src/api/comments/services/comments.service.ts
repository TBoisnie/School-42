import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { Page } from '../../../core/decorators/pagination.decorator.js';
import { Comment } from '../entities/comment.entity.js';
import { Users } from '../../users/entities/users.entity.js';
import { Movie } from '../../movies/entities/movie.entity.js';

@Injectable()
export class CommentsService
{
	constructor(
		@InjectRepository( Comment )
		private readonly repository: Repository< Comment >,
	)
	{
	}

	public async create(
		author: Pick< Users, 'id' >,
		movie: Pick< Movie, 'imdb_id' >,
		payload: Pick< Comment, 'content' >,
	)
		: Promise< Comment >
	{
		const comment = await this.repository.save( this.repository.create({
			author,
			movieImdbId: movie.imdb_id,
			content: payload.content,
		}));

		return this.repository.findOneByOrFail({ id: comment.id });
	}

	public async update(
		comment: Pick< Comment, 'id' >,
		payload: Pick< Comment, 'content' >,
	)
		: Promise< void >
	{
		await this.repository.update( comment, payload );
	}

	public async getPageOrderedByCreationDate(
		page: Page,
	)
		: Promise< Comment[] >
	{
		const PAGE_SIZE = 10;

		return this.repository.find(
		{
			order: { created_at: 'DESC' },
			skip: ( page.index - 1 ) * PAGE_SIZE,
			take: PAGE_SIZE,
		});
	}

	public async findOneBy(
		where: Pick< Comment, 'id' >
	)
		: Promise< Comment | null >
	{
		return this.repository.findOneBy( where );
	}

	public async delete(
		where: Pick< Comment, 'id' >,
	)
		: Promise< void >
	{
		await this.repository.delete( { id: where.id } );
	}
}
