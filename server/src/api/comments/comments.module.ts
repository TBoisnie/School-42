import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Comment } from './entities/comment.entity.js';
import { CommentsService } from './services/comments.service.js';
import { CommentsController } from './controllers/comments.controller.js';
import { AuthModule } from '../auth/auth.module.js';
import { JsonCommentPresenter } from './presenters/json.presenter.js';

@Module({
	imports: [
		TypeOrmModule.forFeature([ Comment ]),
		AuthModule,
	],
	controllers: [
		CommentsController,
	],
	providers: [
		CommentsService,
		JsonCommentPresenter,
	],
	exports: [
		CommentsService,
		JsonCommentPresenter,
	],
})
export class CommentsModule
{
}
