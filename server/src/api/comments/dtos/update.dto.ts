import { MaxLength, MinLength } from 'class-validator';

export class UpdateCommentDto
{
	@MinLength( 8, { message: 'comment.content.length.short' } )
	@MaxLength( 1024, { message: 'comment.content.length.long' } )
	content!: string;
};
