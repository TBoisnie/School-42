
export function isValueOf< T extends readonly any[] >(
	accepted: T,
	value: any,
)
	: value is T[ number ]
{
	return ( value && accepted.includes( value ) );
}
