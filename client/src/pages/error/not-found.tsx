import { Container } from "react-bootstrap";
import { Link } from "react-router-dom";

export function Component()
{
	return (
		<Container className="align-self-center text-center h-100 d-flex flex-column justify-content-center">
			<h1>Page not found</h1>
			<Link to={ '/' }>Back to homepage</Link>
		</Container>
	);
}
