import React, { useCallback, useMemo, useState } from 'react';
import { Form, Stack } from 'react-bootstrap';
import Email from './components/inputs/Email';
import Password from './components/inputs/Password';
import Username from './components/inputs/Username';
import FirstName from './components/inputs/FirstName';
import LastName from './components/inputs/LastName';
import Update from './components/buttons/Update';
import Picture from './components/inputs/Picture';
import Response from './components/modals/Response';

interface ProfileDeleteProps {
    userData: {
        id: number;
        username: string;
        firstName: string;
        lastName: string;
        email: string;
        picture: string;
    }
}

const ProfileForm: React.FC<ProfileDeleteProps> = ({ userData }) => {

    const [isEmailValidated, setIsEmailValidated] = useState<boolean>(true);
    const [isUsernameValidated, setIsUsernameValidated] = useState<boolean>(true);
    const [isFirstNameValidated, setIsFirstNameValidated] = useState<boolean>(true);
    const [isLastNameValidated, setIsLastNameValidated] = useState<boolean>(true);
    const [isPasswordValidated, setIsPasswordValidated] = useState<boolean>(true);
    const [isSubmitting, setIsSubmitting] = useState<boolean>(false);
    const [isSubmitted, setIsSubmitted] = useState<boolean>(false);
    const [serverResponse, setServerResponse] = useState<string | null>(null);
    const [imageCompressed, setCompressedImage] = useState<File | null>(null);

    const isFormValidated = useMemo(() => {
        return isUsernameValidated && isFirstNameValidated && isLastNameValidated && isPasswordValidated && isEmailValidated;
    }, [isUsernameValidated, isFirstNameValidated, isLastNameValidated, isPasswordValidated, isEmailValidated]);

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
            setIsSubmitting(true);
            if (!formObject.password) {
                delete formObject.password;
            }
            if (imageCompressed) {
                const arrayBufferToBase64 = (buffer: ArrayBuffer): string => {
                    let binary = '';
                    const bytes = new Uint8Array(buffer);
                    const len = bytes.byteLength;
                    for (let i = 0; i < len; i++) {
                        binary += String.fromCharCode(bytes[i]);
                    }
                    return btoa(binary);
                };
                const arrayBuffer = await imageCompressed.arrayBuffer();
                formObject['picture'] = arrayBufferToBase64(arrayBuffer);
            }
            const response = await fetch(`/api/users/${userData.id}`, {
                method: 'PATCH',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(formObject),
            });
            setIsSubmitting(false);
            setIsSubmitted(true);
            if (!response.ok) {
                const message = (await response.json()).message;
                setServerResponse(message);
            } else {
                setServerResponse(null);
                const passwordInput = form.querySelector('input[name="password"]') as HTMLInputElement | null;
                if (passwordInput) {
                    passwordInput.value = '';
                }
            }
        }
    }, [isFormValidated, userData, imageCompressed]);

    return (
        <>
            <Form
                noValidate
                onSubmit={handleSubmit}
                className="
                    d-flex flex-column justify-content-center
                    gap-2  
                    ">
                <Stack direction="horizontal" gap={2} >
                <Picture
                    setCompressedImage={setCompressedImage}
                    defautImage={userData.picture}
                />
                                <Stack direction="vertical" gap={2} >

                                <Username
                    defaultValue={userData.username}
                    setIsValidated={setIsUsernameValidated}
                    isSubmitting={isSubmitting}
                    isSubmitted={isSubmitted}
                />
                                <Email
                    defaultValue={userData.email}
                    setIsValidated={setIsEmailValidated}
                    isSubmitting={isSubmitting}
                    isSubmitted={isSubmitted}
                />
                </Stack>
                </Stack>

                <Password
                    setIsValidated={setIsPasswordValidated}
                    isSubmitting={isSubmitting}
                    isSubmitted={isSubmitted}
                    defaultValue={''}
                />

                <FirstName
                    defaultValue={userData.firstName}
                    setIsValidated={setIsFirstNameValidated}
                    isSubmitting={isSubmitting}
                    isSubmitted={isSubmitted}
                />
                <LastName
                    defaultValue={userData.lastName}
                    setIsValidated={setIsLastNameValidated}
                    isSubmitting={isSubmitting}
                    isSubmitted={isSubmitted}
                />

                <Update
                    isSubmitting={isSubmitting}
                    isSubmitted={isSubmitted}
                    isFormValidated={isFormValidated}
                    serverResponse={serverResponse}
                />
            </Form>
            <Response
                serverResponse={serverResponse}
                isSubmitted={isSubmitted}
                setIsSubmitted={setIsSubmitted}
                setServerResponse={setServerResponse}
            />
        </>
    );
};

export default ProfileForm;