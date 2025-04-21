import { useEffect, useState } from "react";
import { Dropdown } from "react-bootstrap";
import { useTranslation } from "react-i18next";
import { Movie } from "../types/movie";
import { Genre, Genres } from "../types/genre";

export interface MoviesFiltererProps
{
	movies: Movie[];
	setMovies: ( movies: Movie[] ) => void;
};

export default function MoviesFilterer(
	{ movies, setMovies }: MoviesFiltererProps
)
{
	const { t } = useTranslation();
	const [ genre, setGenre ] = useState< Genre | undefined >();

	useEffect(() =>
	{
		setMovies(
			movies.filter( ( movie ) =>
				( ! genre || movie.genres?.includes( Genres[ genre ] ) )
			)
		);
	}, [ movies, genre ]);

	return (
		<div style={ { display: 'flex', alignItems: 'center', gap: '1em' } }>
			{ t( 'filters' ) }
			<Dropdown>
				<Dropdown.Toggle>
					{ t( genre ? `genres.${ genre }` : 'genre' ) }
				</Dropdown.Toggle>

				<Dropdown.Menu style={ { overflowY: 'scroll', maxHeight: '25dvh' } } >
					<Dropdown.Item onClick={ () => setGenre(undefined) }>
						{ t( 'genres.any' ) }
					</Dropdown.Item>
					{ Object.keys( Genres ).map( ( genre ) =>
						<Dropdown.Item key={ genre } onClick={ () => setGenre( genre as Genre ) }>
							{ t( `genres.${ genre }` ) }
						</Dropdown.Item>
					)}
				</Dropdown.Menu>
			</Dropdown>
		</div>
	);
}
