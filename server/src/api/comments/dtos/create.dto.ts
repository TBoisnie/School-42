import { Matches, MaxLength, MinLength } from 'class-validator';

export class CreateCommentDto
{
	@Matches( /^tt\d{4,16}$/, { message: 'comment.movie_id.invalid' } )
	movie_id!: string;

	@MinLength( 8, { message: 'comment.content.length.short' } )
	@MaxLength( 1024, { message: 'comment.content.length.long' } )
	content!: string;
};
