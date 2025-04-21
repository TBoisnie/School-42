import React, { useMemo } from 'react';
import ValidationInput from '../../../common/ValidationInput';
import { email as emailValidator } from '../../../../utilities/Validators';
import { useTranslation } from 'react-i18next';

interface EmailInputProps {
    disabled: boolean;
    setIsValidated: (isValidated: boolean) => void;
}

const Email: React.FC<EmailInputProps> = ({
    disabled,
    setIsValidated
}) => {

    const { t } = useTranslation();

    const emailTranslation = useMemo(() => t('register.input.email'), [t]);

    return (
        <ValidationInput
            name={'email'}
            type='email'
            label={emailTranslation}
            maxLength={255}
            disabled={disabled}
            validator={emailValidator}
            setIsValidated={setIsValidated}
        />
    );
};

export default Email;
