import { Comment } from '../entities/comment.entity.js';

export type JsonComment =
	& Pick< Comment, 'id'|'content'|'created_at' >
	& { author: Pick< Comment['author'], 'id'|'username' > }
	& { movie: Pick< Awaited< Comment['movie'] >, 'imdb_id' > }
;

export class JsonCommentPresenter
{

	public async format(
		comment: Comment
	)
		: Promise< JsonComment >
	{
		const author = comment.author;
		const movie = await comment.movie;

		return {
			id: comment.id,
			content: comment.content,
			author: {
				id: author.id,
				username: author.username,
			},
			movie: {
				imdb_id: movie.imdb_id,
			},
			created_at: comment.created_at,
		};
	}

}
