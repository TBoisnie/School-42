import React, { useMemo } from 'react';
import { Container, Stack } from 'react-bootstrap';
import Header from '../common/Header';
import RegisterForm from './components/RegisterForm';
import { useTranslation } from 'react-i18next';

const Register: React.FC = () => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const registerHeaderHeader = useMemo(() => t('register.header.header'), [t]);
    const registerHeaderParagraph = useMemo(() => t('register.header.paragraph'), [t]);

    return (
        <Container
            
            className="align-self-center"
        >
                <Header
                    header={registerHeaderHeader}
                    paragraph={registerHeaderParagraph}
                />
                <RegisterForm />
        </Container>
    );
};

export default Register;