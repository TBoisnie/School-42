// composant to reset password
import React, { useMemo } from 'react';
import { Container } from 'react-bootstrap';
import { useTranslation } from 'react-i18next';
import Header from '../common/Header';
import ResetForm from './composants/ResetForm';

const Reset: React.FC = () => {

    // 5. useCustom
    const { t } = useTranslation();

    // 7. useCallBack / useMemo
    const header = useMemo(() => t('reset.header.header'), [t]);
    const paragraph = useMemo(() => t('reset.header.paragraph'), [t]);

    return (
        <Container 
            className="align-self-center"
        >
            <Header header={header} paragraph={paragraph} />
            <ResetForm />
        </Container>
    );
};

export default Reset;