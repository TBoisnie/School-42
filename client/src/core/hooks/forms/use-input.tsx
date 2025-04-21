import type { ChangeEvent } from 'react';
import { useState } from 'react';

/**
 * useInput
 */
export function useInput(
	_value : string,
)
{
	const [ value, setValue ] = useState( _value );

	function onChange(
		event : ChangeEvent< HTMLInputElement >,
	)
	{
		setValue( event.target.value );
	}

	return { value, onChange };
}
