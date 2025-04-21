import { useTranslation } from "react-i18next";
import { useInput } from "../../../core/hooks/forms/use-input";
import { FormEvent, useState } from "react";
import { Movie } from "../../movies";
import { CommentApi } from "../services/comment-api";
import { Comment } from "../types/comment";
import { Button, Form, InputGroup } from "react-bootstrap";

export interface CommentCreateFormProps
{
	movie_id : Movie['imdb_id'];
	onCreated ?: ( comment : Comment ) => void;
};

export default function CommentCreateForm(
	{ movie_id, onCreated } : CommentCreateFormProps,
)
{
	const content = useInput( '' );
	const [ error, setError ] = useState< string | undefined >();
	const { t } = useTranslation();

	const onSubmit = async ( e : FormEvent<HTMLFormElement> ) =>
	{
		e.preventDefault();

		try
		{
			const comment = await CommentApi.create( movie_id, content.value );
			onCreated?.( comment );
			content.onChange( { target: { value: '' } } as any );
		}
		catch ( err: unknown )
		{
			if ( err instanceof Response )
			{
				err.json().then( ( value ) => setError( `${ value.message }` ) ).catch();
			}
		}
	};

	return (
		<form onSubmit={ onSubmit }>
			<InputGroup hasValidation>
				<InputGroup.Text>{ t('create') }</InputGroup.Text>
				<Form.Control aria-label={ t('create') } { ...content } required isInvalid={ !! error } onChange={ (e) => { setError(undefined); content.onChange(e as any); } } />
				<Button type='submit' variant="primary">{ t('save') }</Button>
				{ error && <Form.Control.Feedback type="invalid">{ t( 'comment.content.length' ) }</Form.Control.Feedback> }
			</InputGroup>
		</form>
	);

}
