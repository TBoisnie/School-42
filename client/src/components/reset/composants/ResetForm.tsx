import React, { useCallback, useEffect, useMemo, useState } from 'react';
import { useNavigate } from 'react-router-dom';
import ValidationInput from '../../common/ValidationInput';
import ValidationButton from '../../common/ValidationButton';
import { Form } from 'react-bootstrap';
import { useTranslation } from 'react-i18next';
import * as validate from '../../../utilities/Validators';
import { useModal } from '../../contexts/ModalContext';

const ResetForm: React.FC = () => {

    // 1. useState
    const [isValidEmail, setIsValidEmail] = useState<boolean>(false);
    const [isSubmitting, setIsSubmitting] = useState<boolean>(false);
    const [isSubmitted, setIsSubmitted] = useState<boolean>(false);
    const [serverResponse, setServerResponse] = useState<string | null>(null);

    // 5. useCustom
    const { t } = useTranslation();
    const navigate = useNavigate();
    const { showModal } = useModal();

    // 6. useCallback / useMemo
    const labelEmail = useMemo(() => t('reset.input.email'), [t]);
    const placeholderEmail = useMemo(() => t('reset.input.email'), [t]);

    const modalSuccessHeader = useMemo(() => t('reset.modal.success.header'), [t]);
    const modalSuccessParagraph = useMemo(() => t('reset.modal.success.paragraph'), [t]);
    const modalErrorHeader = useMemo(() => t('reset.modal.error.header'), [t]);
    const modalErrorParagraph = useMemo(() => {
        if (serverResponse) {
            return t(`reset.modal.error.paragraph.${serverResponse}`);
        }
        return '';
    }, [t, serverResponse]);

    const isFormValidated = useMemo(() => isValidEmail, [isValidEmail]);

    // 7. Event handlers
    const handleSubmit = useCallback(async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        e.stopPropagation();
        const form = e.currentTarget;
        if (form.checkValidity() === false) {
            return;
        }
        if (isFormValidated) {
            const formData = new FormData(form);
            const formObject = Object.fromEntries(formData.entries());
            try {
                setIsSubmitting(true);
                const response = await fetch('/api/auth/reset', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify(formObject),
                });
                setIsSubmitting(false);
                setIsSubmitted(true);
                if (!response.ok) {
                    const message = (await response.json()).message;
                    if (message === 'User not found') {
                        const emailInput = form.querySelector('input[name="email"]') as HTMLInputElement | null;
                        if (emailInput) {
                            emailInput.value = '';
                        }
                        setIsValidEmail(false);
                        setServerResponse('email');
                    } else {
                        setServerResponse('server');
                    }
                } else {
                    setServerResponse(null);
                }
            } catch (error) {
                setServerResponse('server');
                console.error(error);
            }
        }
    }, [isFormValidated]);

    const handleOnHide = useCallback(() => {
        setIsSubmitted(false);
        setTimeout(() => {
            if (!serverResponse) {
                navigate('/');
            }
        }, 300);
    }, [navigate, serverResponse]);

    // 8. useEffect
    useEffect(() => {
        if (isSubmitted) {
            showModal(
                handleOnHide,
                !serverResponse,
                modalSuccessHeader,
                modalSuccessParagraph,
                modalErrorHeader,
                modalErrorParagraph
            );
        }
    }, [isSubmitted, serverResponse]);

    return (
        <Form
            noValidate
            onSubmit={handleSubmit}
            className="d-flex flex-column gap-2"
        >
            <ValidationInput
                name={'email'}
                label={labelEmail}
                maxLength={255}
                disabled={isSubmitting || isSubmitted}
                type='email'
                validator={validate.email}
                setIsValidated={setIsValidEmail}
            />
            <ValidationButton
                type="submit"
                isSubmitting={isSubmitting}
                isSubmitted={isSubmitted}
                isDisabled={isSubmitting || isSubmitted || !isFormValidated}
                isFormValidated={isFormValidated}
            />
        </Form>
    );
};

export default ResetForm;
