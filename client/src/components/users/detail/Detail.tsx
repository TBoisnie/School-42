import React, { useEffect, useMemo, useState } from 'react';
import { Container } from 'react-bootstrap';
import { useParams } from 'react-router-dom';
import Header from '../../common/Header';
import DetailStack from './stack/DetailStack';
import { useTranslation } from 'react-i18next';

const Detail: React.FC = () => {

    // 1. useState
    const [userData, setUserData] = useState({
        username: '',
        firstName: '',
        lastName: '',
        picture: '',
    });
    const [isLoading, setIsLoading] = useState(true);

    // 2. useParams
    const { id } = useParams<{ id: string }>();

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const headerTranslation = useMemo(() => t('detail.header.header'), [t]);
    const paragraphTranslation = useMemo(() => t('detail.header.paragraph'), [t]);

    // 8. useEffect
    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await fetch(`/api/users/${id}`);
                const data = await response.json();
                setUserData(data);
                setIsLoading(false);
            } catch (error) {
                console.error('Error fetching user data:', error);
            }
        };
        fetchData();
    }, [id]);

    return (
        <Container
            fluid
            className="align-self-center"
        >
            <Header
                header={headerTranslation}
                paragraph={paragraphTranslation}
            />
            <DetailStack
                userData={userData}
            />
        </Container>
    );
};

export default Detail;