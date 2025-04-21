import { useState } from "react";
import { Card } from "react-bootstrap";

export interface PosterProps
{
	image: string;
	title: string;
	hideTitle?: boolean;
	seen?: boolean;
}

export function Poster(
	{ image, title, hideTitle, seen }: PosterProps
)
{
	const [ focus, setFocus ] = useState(false);

	return (
		<Card title={ title } text="light" border={ focus ? 'light' : seen ? 'primary' : 'none' } style={ { background: 'rgb(17,21,25)' } } onMouseEnter={ () => setFocus(true) } onMouseLeave={()=>setFocus(false)}>
			<Card.Img variant="top" src={ image } alt={ title } style={ { aspectRatio: 2/3 } } />
			{ ! hideTitle &&
				<Card.Body>
					<Card.Text style={ { whiteSpace: 'nowrap', textOverflow: 'ellipsis', overflow: 'hidden' } }>
						{ title }
					</Card.Text>
				</Card.Body>
			}
		</Card>
	);
}
