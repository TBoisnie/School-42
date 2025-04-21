// delete account

import React, { useCallback, useEffect, useMemo, useState } from 'react';
import { useTranslation } from 'react-i18next';
import { useAuth } from '../../contexts/AuthContext';
import { useModal } from '../../contexts/ModalContext';
import { useNavigate } from 'react-router-dom';
import { Link } from 'react-router-dom';

// userData as arguments
interface ProfileDeleteProps {
    userData: {
        id: number;
        username: string;
        firstName: string;
        lastName: string;
        email: string;
    }
}

const Delete: React.FC<ProfileDeleteProps> = ({ userData }) => {

    // 1. useState
    const [isSubmitting, setIsSubmitting] = useState<boolean>(false);
    const [isSubmitted, setIsSubmitted] = useState<boolean>(false);
    const [serverResponse, setServerResponse] = useState<string | null>(null);

    // 5. useCustom
    const { t } = useTranslation();
    const { setIsAuthenticated } = useAuth();
    const { showModal, showConfirmBox } = useModal();
    const navigate = useNavigate();

    // 6. useCallback / useMemo
    const buttonDelete = useMemo(() => t('profile.button.delete'), [t]);
    const successHeader = useMemo(() => t('profile.modal.delete.success.header'), [t]);
    const successParagraph = useMemo(() => t('profile.modal.delete.success.paragraph'), [t]);
    const errorHeader = useMemo(() => t('profile.modal.delete.error.header'), [t]);
    const errorParagraph = useMemo(() => {
        if (serverResponse) {
            return t(`profile.modal.delete.error.paragraph.${serverResponse}`);
        }
        return '';
    }, [t, serverResponse]);

    // 7. Event handlers
    const handleOnAccept = useCallback(async () => {
        setIsSubmitting(true);
        const response = await fetch(`/api/users/${userData.id}`, {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json',
            },
        });
        setIsSubmitting(false);
        setIsSubmitted(true);
        if (!response.ok) {
            const message = (await response.json()).message;
            setServerResponse(message);
        } else {
            setServerResponse(null);
            showModal(
                handleOnHide,
                true,
                successHeader,
                successParagraph,
                errorHeader,
                errorParagraph,
            );
        }
    }, [userData.id]);


    const handleConfirmBox = useCallback(() => {
        showConfirmBox(
            () => { },
            'Are you sure you want to delete your account?',
            handleOnAccept,
            () => { },
        );
    }, [handleOnAccept, showConfirmBox]);

    const handleOnHide = useCallback(() => {
        setIsSubmitted(false);
        setServerResponse(null);
        setTimeout(() => {
            if (!serverResponse) {
                setIsAuthenticated(false);
                navigate('/');
            }
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
    }, [isSubmitted, serverResponse, successHeader, successParagraph, errorHeader, errorParagraph, handleOnHide, showModal]);

    return (
        <Link to="" className="align-self-center text-secondary"
            onClick={handleConfirmBox}
        >
            {buttonDelete}
        </Link>
    );
};

export default Delete;