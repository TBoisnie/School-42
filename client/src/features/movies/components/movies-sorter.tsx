import { useEffect, useState } from "react";
import { Dropdown } from "react-bootstrap";
import { useTranslation } from "react-i18next";
import { Movie } from "../types/movie";
import { SortsBy, SortBy, SortsOrder, SortOrder } from "../types/sort";

export interface MoviesSorterProps
{
	movies : Movie[];
	setMovies : ( movies: Movie[] ) => void;
	sortBy ?: SortBy;
	orderBy ?: SortOrder;
};

export default function MoviesSorter(
	{ movies, setMovies, sortBy, orderBy } : MoviesSorterProps
)
{
	const { t } = useTranslation();
	const [ sort_by, setSortBy ] = useState< SortBy | undefined >( sortBy );
	const [ sort_order, setSortOrder ] = useState< SortOrder >( orderBy ?? 'desc');

	useEffect(() =>
	{
		setSortBy( sortBy );
	}, [ setSortBy, sortBy ]);

	useEffect(() =>
	{
		setSortOrder( orderBy ?? 'desc' );
	}, [ setSortOrder, orderBy ]);

	useEffect(() =>
	{
		setMovies(
			movies.toSorted( ( a, b ) =>
			{
				if ( ! sort_by )
				{
					return ( sort_order === 'asc' ) ? -1 : 1;
				}

				if ( ! b[ sort_by ] )
				{
					return ( ( sort_order === 'asc' ) ? -1 : 1 );
				}

				if ( ! a[ sort_by ] )
				{
					return ( ( sort_order === 'asc' ) ? 1 : -1 );
				}

				if ( a[ sort_by ] <= b[ sort_by ] )
				{
					return ( ( sort_order === 'asc' ) ? -1 : 1 );
				}

				return ( ( sort_order === 'asc' ) ? 1 : -1 );
			})
		);
	}, [ movies, sort_by, sort_order ]);

	return (
		<div style={ { display: 'flex', alignItems: 'center', gap: '1em' } }>
			{ t('sort_by') }
			<Dropdown>
				<Dropdown.Toggle>
					{ t( `infos.${ sort_by ?? 'add_date' }` ) }
				</Dropdown.Toggle>
				<Dropdown.Menu style={ { overflowY: 'scroll', maxHeight: '25dvh' } } >
					<Dropdown.Item onClick={ () => setSortBy( undefined ) }>
						{ t( `infos.add_date` ) }
					</Dropdown.Item>
					{ SortsBy.map( ( by ) =>
						<Dropdown.Item key={ by } onClick={ () => setSortBy( by as SortBy ) }>
							{ t( `infos.${ by }` ) }
						</Dropdown.Item>
					)}
				</Dropdown.Menu>
			</Dropdown>
			{ t('order') }
			<Dropdown>
				<Dropdown.Toggle>
					{ t( `orders.${ sort_order }` ) }
				</Dropdown.Toggle>
				<Dropdown.Menu style={ { overflowY: 'scroll', maxHeight: '25dvh' } } >
					{ SortsOrder.map( ( order ) =>
						<Dropdown.Item key={ order } onClick={ () => setSortOrder( order as SortOrder ) }>
							{ t( `orders.${ order }` ) }
						</Dropdown.Item>
					)}
				</Dropdown.Menu>
			</Dropdown>
		</div>
	);
}
