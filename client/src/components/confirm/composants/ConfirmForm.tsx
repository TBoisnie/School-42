// composant to confirm password
import React, { useCallback, useEffect, useMemo, useState } from 'react';
import { Form } from 'react-bootstrap';
import { useTranslation } from 'react-i18next';
import * as validate from '../../../utilities/Validators';
import ValidationInput from '../../common/ValidationInput';
import ValidationButton from '../../common/ValidationButton';
import { useLocation, useNavigate } from 'react-router-dom';
import { useModal } from '../../contexts/ModalContext';

const ConfirmForm: React.FC = () => {

    // 1. useState
    const [isValidPassword, setIsValidPassword] = useState(false);
    const [isSubmitting, setIsSubmitting] = useState<boolean>(false);
    const [isSubmitted, setIsSubmitted] = useState<boolean>(false);
    const [serverResponse, setServerResponse] = useState<string | null>(null);

    // 5. useCustom
    const { t } = useTranslation();
    const location = useLocation();
    const navigate = useNavigate();
    const { showModal } = useModal();

    // 6. useCallback / useMemo
    const confirmInputPassword = useMemo(() => t('confirm.input.password'), [t]);
    const confirmButtonConfirm = useMemo(() => t('confirm.button.confirm'), [t]);
    const confirmModalSuccessHeader = useMemo(() => t('confirm.modal.success.header'), [t]);
    const confirmModalSuccessParagraph = useMemo(() => t('confirm.modal.success.paragraph'), [t]);
    const confirmModalErrorHeader = useMemo(() => t('confirm.modal.error.header'), [t]);
    const confirmModalErrorParagraph = useMemo(() => t('confirm.modal.error.paragraph.server'), [t]);

    const isFormValid = useMemo(() => {
        return isValidPassword;
    }, [isValidPassword]);

    // 7. Event handlers
    const handleSubmit = useCallback(async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        e.stopPropagation();
        const form = e.currentTarget;
        if (form.checkValidity() === false) {
            return;
        }
        if (isFormValid) {
            setIsSubmitting(true);
            const formData = new FormData(form);
            const formObject = Object.fromEntries(formData.entries());
            try {
                const queryParams = new URLSearchParams(location.search);
                const token = queryParams.get('token');
                const response = await fetch('/api/auth/confirm?token=' + token, {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify(formObject),
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
        }
    }, [isFormValid]);

    const handleOnHide = useCallback(() => {
        setTimeout(() => {
            setIsSubmitted(false);
            if (!serverResponse) {
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
                confirmModalSuccessHeader,
                confirmModalSuccessParagraph,
                confirmModalErrorHeader,
                confirmModalErrorParagraph
            );
        }
    }, [isSubmitted, serverResponse]);

    return (
        <Form
            noValidate
            onSubmit={handleSubmit}
            className="
                d-flex flex-column 
                gap-2 
            ">
            <ValidationInput
                name="password"
                label={confirmInputPassword}
                maxLength={255}
                disabled={isSubmitting}
                type="password"
                validator={validate.password}
                setIsValidated={setIsValidPassword}
            />
            <ValidationButton
                isSubmitted={isSubmitted}
                isSubmitting={isSubmitting}
                isDisabled={isSubmitting || isSubmitted || !isFormValid}
                isFormValidated={isFormValid}
                text={confirmButtonConfirm}
            />
        </Form>
    );
};

export default ConfirmForm;
