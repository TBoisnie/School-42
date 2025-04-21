import { Col, Container, Row } from "react-bootstrap";
import { Outlet } from "react-router-dom";

export default function AuthLayout()
{
	return (
		<Container>
			<Row>
				<Col xs={12} md={8} className="m-auto">
					<Outlet />
				</Col>
			</Row>
		</Container>
	);
}
