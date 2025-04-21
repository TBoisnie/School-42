import { useEffect, useId } from "react";
import { useInput } from "../../../core/hooks/forms/use-input";
import { useDebounce } from "../../../core/hooks/use-debounce";

export interface MoviesSearchFormProps
{
	search ?: string;
	onSubmit : ( title : string ) => void;
};

export default function MoviesSearchForm(
	{ search, onSubmit } : MoviesSearchFormProps,
)
{
	const id = useId();
	const title = useInput( search ?? "" );
	const [ debouncedValue ] = useDebounce( title.value, 1000 );

	useEffect(() =>
	{
		onSubmit( title.value.trim() );
	}, [ debouncedValue ]);

	return (
		<form style={ { display: 'flex', alignItems: 'center', gap: '1em' } } onSubmit={ e => e.preventDefault() }>
			<label htmlFor={ `${ id }_title` }>Search: </label>
			<input type='text' name='title' id={ `${ id }_title` } { ...title } />
		</form>
	);
}
