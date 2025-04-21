import { useParams } from "react-router-dom";
import { MoviePlayer } from "../../features/movies";
import { CommentsBrowser } from "../../features/comments";

export function Component()
{
	const { imdb_id } = useParams();

	return (
		<div style={ { display: 'flex', flexDirection: 'column', gap: '1em' } }>
			<MoviePlayer imdbId={ imdb_id! } />
			<CommentsBrowser movie_id={ imdb_id! } />
		</div>
	);
}
