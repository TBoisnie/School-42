import { ToggleButton, ToggleButtonGroup } from "react-bootstrap";
import { Movie } from "../types/movie";
import { useId } from "react";

export interface TorrentSelectorProps
{
	torrents : Movie['torrents'];
	selectedTorrent ?: Movie['torrents'][ number ];
	setSelectedTorrent : ( torrent: Movie['torrents'][ number ] ) => void;
};

export default function TorrentSelector(
	{ torrents, selectedTorrent, setSelectedTorrent } : TorrentSelectorProps,
)
{
	const id = useId();

	const uniqueQualityTorrents = torrents
		.filter(( torrent, index, arr ) => arr.findIndex(( t ) => t.quality === torrent.quality ) === index )
	;

	return (
		<ToggleButtonGroup type='radio' name={ id } value={ selectedTorrent?.hash }>
			{ uniqueQualityTorrents.map( ( torrent ) =>
				<ToggleButton
					key={ torrent.hash }
					id={ `${ id }_${ torrent.hash }`}
					value={ torrent.hash }
					onClick={ () => setSelectedTorrent( torrent ) }
				>
					{ torrent.quality }
				</ToggleButton>
			)}
		</ToggleButtonGroup>
	);
}
