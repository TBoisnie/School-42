import { useTranslation } from "react-i18next";
import { Table } from "react-bootstrap";
import { Poster } from "../../../core/components/poster";
import { Movie } from "../types/movie";

export interface MovieDetailsProps
{
	movie : Movie,
};

export default function MovieDetails(
	{ movie } : MovieDetailsProps,
)
{
	const { t } = useTranslation();

	return (
		<div style={ { display: 'flex', alignItems: 'start', gap: '1em' } }>
			<Poster image={ movie.poster! } title={ movie.title } hideTitle />
			<Table variant='dark' striped bordered hover>
				<tbody>
					<tr><td>{ t('infos.title') }</td><td>{ movie.title }</td></tr>
					<tr><td>{ t('infos.year') }</td><td>{ movie.year }</td></tr>
					<tr><td>{ t('infos.runtime') }</td><td>{ movie.runtime }</td></tr>
					<tr><td>{ t('infos.rating') }</td><td>{ movie.imdb_rating }</td></tr>
					<tr><td>{ t('infos.description') }</td><td>{ movie.description }</td></tr>
				</tbody>
			</Table>
		</div>
	);
}
