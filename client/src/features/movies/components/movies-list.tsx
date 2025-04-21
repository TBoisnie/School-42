import { Link } from "react-router-dom";
import { Poster } from "../../../core/components/poster";
import { Movie } from "../types/movie";

interface MovieListProps
{
	movies: Movie[];
}

export default function MovieList(
	{ movies }: MovieListProps
)
{
	return (
		<ul style={ { display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(12rem, 1fr))', padding: 0, gap: '.5rem', margin: 0, listStyle: 'none' } }>
			{ movies.map( ( movie ) =>
				<li key={ movie.imdb_id } style={ { position: 'relative' } }>
					<Link to={ `/movies/${ movie.imdb_id }` } style={ { textDecoration: 'none' } }>
						<Poster image={ movie.poster ?? '' } title={ movie.title } seen={ movie.seen } />
						{ movie.year &&
							<span style={ { padding: '.25em .5em', position: 'absolute', top: '.5em', left: '.5em', borderRadius: '.25em', color: 'white', background: 'hsl(0 0 0 / .75)' } }>
								{ movie.year }
							</span>
						}
						{ movie.imdb_rating &&
							<span style={ { padding: '.25em .5em', position: 'absolute', top: '.5em', right: '.5em', borderRadius: '.25em', color: 'white', background: 'hsl(0 0 0 / .75)' } }>
								{ movie.imdb_rating }/10
							</span>
						}
					</Link>
				</li>
			)}
		</ul>
	);
}
