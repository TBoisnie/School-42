// composant to confirm password
import React, { useMemo } from 'react';
import { Container } from 'react-bootstrap';
import { useTranslation } from 'react-i18next';
import Header from '../common/Header';
import ConfirmForm from './composants/ConfirmForm';

const Confirm: React.FC = () => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const confirmHeaderHeader = useMemo(() => t('confirm.header.header'), [t]);
    const confirmHeaderParagraph = useMemo(() => t('confirm.header.paragraph'), [t]);

    return (
        <Container fluid className="d-flex flex-column justify-content-center gap-3 ">
            <Header header={confirmHeaderHeader} paragraph={confirmHeaderParagraph} />
            <ConfirmForm />
        </Container>
    );
};

export default Confirm;
