import { useCallback, useState } from "react";
import InfiniteScroll from "../../../core/components/pagination/infinite-scroll";
import MoviesSearchForm from "./movies-search-form";
import MoviesFilterer from "./movies-filterer";
import MoviesSorter from "./movies-sorter";
import MoviesList from "./movies-list";
import { MovieApi } from "../services/movie-api";
import { Movie } from "../types/movie";

export default function MoviesBrowser()
{
	const [ search, setSearch ] = useState( "" );

	const [ movies, setMovies ] = useState< Movie[] >( [] );
	const [ filteredMovies, setFilteredMovies ] = useState< Movie[] >( movies );
	const [ sortedMovies, setSortedMovies ] = useState< Movie[] >( filteredMovies );

	const request = useCallback( async ( title : string | undefined, page : number ) =>
	{
		const result = await MovieApi.search( title, page );

		setMovies(( state ) =>
		{
			const merge = ( page === 1) ? result : [ ...state, ...result ];

			return merge.filter( ( movie, index ) => merge.findIndex( m  => movie.imdb_id === m.imdb_id ) === index);
		});

		return ( result.length > 0 );
	}, []);

	const loadPage = useCallback( ( page : number ) => request( search, page ), [ search ]);

	return (
		<>
			<div style={ { display: 'flex', flexWrap: 'wrap', justifyContent: 'space-between', gap: '.5em', padding: '1em' } }>
				<MoviesSearchForm search={ search } onSubmit={ setSearch } />
				<div style={{ display: 'flex', flexWrap: 'wrap', gap: '.5em' }} >
					<MoviesFilterer movies={ movies } setMovies={ setFilteredMovies } />
					<MoviesSorter movies={ filteredMovies } setMovies={ setSortedMovies } sortBy={ search ? 'title' : undefined } orderBy={ search ? 'asc' : 'desc' } />
				</div>
			</div>
			<div>
				<InfiniteScroll onNextPage={ loadPage }>
					<MoviesList movies={ sortedMovies } />
				</InfiniteScroll>
			</div>
			</>
	);
}
