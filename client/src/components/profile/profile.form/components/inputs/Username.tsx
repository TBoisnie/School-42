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

const Username: React.FC<Props> = ({
    defaultValue,
    setIsValidated,
    isSubmitting,
    isSubmitted,
}) => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const labelTranslation = useMemo(() => t('profile.input.username'), [t]);

    return (
        <ValidationInput
            name="username"
            label={labelTranslation}
            maxLength={20}
            disabled={isSubmitting || isSubmitted}
            type="text"
            validator={validate.username}
            setIsValidated={setIsValidated}
            defaultValue={defaultValue}
        />
    );
};

export default Username;
