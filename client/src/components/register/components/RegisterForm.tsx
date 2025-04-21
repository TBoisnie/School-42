import React, { useCallback, useEffect, useMemo, useState } from 'react';
import { useNavigate } from 'react-router-dom';
import ValidationInput from '../../common/ValidationInput';
import ValidationButton from '../../common/ValidationButton';
import { Form } from 'react-bootstrap';
import { useTranslation } from 'react-i18next';
import * as validate from '../../../utilities/Validators';
import { useModal } from '../../contexts/ModalContext';

const RegisterForm: React.FC = () => {

    // 1. useState
    const [isUsernameValidated, setIsUsernameValidated] = useState<boolean>(false);
    const [isFirstNameValidated, setIsFirstNameValidated] = useState<boolean>(false);
    const [isLastNameValidated, setIsLastNameValidated] = useState<boolean>(false);
    const [isEmailValidated, setIsEmailValidated] = useState<boolean>(false);
    const [isPasswordValidated, setIsPasswordValidated] = useState<boolean>(false);
    const [isSubmitting, setIsSubmitting] = useState<boolean>(false);
    const [isSubmitted, setIsSubmitted] = useState<boolean>(false);
    const [serverResponse, setServerResponse] = useState<string | null>(null);

    // 5. useCustom
    const { t } = useTranslation();
    const navigate = useNavigate();
    const { showModal } = useModal();

    // 6. useCallback / useMemo
    const username = useMemo(() => t('register.input.username'), [t]);
    const firstName = useMemo(() => t('register.input.firstname'), [t]);
    const lastName = useMemo(() => t('register.input.lastname'), [t]);
    const email = useMemo(() => t('register.input.email'), [t]);
    const password = useMemo(() => t('register.input.password'), [t]);

    const buttonRegister = useMemo(() => t('register.button.register'), [t]);

    const modalSuccessHeader = useMemo(() => t('register.modal.success.header'), [t]);
    const modalSuccessParagraph = useMemo(() => t('register.modal.success.paragraph'), [t]);
    const modalErrorHeader = useMemo(() => t('register.modal.error.header'), [t]);
    const modalErrorParagraph = useMemo(() => {
        if (serverResponse) {
            return t(`register.modal.error.paragraph.${serverResponse}`);
        }
        return '';
    }, [t, serverResponse]);

    const isFormValidated = useMemo(() => {
        return isUsernameValidated && isFirstNameValidated && isLastNameValidated && isEmailValidated && isPasswordValidated;
    }, [isUsernameValidated, isFirstNameValidated, isLastNameValidated, isEmailValidated, isPasswordValidated]);

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
                const response = await fetch('/api/users', {
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
                    if (message === 'User already exists') {
                        const emailInput = form.querySelector('input[name="email"]') as HTMLInputElement | null;
                        if (emailInput) {
                            emailInput.value = '';
                        }
                        setIsEmailValidated(false);
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
        setTimeout(() => {
            setIsSubmitted(false);
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
            className=" 
                    d-flex flex-column
                    gap-2
                    ">
            <ValidationInput
                name={'email'}
                label={email}
                maxLength={255}
                disabled={isSubmitting || isSubmitted}
                type='email'
                validator={validate.email}
                setIsValidated={setIsEmailValidated}
            />
            <ValidationInput
                name={'password'}
                label={password}
                maxLength={20}
                disabled={isSubmitting || isSubmitted}
                type='password'
                validator={validate.password}
                setIsValidated={setIsPasswordValidated}
            />
            <ValidationInput
                name={'username'}
                label={username}
                maxLength={255}
                disabled={isSubmitting || isSubmitted}
                validator={validate.username}
                setIsValidated={setIsUsernameValidated}
            />
            <ValidationInput
                name={'firstName'}
                label={firstName}
                maxLength={255}
                disabled={isSubmitting || isSubmitted}
                validator={validate.firstName}
                setIsValidated={setIsFirstNameValidated}
            />
            <ValidationInput
                name={'lastName'}
                label={lastName}
                maxLength={255}
                disabled={isSubmitting || isSubmitted}
                validator={validate.lastName}
                setIsValidated={setIsLastNameValidated}
            />
            <ValidationButton
                isSubmitting={isSubmitting}
                isSubmitted={isSubmitted}
                isDisabled={isSubmitting || isSubmitted || !isFormValidated}
                isFormValidated={isFormValidated}
                text={buttonRegister}
            />
        </Form>
    );
};

export default RegisterForm;
