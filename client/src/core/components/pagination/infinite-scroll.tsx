import { ReactElement, useEffect, useRef, useState } from "react";
import { useTranslation } from "react-i18next";

export interface InfiniteScrollProps
{
	children : ReactElement;
	onNextPage : ( page : number ) => Promise< boolean >;
}

export default function InfiniteScroll(
	{ children, onNextPage } : InfiniteScrollProps,
)
{
	const ref = useRef( null );
	const [ page, setPage ] = useState( 1 );
	const [ hasNextPage, setHasNextPage ] = useState( true );
	const [ isLoading, setIsLoading ] = useState( false );
	const { t } = useTranslation();

	useEffect(() =>
	{
		setPage( 1 );
		setHasNextPage( true );
	}, [ onNextPage ]);

	useEffect(() =>
	{
		const observer = new IntersectionObserver(( entries ) =>
		{
			if ( page === 1 || ( entries[ 0 ].isIntersecting && ! isLoading ) )
			{
				setIsLoading( true );
				onNextPage( page )
					.then( ( hasNext ) =>
					{
						setPage( page + 1 );
						setHasNextPage( hasNext );
					})
					.catch( ( err : unknown ) =>
					{
						// console.log( `InfiniteScroll: Loading page ${ page } failed`, err );
					})
					.finally(() =>
					{
						setIsLoading( false );
					})
				;
			}
		});

		if ( ref.current )
		{
			observer.observe( ref.current );
		}

		return () => observer.disconnect();
	}, [ ref, page, onNextPage, setPage, setHasNextPage ]);

	return (
		<>
			{ children }
			<div style={ { padding: '1em', textAlign: 'center' } }>
				{ hasNextPage
					? <span ref={ ref } >{ t('loading') }...</span>
					: t('no_more_pages')
				}
			</div>
		</>
	);
}
