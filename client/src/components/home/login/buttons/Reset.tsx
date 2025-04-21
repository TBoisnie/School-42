import React, { useCallback, useMemo } from 'react';
import { Button } from 'react-bootstrap';
import { useTranslation } from 'react-i18next';
import { useNavigate } from 'react-router-dom';

const Reset: React.FC = () => {

    // 5. useCustom
    const { t } = useTranslation();
    const navigate = useNavigate();

    // 6. useCallback / useMemo
    const resetTranslated = useMemo(() => t('login.button.reset'), [t]);

    // 7. Event handlers
    const handleNavigateReset = useCallback(() => {
        navigate('/auth/reset');
    }, []);

    return (
        <Button
            variant="link"
            className="align-self-center"
            onClick={handleNavigateReset}
        >
            {resetTranslated}
        </Button>
    );
};

export default Reset;