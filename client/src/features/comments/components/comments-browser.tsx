import { useCallback, useState } from "react";
import InfiniteScroll from "../../../core/components/pagination/infinite-scroll";
import { Comment, Comment as CommentType } from "../types/comment";
import { CommentApi } from "../services/comment-api";
import CommentsList from "./comment-list";
import CommentCreateForm from "./comment-create-form";
import { Movie } from "../../movies";
import { useTranslation } from "react-i18next";

export interface CommentsBrowserProps
{
	movie_id : Movie['imdb_id'];
};

export default function CommentsBrowser(
	{ movie_id } : CommentsBrowserProps,
)
{
	const { t } = useTranslation();
	const [ comments, setComments ] = useState< CommentType[] >( [] );

	const loadPage = useCallback( async ( page : number ) =>
	{
		const result = await CommentApi.movie( movie_id, page );

		setComments(( state ) => [ ...state, ...result ]);

		return ( result.length > 0 );
	}, []);

	const deleteComment = async (id: number) =>
	{
		try
		{
			const is_deleted = await CommentApi.delete(id);

			if ( is_deleted )
			{
				setComments(comments.filter(c => c.id != id));
			}
		}
		catch ( e: unknown )
		{
			// console.log('comments-browser:deleteComment:', e)
		}
	};

	return (
		<div style={ { display: 'flex', flexDirection: 'column', gap: '1em' } } >
			<h2>{ t('comments') }</h2>
			<CommentCreateForm movie_id={ movie_id } onCreated={ ( comment: Comment ) => setComments(( comments ) => [ comment, ...comments ]) } />
			<InfiniteScroll onNextPage={ loadPage }>
				<CommentsList comments={ comments } onDelete={ deleteComment } />
			</InfiniteScroll>
		</div>
	);
}
