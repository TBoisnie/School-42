import { useEffect, useState } from "react";

/**
 * useDebounce
 */
export function useDebounce< T >(
	_input : T,
	_delay : number = 150,
)
{
	const [ output, setOutput ] = useState< T >( _input );

	useEffect(() =>
	{
		const timer = setTimeout( () => setOutput( _input ), _delay );

		return () => clearTimeout( timer );
	}, [ _input ]);

	return [ output ];
}
