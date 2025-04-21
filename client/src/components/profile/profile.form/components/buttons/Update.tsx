import React, { useMemo } from 'react';
import ValidationButton from '../../../../common/ValidationButton';
import { useTranslation } from 'react-i18next';

interface Props {
    isSubmitting: boolean;
    isSubmitted: boolean;
    isFormValidated: boolean;
    serverResponse: string | null;
}

const Update: React.FC<Props> = ({
    isSubmitting,
    isSubmitted,
    isFormValidated,
    serverResponse
}) => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const updateTranslation = useMemo(() => t('profile.button.update'), [t]);

    return (
        <ValidationButton
            isSubmitting={isSubmitting}
            isSubmitted={isSubmitted}
            isDisabled={isSubmitting || isSubmitted || !isFormValidated}
            isFormValidated={!serverResponse}
            text={updateTranslation}
            className="w-100 align-self-center mt-3"
        />
    );
};

export default Update;