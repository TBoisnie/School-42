import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { TorrentsModule } from '../torrents/torrents.module.js';
import { MoviesController } from './controllers/movies.controller.js';
import { Movie } from './entities/movie.entity.js';
import { MoviesService } from './services/movies.service.js';
import { JsonMoviePresenter } from './presenters/json.presenter.js';
import { OmdbService } from './services/omdb.service.js';
import { AuthModule } from '../auth/auth.module.js';
import { CommentsModule } from '../comments/comments.module.js';
import { UsersModule } from '../users/users.module.js';
import { ViewsService } from './services/views.service.js';
import { MovieView } from './entities/view.entity.js';

@Module({
	imports: [
		TypeOrmModule.forFeature([ Movie, MovieView ]),
		TorrentsModule,
		AuthModule,
		CommentsModule,
		UsersModule,
	],
	controllers: [
		MoviesController,
	],
	providers: [
		MoviesService,
		OmdbService,
		JsonMoviePresenter,
		ViewsService,
	],
	exports: [
	],
})
export class MoviesModule
{
}
