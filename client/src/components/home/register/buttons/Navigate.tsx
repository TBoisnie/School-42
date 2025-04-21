import React, { useCallback, useMemo } from 'react';
import { Button } from 'react-bootstrap';
import { useTranslation } from 'react-i18next';
import { useNavigate } from 'react-router-dom';

const Navigate: React.FC = () => {

    // 5. useCustom
    const navigate = useNavigate();
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const loginButtonRegister = useMemo(() => t('login.button.register'), [t]);

    // 7. Event handlers
    const handleOnClick = useCallback(() => {
        navigate('/auth/register');
    }, [navigate]);

    return (
        <Button
            variant="primary"
            className="w-100"
            onClick={handleOnClick}
        >
            {loginButtonRegister}
        </Button>
    );
};

export default Navigate;