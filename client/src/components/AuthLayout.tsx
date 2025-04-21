import { Row } from "react-bootstrap"
import { Outlet } from "react-router-dom"

const AuthLayout: React.FC = () => {
    return (
        <Row xs={1} sm={1} md={2} lg={3} xl={3} xxl={3} className="h-100 m-0">
            <Outlet />
        </Row>
    );
  };

  export default AuthLayout;
