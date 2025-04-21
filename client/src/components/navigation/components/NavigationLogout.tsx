import React, { useCallback, useMemo } from 'react';
import { Link } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import { Nav, NavDropdown, Button } from 'react-bootstrap';

interface NavigationLoginProps {
    onClick: () => void;
}

const NavigationLogin: React.FC<NavigationLoginProps> = ({ onClick }) => {

    // 5. useCustom
    const { t, i18n } = useTranslation();

    // 6. useCallback / useMemo
    const navbarButtonLanguage = useMemo(() => t('navbar.button.language'), [t]);
    const navbarButtonLogin = useMemo(() => t('navbar.button.login'), [t]);

    // 7. Event handlers
    const handleChangeLanguage = useCallback((language: string) => {
        i18n.changeLanguage(language);
        document.cookie = `lang=${language}; path=/`;
    }, []);

    return (
        <>

            <NavDropdown title={navbarButtonLanguage} menuVariant="dark" className='align-self-start'>
            <NavDropdown.Item onClick={() => handleChangeLanguage('en')}>English</NavDropdown.Item>
            <NavDropdown.Item onClick={() => handleChangeLanguage('fr')}>Français</NavDropdown.Item>
            <NavDropdown.Item onClick={() => handleChangeLanguage('es')}>Español</NavDropdown.Item>
            <NavDropdown.Item onClick={() => handleChangeLanguage('de')}>Deutsch</NavDropdown.Item>
            </NavDropdown>
            <Link to='/auth/login' className='align-self-start ms-auto'>
                <Button onClick={onClick}>
                    {navbarButtonLogin}
                </Button>
            </Link>
        </>
    );
};

export default NavigationLogin;
