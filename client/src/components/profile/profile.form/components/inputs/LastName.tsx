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

const LastName: React.FC<Props> = ({
    defaultValue,
    setIsValidated,
    isSubmitting,
    isSubmitted,
}) => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const labelTranslation = useMemo(() => t('profile.input.lastname'), [t]);

    return (
        <ValidationInput
            name="lastName"
            label={labelTranslation}
            maxLength={50}
            disabled={isSubmitting || isSubmitted}
            type="text"
            validator={validate.lastName}
            setIsValidated={setIsValidated}
            defaultValue={defaultValue}
        />
    );
};

export default LastName;
