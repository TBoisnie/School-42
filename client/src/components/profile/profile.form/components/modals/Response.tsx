// src/components/Modal/LoginModal.tsx
import React, { useCallback, useEffect, useMemo } from 'react';
import { useTranslation } from 'react-i18next';
import { useModal } from '../../../../contexts/ModalContext';

interface Props {
    isSubmitted: boolean;
    serverResponse: string | null;
    setIsSubmitted: (value: boolean) => void;
    setServerResponse: (value: string | null) => void;
}

const Response: React.FC<Props> = ({
    isSubmitted,
    serverResponse,
    setIsSubmitted,
    setServerResponse
}) => {

    // 5. useCustom
    const { t } = useTranslation();
    const { showModal } = useModal();

    // 6. useCallback / useMemo
    const successHeader = useMemo(() => t('profile.modal.update.success.header'), [t]);
    const successParagraph = useMemo(() => t('profile.modal.update.success.paragraph'), [t]);
    const errorHeader = useMemo(() => t('profile.modal.update.error.header'), [t]);
    const errorParagraph = useMemo(() => serverResponse ? t(`profile.modal.update.error.paragraph.${serverResponse}`) : '', [t, serverResponse]);

    // 7. Event handlers
    const handleOnHide = useCallback(() => {
        setTimeout(() => {
            setIsSubmitted(false);
            setServerResponse(null);
        }, 300);
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

    return null;
};

export default Response;