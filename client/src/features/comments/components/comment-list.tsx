import { Card } from "react-bootstrap";
import { Comment } from "../types/comment";
import { NavLink } from "react-router-dom";

interface CommentsListProps
{
	comments: Comment[];
	onDelete: (id:number) => Promise< void >;
}

export default function CommentsList(
	{ comments, onDelete } : CommentsListProps,
)
{
	return (
		<ul style={ { display: 'flex', flexDirection: 'column', padding: 0, gap: '.5rem', margin: 0, listStyle: 'none' } }>
			{ comments.map( ( comment ) =>
				<li key={ comment.id }>
					<Card text='light' style={ { padding: '.5em', gap: '.5em', background: '#111519' } }>
						<header style={ { display: 'flex', justifyContent: 'space-between' } }>
							<span>#{ comment.id } - By <NavLink to={ `/users/${ comment.author.id }` }>{ comment.author.username }</NavLink></span>
							<span onClick={ () => onDelete(comment.id) } style={ { cursor: 'pointer' } } title="Delete">X</span>
						</header>
						<div style={ { paddingTop: '.5em', borderTop: '1px solid #212529'} }>
							{ comment.content }
						</div>
					</Card>
				</li>
			)}
		</ul>
	);
}
