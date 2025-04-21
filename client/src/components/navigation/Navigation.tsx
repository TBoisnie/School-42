import React, { useMemo, useState } from 'react';
import { Link } from 'react-router-dom';
import { Navbar, Container, Nav } from 'react-bootstrap';
import { useAuth } from '../contexts/AuthContext';
import NavigationLogin from './components/NavigationLogin';
import NavigationLogout from './components/NavigationLogout';
import { useTranslation } from 'react-i18next';

const Navigation: React.FC = () => {
  const { t } = useTranslation();
  const { isAuthenticated } = useAuth();
  const navbarButtonHome = useMemo(() => t('navbar.button.home'), [t]);

  const [expanded, setExpanded] = useState(false);

  const handleLinkClick = () => {
    setExpanded(false);
  };

  return (
    <Navbar bg="dark  bg-opacity-75" variant="dark border-bottom w-100 shadow "
      className='position-fixed'
      style={{ zIndex: 1000 }}
      expand="lg"
      expanded={expanded}
    >
      <Container>
        <Navbar.Brand as={Link} to="/" onClick={handleLinkClick}>
          {navbarButtonHome}
        </Navbar.Brand>
        <Navbar.Toggle aria-controls="basic-navbar-nav" onClick={() => setExpanded(!expanded)} />
        <Navbar.Collapse id="basic-navbar-nav">
          <Nav className="me-auto w-100">
          {isAuthenticated ? (
              <NavigationLogin onClick={handleLinkClick} />
            ) : (
              <NavigationLogout onClick={handleLinkClick} />
            )}
          </Nav>
        </Navbar.Collapse>
      </Container>
    </Navbar>
  );
};

export default Navigation;