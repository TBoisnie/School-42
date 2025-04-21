import React, { useCallback, useMemo, useState } from 'react';
import { Form } from 'react-bootstrap';
import Email from './inputs/Email';
import Password from './inputs/Password';
import Submit from './buttons/Submit';
import Response from './response/Response';
import Reset from './buttons/Reset';

const Login: React.FC = () => {

    // 1. useState
    const [isEmailValidated, setIsEmailValidated] = useState<boolean>(false);
    const [isPasswordValidated, setIsPasswordValidated] = useState<boolean>(false);
    const [isSubmitting, setIsSubmitting] = useState<boolean>(false);
    const [isSubmitted, setIsSubmitted] = useState<boolean>(false);
    const [serverResponse, setServerResponse] = useState<string | null>(null);

    // 6. useCallback / useMemo
    const isFormValidated = useMemo(() => {
        return isEmailValidated && isPasswordValidated;
    }, [isEmailValidated, isPasswordValidated]);

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
                const response = await fetch('/api/auth/login', {
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
                    // Clear the password field if the error is related to the password
                    if (message === 'Invalid password') {
                        const passwordInput = form.querySelector('input[name="password"]') as HTMLInputElement | null;
                        if (passwordInput) {
                            passwordInput.value = '';
                        }
                        setIsPasswordValidated(false);
                        setServerResponse('password');
                        // Clear the email and password fields if the error is related to the email
                    } else if (message === 'Email not found') {
                        const emailInput = form.querySelector('input[name="email"]') as HTMLInputElement | null;
                        if (emailInput) {
                            emailInput.value = '';
                        }
                        const passwordInput = form.querySelector('input[name="password"]') as HTMLInputElement | null;
                        if (passwordInput) {
                            passwordInput.value = '';
                        }
                        setIsEmailValidated(false);
                        setIsPasswordValidated(false);
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

    return (
        <Form
            noValidate={true}
            onSubmit={handleSubmit}
            className="d-flex flex-column gap-2">
            <Email
                disabled={isSubmitting || isSubmitted}
                setIsValidated={setIsEmailValidated}
            />
            <Password
                disabled={isSubmitting || isSubmitted}
                setIsValidated={setIsPasswordValidated}
            />
            <Submit
                isSubmitting={isSubmitting}
                isSubmitted={isSubmitted}
                isFormValidated={!serverResponse && isFormValidated}
            />
            <Reset />
            <Response
                isSubmitted={isSubmitted}
                serverResponse={serverResponse}
                setIsSubmitted={setIsSubmitted}
                setServerResponse={setServerResponse}
            />
        </Form>
    );
};

export default Login;