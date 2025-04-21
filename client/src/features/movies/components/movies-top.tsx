import { useEffect, useState } from "react";
import { Movie } from "../types/movie";
import { MovieApi } from "../services/movie-api";
import { useTranslation } from "react-i18next";
import MovieList from "./movies-list";

export default function MoviesTop()
{
	const [ movies, setMovies ] = useState<Movie[]>([]);
	const { t } = useTranslation();

	useEffect(() =>
	{
		MovieApi.top()
			.then( ( movies: Movie[] ) =>
			{
				setMovies(
					movies
						.sort((a, b) => ( ( ! b.year ) ? 1 : ( ! a.year ) ? -1 : ( a.year <= b.year ) ? 1 : -1 ))
						.filter((_, i) => i < 12)
				);
			})
			.catch( ( e ) => { /* console.log( e ) */ } )
		;
	}, []);

	return (
		<>
		<h1>{ t('top') }</h1>
		<MovieList movies={ movies } />
		</>
	);
}
