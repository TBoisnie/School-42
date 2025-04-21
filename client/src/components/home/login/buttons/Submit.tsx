import React, { useMemo } from 'react';
import { useTranslation } from 'react-i18next';
import ValidationButton from '../../../common/ValidationButton';

interface SubmitButtonProps {
    isSubmitting: boolean;
    isSubmitted: boolean;
    isFormValidated: boolean;
}

const Submit: React.FC<SubmitButtonProps> = ({ 
    isSubmitting, 
    isSubmitted, 
    isFormValidated
 }) => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const loginTranslated = useMemo(() => t('login.button.login'), [t]);

    return (
        <ValidationButton
            isSubmitting={isSubmitting}
            isSubmitted={isSubmitted}
            isDisabled={isSubmitting || isSubmitted || !isFormValidated}
            isFormValidated={isFormValidated}
            text={loginTranslated}
            className="w-100 align-self-center"
        />
    );
};

export default Submit;