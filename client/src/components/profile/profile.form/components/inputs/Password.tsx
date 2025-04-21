import React, { useMemo } from 'react';
import ValidationInput from '../../../../common/ValidationInput';
import * as validate from '../../../../../utilities/Validators';
import { useTranslation } from 'react-i18next';

interface Props {
    defaultValue: string;
    setIsValidated: (isValid: boolean) => void;
    isSubmitting: boolean;
    isSubmitted: boolean;
}

const Password: React.FC<Props> = ({
    defaultValue,
    setIsValidated,
    isSubmitting,
    isSubmitted,
}) => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const labelTranslation = useMemo(() => t('profile.input.password'), [t]);

    return (
        <ValidationInput
            name="password"
            label={labelTranslation}
            maxLength={64}
            disabled={isSubmitting || isSubmitted}
            type="password"
            validator={validate.password}
            setIsValidated={setIsValidated}
            defaultValue={defaultValue}
        />
    );
};

export default Password;
