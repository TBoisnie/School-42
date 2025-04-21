import React, { useCallback, useEffect, useMemo, useState } from 'react';
import { Nav, NavDropdown } from 'react-bootstrap';
import { Link, useNavigate } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import ValidationButton from '../../common/ValidationButton';
import { useAuth } from '../../contexts/AuthContext';
import { useModal } from '../../contexts/ModalContext';
import i18n from '../../../utilities/Translation';

interface NavigationLoginProps {
    onClick: () => void;
}

const NavigationLogin: React.FC<NavigationLoginProps> = ({ onClick }) => {

    // 1. useState
    const [isSubmitting, setIsSubmitting] = useState<boolean>(false);
    const [isSubmitted, setIsSubmitted] = useState<boolean>(false);
    const [serverResponse, setServerResponse] = useState<string | null>(null);

    // 3. useContext
    const { setIsAuthenticated } = useAuth();
    const { showModal, hideModal } = useModal();

    // 5. useCustom
    const { t } = useTranslation();
    const navigate = useNavigate();

    // 6. useCallback / useMemo
    const buttonProfile = useMemo(() => t('navbar.button.profile'), [t]);
    const buttonMovies = useMemo(() => t('navbar.button.movies'), [t]);
    const buttonUsers = useMemo(() => t('navbar.button.users'), [t]);
    const buttonLogout = useMemo(() => t('navbar.button.logout'), [t]);

    const successHeader = useMemo(() => t('navbar.modal.success.header'), [t]);
    const successParagraph = useMemo(() => t('navbar.modal.success.paragraph'), [t]);
    const errorHeader = useMemo(() => t('navbar.modal.error.header'), [t]);
    const errorParagraph = useMemo(() => {
        if (serverResponse) {
            return t(`navbar.modal.error.paragraph.${serverResponse}`);
        }
        return '';
    }, [t, serverResponse]);

        const navbarButtonLanguage = useMemo(() => t('navbar.button.language'), [t]);
    

    // 7. Event handlers

    const handleOnHide = useCallback(() => {
        hideModal();
        setTimeout(() => {
            setIsSubmitted(false);
            if (!serverResponse) {
                setIsAuthenticated(false);
                navigate('/');
            }
        }, 300);
    }, [isSubmitted, setIsAuthenticated, navigate]);

    const handleLogout = useCallback(async () => {
        try {
            setIsSubmitting(true);
            const response = await fetch('/api/auth/logout', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
            });
            setIsSubmitting(false);
            setIsSubmitted(true);
            if (!response.ok) {
                setServerResponse('server');
            } else {
                setServerResponse(null);
            }
        } catch (error) {
            setServerResponse('server');
            console.error(error);
        }
    }, []);

        const handleChangeLanguage = useCallback((language: string) => {
            i18n.changeLanguage(language);
            document.cookie = `lang=${language}; path=/`;
        }, []);

    // 8. useEffect
    useEffect(() => {
        if (isSubmitted) {
            showModal(
                handleOnHide,
                !serverResponse,
                successHeader,
                successParagraph,
                errorHeader,
                errorParagraph,
            );
        }
    }, [isSubmitted, serverResponse]);

    return (
        <>
                    <NavDropdown title={navbarButtonLanguage} menuVariant="dark" className='align-self-start'>
            <NavDropdown.Item onClick={() => handleChangeLanguage('en')}>English</NavDropdown.Item>
            <NavDropdown.Item onClick={() => handleChangeLanguage('fr')}>Français</NavDropdown.Item>
            <NavDropdown.Item onClick={() => handleChangeLanguage('es')}>Español</NavDropdown.Item>
            <NavDropdown.Item onClick={() => handleChangeLanguage('de')}>Deutsch</NavDropdown.Item>
            </NavDropdown>
            <Nav.Link as={Link} to="/auth/profile" className='align-self-start' onClick={onClick}>
                {buttonProfile}
            </Nav.Link>
            <Nav.Link as={Link} to="/movies" className='align-self-start' onClick={onClick}>
                {buttonMovies}
            </Nav.Link>
            <Nav.Link as={Link} to="/users" className='align-self-start' onClick={onClick}>
                {buttonUsers}
            </Nav.Link>
            <ValidationButton
                isSubmitted={isSubmitted}
                isSubmitting={isSubmitting}
                isDisabled={isSubmitting}
                isFormValidated={!serverResponse}
                onClick={async () => { handleLogout(); onClick() }}
                text={buttonLogout}
                type='button'
                className='ms-auto'
            />
        </>
    );
};

export default NavigationLogin;