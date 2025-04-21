import { Container, Row } from "react-bootstrap";
import { Outlet } from "react-router-dom";
import Navigation from "../../components/navigation/Navigation";

export function MainLayout()
{
	return (
		<Container fluid className="bg-dark text-light min-vh-100">
			<Row>
				<Navigation />
			</Row>
			<Row>
				<Outlet />
			</Row>
		</Container>
	);
}
