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

const Email: React.FC<Props> = ({
    defaultValue,
    setIsValidated,
    isSubmitting,
    isSubmitted,
}) => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const labelTranslation = useMemo(() => t('profile.input.email'), [t]);

    return (
        <ValidationInput
            name="email"
            label={labelTranslation}
            maxLength={255}
            disabled={isSubmitting || isSubmitted}
            type="email"
            validator={validate.email}
            setIsValidated={setIsValidated}
            defaultValue={defaultValue}
        />
    );
};

export default Email;
