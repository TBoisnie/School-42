import { Body, Controller, Delete, Get, NotFoundException, Param, Post, Res, UseGuards, UsePipes, ValidationPipe } from '@nestjs/common';
// import { CacheInterceptor } from '@nestjs/cache-manager';
import { Page, Pagination } from '../../../core/decorators/pagination.decorator.js';
import { CookieGuard } from '../../auth/guards/cookie.guard.js';
import { FilteredBy, Filtering } from '../decorators/filtering.decorator.js';
import { SortedBy, Sorting } from '../decorators/sorting.decorator.js';
import { JsonMovie, JsonMoviePresenter } from '../presenters/json.presenter.js';
import { SearchService } from '../../torrents/services/search.service.js';
import { MoviesService } from '../services/movies.service.js';
import { StreamingService } from '../../../api/torrents/services/streaming.service.js';
import { JsonComment, JsonCommentPresenter } from '../../../api/comments/presenters/json.presenter.js';
import { UpdateCommentDto } from '../../../api/comments/dtos/update.dto.js';
import { CookiePayload } from '../../../api/auth/types/token-payload.type.js';
import { GetCookiePayload } from '../../../core/decorators/get-cookie-playload.decorator.js';
import { CommentsService } from '../../../api/comments/services/comments.service.js';
import { ViewsService } from '../services/views.service.js';
import { UsersService } from '../../../api/users/services/users.service.js';
import { Response } from 'express';
import { SubtitlesService } from '../../torrents/services/subtitles.service.js';

@Controller('movies')
export class MoviesController
{

	constructor(
		private readonly searcher: SearchService,
		private readonly movies: MoviesService,
		private readonly presenter: JsonMoviePresenter,
		private readonly streamer: StreamingService,
		private readonly comments: CommentsService,
		private readonly commentPresenter: JsonCommentPresenter,
		private readonly views: ViewsService,
		private readonly users: UsersService,
		private readonly subtitles: SubtitlesService,
	)
	{
	}

	@Get('/top')
	public async top()
		: Promise< JsonMovie[] >
	{
		const results = await this.searcher.movies({}, {}, { index: 1, size: 10 });

		if ( ! results )
		{
			return [];
		}

		const movies = await this.movies.saveBulk(results);

		return await Promise.all( movies.map( this.presenter.format.bind(this.presenter, undefined) ) );
	}

	@Get('/')
	@UseGuards(CookieGuard)
	// @UseInterceptors(CacheInterceptor)
	public async all(
		@Filtering() filters: FilteredBy,
		@Sorting() sorts: SortedBy,
		@Pagination() page: Page,
		@GetCookiePayload() cookie: CookiePayload,
	)
		: Promise< JsonMovie[] >
	{
		const results = await this.searcher.movies( filters, sorts, page );

		if ( ! results )
		{
			return [];
		}

		const movies = await this.movies.saveBulk( results );
		const user = await this.users.getUserById(cookie.id);

		return await Promise.all( movies.map( this.presenter.format.bind(this.presenter, user) ) );
	}

	@Get(':imdb_id')
	@UseGuards(CookieGuard)
	// @UseInterceptors(CacheInterceptor)
	public async one(
		@Param('imdb_id') imdb_id: string,
		@GetCookiePayload() cookie: CookiePayload,
	)
		: Promise< JsonMovie >
	{
		const result = await this.searcher.movie({ imdb_id });

		if ( ! result )
		{
			throw new NotFoundException('movie.one.not_found');
		}

		const movie = await this.movies.save( result );
		const user = await this.users.getUserById(cookie.id);

		return this.presenter.format( user, movie );
	}

	@Get(':imdb_id/comments')
	@UseGuards(CookieGuard)
	public async getComments(
		@Param('imdb_id') imdb_id: string,
		@Pagination() page: Page,
	)
		: Promise< JsonComment[] >
	{
		const movie = await this.movies.find({ imdb_id });

		if ( ! movie )
		{
			return [];
		}

		const size = 10;
		const comments = (await movie.comments).slice( ( page.index - 1 ) * size, page.index * size );

		return Promise.all( comments.map( this.commentPresenter.format.bind( this.commentPresenter ) ) );
	}

	@Post(':imdb_id/comments')
	@UseGuards(CookieGuard)
	@UsePipes(new ValidationPipe({ transform: true }))
	public async comment(
		@Param('imdb_id') imdb_id: string,
		@Body() body: UpdateCommentDto,
		@GetCookiePayload() user: CookiePayload,
	)
		: Promise< JsonComment >
	{
		const movie = await this.movies.find({ imdb_id });

		if ( ! movie )
		{
			throw new NotFoundException('movie.not_found');
		}

		const comment = await this.comments.create( user, movie, body );

		return this.commentPresenter.format( comment );
	}

	@Get(':imdb_id/torrents/:hash/stream')
	@UseGuards(CookieGuard)
	public async stream(
		@Param('imdb_id') imdb_id: string,
		@Param('hash') hash: string,
		@Res({ passthrough: false }) res: Response,
		@GetCookiePayload() user: CookiePayload,
	)
	{
		const movie = await this.searcher.movie({ imdb_id });

		if ( ! movie || ! movie.torrents.find( torrent => torrent.hash === hash ))
		{
			throw new NotFoundException('movie.stream.not_found');
		}

		this.views.add({ id: user.id }, { imdb_id: imdb_id });

		await this.streamer.stream( hash, res );
	}

	@Get(':imdb_id/torrents/:hash/subtitles/:lang')
	@UseGuards(CookieGuard)
	public async subtitle(
		@Param('imdb_id') imdb_id: string,
		@Param('hash') hash: string,
		@Param('lang') language: 'fr'|'en'|'es'|'de',
		@Res({ passthrough: false }) res: Response,
	)
	{
		const languages = {
			'fr': ['fre', 'fra'],
			'en': ['eng'],
			'es': ['esp', 'spa'],
			'de': ['ger', 'deu'],
		};

		if ( ! Object.keys(languages).includes( language ) )
		{
			throw new NotFoundException('movie.subtitle.unsupported_language');
		}

		const movie = await this.searcher.movie({ imdb_id });

		if ( ! movie )
		{
			throw new NotFoundException('movie.not_found');
		}

		await this.subtitles.download( hash, languages[ language ], res );
	}

	@Delete(':imdb_id')
	@UseGuards(CookieGuard)
	public async delete(
		@Param('imdb_id') imdb_id: string,
		@GetCookiePayload() user: CookiePayload,
	)
	{
		return this.movies.delete(imdb_id);
	}
}
