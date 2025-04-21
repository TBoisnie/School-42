import React, { useState, useMemo, useEffect } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import { useTranslation } from 'react-i18next';
import { useModal } from '../contexts/ModalContext';
import { useAuth } from '../contexts/AuthContext';

const Response: React.FC = () => {

    // 1. useState
    const [code, setCode] = useState('');

    // 3. useContext
    const { showModal } = useModal();

    // 5. useCustom
    const { t } = useTranslation();
    const location = useLocation();
    const navigate = useNavigate();
    const { isAuthenticated, setIsAuthenticated } = useAuth();

    // 6. useCallback / useMemo
    const provider = useMemo(() => {
        if (location.pathname.includes('42')) {
            return '42';
        } else if (location.pathname.includes('google')) {
            return 'google';
        } else if (location.pathname.includes('github')) {
            return 'github';
        } else {
            return '';
        }
    }, [location.pathname]);
    const successHeaderTranslation = useMemo(() => {
        if (provider === '42') {
            return t('oauth.42.modal.success.header');
        } else if (provider === 'google') {
            return t('oauth.google.modal.success.header');
        } else if (provider === 'github') {
            return t('oauth.github.modal.success.header');
        } else {
            return '';
        }
    }, [provider, t]);
    const successParagraphTranslation = useMemo(() => {
        if (provider === '42') {
            return t('oauth.42.modal.success.paragraph');
        } else if (provider === 'google') {
            return t('oauth.google.modal.success.paragraph');
        } else if (provider === 'github') {
            return t('oauth.github.modal.success.paragraph');
        } else {
            return '';
        }
    }, [provider, t]);
    const errorHeaderTranslation = useMemo(() => {
        return t('oauth.modal.error.header');
    }, [t]);
    const errorParagraphTranslation = useMemo(() => {
        return t('oauth.modal.error.paragraph');
    }, [t]);

    // 8. useEffect
    useEffect(() => {
        setCode('');
        const fetchData = async () => {
            const queryParams = new URLSearchParams(location.search);
            if (queryParams) {
                const code = queryParams.get('code');
                if (code) {
                    const url = `/api/oauth/${provider}/callback?code=${code}`;
                    const response = await fetch(url, {
                        method: 'GET',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                    });
                    if (response.ok) {
                        setCode(code);
                        setIsAuthenticated(true);
                    }
                }
            }
        };
        fetchData();
    }, [location.search, provider]);

    useEffect(() => {
        if (code) {
            showModal(
                () => navigate('/'),
                isAuthenticated,
                successHeaderTranslation,
                successParagraphTranslation,
                errorHeaderTranslation,
                errorParagraphTranslation
            );
        }
    }, [
        code,
        successHeaderTranslation,
        successParagraphTranslation,
        errorHeaderTranslation,
        errorParagraphTranslation
    ]);

    return null;
};

export default Response;