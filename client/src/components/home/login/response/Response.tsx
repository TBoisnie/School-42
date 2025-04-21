// src/components/Modal/LoginModal.tsx
import React, { useCallback, useEffect, useMemo } from 'react';
import { useNavigate } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import { useModal } from '../../../contexts/ModalContext';
import { useAuth } from '../../../contexts/AuthContext';

interface LoginModalProps {
    isSubmitted: boolean;
    serverResponse: string | null;
    setIsSubmitted: (value: boolean) => void;
    setServerResponse: (value: string | null) => void;
}

const Response: React.FC<LoginModalProps> = ({ isSubmitted, serverResponse, setIsSubmitted, setServerResponse }) => {
    
    // 5. useCustom
    const { t } = useTranslation();
    const navigate = useNavigate();
    const { showModal } = useModal();
    const { setIsAuthenticated } = useAuth();

    // 6. useCallback / useMemo
    const successHeader = useMemo(() => t('login.modal.success.header'), [t]);
    const successParagraph = useMemo(() => t('login.modal.success.paragraph'), [t]);
    const errorHeader = useMemo(() => t('login.modal.error.header'), [t]);
    const errorParagraph = useMemo(() => serverResponse ? t(`login.modal.error.paragraph.${serverResponse}`) : '', [t, serverResponse]);

    // 7. Event handlers
    const handleOnHide = useCallback(() => {
        setTimeout(() => {
            setIsSubmitted(false);
            if (!serverResponse) {
                navigate('/');
                setIsAuthenticated(true);
            }
            setServerResponse(null);
        }, 300);
    }, [serverResponse]);

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

    return null;
};

export default Response;