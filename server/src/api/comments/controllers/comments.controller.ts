import { Body, Controller, Delete, ForbiddenException, Get, HttpCode, HttpStatus, NotFoundException, Param, Patch, Post, UseGuards, UsePipes, ValidationPipe } from '@nestjs/common';
import { Page, Pagination } from '../../../core/decorators/pagination.decorator.js';
import { CommentsService } from '../services/comments.service.js';
import { CreateCommentDto } from '../dtos/create.dto.js';
import { UpdateCommentDto } from '../dtos/update.dto.js';
import { GetCookiePayload } from '../../../core/decorators/get-cookie-playload.decorator.js';
import { CookiePayload } from '../../auth/types/token-payload.type.js';
import { CookieGuard } from '../../auth/guards/cookie.guard.js';
import { JsonComment, JsonCommentPresenter } from '../presenters/json.presenter.js';
import { Comment } from '../entities/comment.entity.js';

@Controller('comments')
@UseGuards(CookieGuard)
export class CommentsController
{

	constructor(
		private readonly comments: CommentsService,
		private readonly presenter: JsonCommentPresenter,
	)
	{
	}

	@Get()
	public async all(
		@Pagination() page: Page,
	)
		: Promise< JsonComment[] >
	{
		const comments = await this.comments.getPageOrderedByCreationDate( page );

		return Promise.all( comments.map( this.presenter.format.bind(this.presenter) ) );
	}

	@Get(':id')
	public async one(
		@Param('id') id: Comment['id'],
	)
		: Promise< JsonComment >
	{
		const comment = await this.comments.findOneBy({ id });

		if ( ! comment )
		{
			throw new NotFoundException('comment.one.not_found');
		}

		return this.presenter.format( comment );
	}

	@Post()
	@UsePipes(new ValidationPipe({ transform: true }))
	public async create(
		@GetCookiePayload() user: CookiePayload,
		@Body() dto: CreateCommentDto,
	)
		: Promise< Pick< Comment, 'id' > >
	{
		return this.comments.create( { id: user.id }, { imdb_id: dto.movie_id }, { content: dto.content } );
	}

	@Patch(':id')
	@UsePipes(new ValidationPipe({ transform: true }))
	public async update(
		@GetCookiePayload() user: CookiePayload,
		@Param('id') id: number,
		@Body() dto: UpdateCommentDto,
	)
		: Promise< void >
	{
		const comment = await this.comments.findOneBy({ id });

		if ( ! comment )
		{
			throw new NotFoundException('comment.update.not_found');
		}

		if ( comment.author.id != user.id )
		{
			throw new ForbiddenException('comment.update.forbidden');
		}

		return this.comments.update( comment, dto );
	}

	@Delete(':id')
	@HttpCode(HttpStatus.NO_CONTENT)
	public async delete(
		@GetCookiePayload() user: CookiePayload,
		@Param('id') id: number,
	)
		: Promise< void >
	{
		const comment = await this.comments.findOneBy({ id });

		if ( ! comment )
		{
			return ;
		}

		if ( comment.author.id != user.id )
		{
			throw new ForbiddenException('comment.delete.forbidden');
		}

		await this.comments.delete( comment );
	}

}
