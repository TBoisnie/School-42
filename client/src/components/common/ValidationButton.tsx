import React, { useMemo } from 'react';
import { Button } from 'react-bootstrap';
import { useTranslation } from 'react-i18next';

interface ValidationButtonProps {
    isSubmitted: boolean;
    isSubmitting: boolean;
    isDisabled: boolean;
    isFormValidated?: boolean;
    text?: string;
    type?: 'submit' | 'button';
    className?: string;
    onClick?: () => Promise<void>
}

const ValidationButton: React.FC<ValidationButtonProps> = ({
    isSubmitted,
    isSubmitting,
    isDisabled,
    isFormValidated = true,
    text,
    type = 'submit',
    className = '',
    onClick,
}) => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const buttonValidationSubmit = useMemo(() => t('button.validation.submit'), [t]);
    const buttonValidationSubmitting = useMemo(() => t('button.validation.submitting'), [t]);
    const buttonValidationSubmitted = useMemo(() => t('button.validation.submitted'), [t]);
    const buttonValidationFailed = useMemo(() => t('button.validation.failed'), [t]);
    
    const buttonColor = useMemo(() => {
        if (isSubmitted) {
            if (!isFormValidated) return 'danger';
            return 'success';
        }
        return 'primary';
    }, [isSubmitted, isFormValidated]);

    const buttonText = useMemo(() => {
        if (isSubmitting) return buttonValidationSubmitting;
        if (isSubmitted) {
            if (isFormValidated) return buttonValidationSubmitted;
            return buttonValidationFailed;
        }
        return text || buttonValidationSubmit;
    }, [isSubmitting, isSubmitted, isFormValidated, text, buttonValidationSubmit, buttonValidationSubmitting, buttonValidationSubmitted, buttonValidationFailed]);

    return (
        <Button
            type={type}
            disabled={isDisabled}
            variant={buttonColor}
            className={className}
            onClick={onClick}
        >
            {buttonText}
        </Button>
    );
};

export default ValidationButton;
