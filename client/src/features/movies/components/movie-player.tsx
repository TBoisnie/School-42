import { useEffect, useState } from "react";
import VideoPlayer from "../../../core/components/video-player";
import { Movie } from "../types/movie";
import { MovieApi } from "../services/movie-api";
import TorrentSelector from "./torrent-selector";
import { useTranslation } from "react-i18next";
import MovieDetails from "./movie-details";

export interface MoviePlayerProps
{
	imdbId : Movie['imdb_id'];
};

export default function MoviePlayer(
	{ imdbId } : MoviePlayerProps,
)
{
	const { t } = useTranslation( [ 'common', 'movies' ] );
	const [ isLoading, setIsLoading ] = useState( true );
	const [ movie, setMovie ] = useState< Movie | undefined >();
	const [ selectedTorrent, setSelectedTorrent ] = useState< Movie['torrents'][number] >();

	useEffect(() =>
	{
		MovieApi.get( imdbId )
			.then( ( m ) =>
			{
				setMovie( m );
				// setSelectedTorrent( m.torrents[ 0 ] ); // Note: Uncomment to auto select the first torrent
			})
			.catch( ( e ) => { /* console.log( e ) */ } )
			.finally( () => setIsLoading( false ) )
		;
	}, []);

	return (
		<>
			{ isLoading ? t( 'loading' ) : ! movie ? t( 'not_found', { ns: 'movies' } ) :
				<div style={ { display: 'flex', flexDirection: 'column', gap: '1em' } }>
					<VideoPlayer src={ selectedTorrent ? `https://localhost:5173/api/movies/${ movie.imdb_id }/torrents/${ selectedTorrent.hash }/stream` : undefined } />
					<TorrentSelector torrents={ movie.torrents } selectedTorrent={ selectedTorrent } setSelectedTorrent={ setSelectedTorrent } />
					<MovieDetails movie={ movie } />
				</div>
			}
		</>
	);
}
