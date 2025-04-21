
export function toSafeInt(
	value: string,
	backup: number,
)
{
	const x = Math.trunc( +value );
	return ( Number.isSafeInteger( x ) ) ? x : backup;
}
