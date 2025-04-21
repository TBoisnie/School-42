import React, { useMemo } from 'react';
import ValidationInput from '../../../common/ValidationInput';
import { password as passwordValidator } from '../../../../utilities/Validators';
import { useTranslation } from 'react-i18next';

interface PasswordInputProps {
    disabled: boolean;
    setIsValidated: (isValidated: boolean) => void;
}

const Password: React.FC<PasswordInputProps> = ({
    disabled,
    setIsValidated
}) => {

    const { t } = useTranslation();

    const passwordTranslation = useMemo(() => t('register.input.password'), [t]);

    return (
        <ValidationInput
            name={'password'}
            type='password'
            label={passwordTranslation}
            maxLength={20}
            disabled={disabled}
            validator={passwordValidator}
            setIsValidated={setIsValidated}
        />
    );
};

export default Password;
