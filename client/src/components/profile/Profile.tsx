import React, { useEffect, useMemo, useState } from 'react';
import { Col, Container, Row, Stack } from 'react-bootstrap';
import Header from '../common/Header';
import ProfileForm from './profile.form/ProfileForm';
import { useTranslation } from 'react-i18next';
import Delete from './profile.button/Delete';

const Profile: React.FC = () => {
    // 1. useState
    const [userData, setUserData] = useState({
        id: 0,
        username: '',
        email: '',
        firstName: '',
        lastName: '',
        picture: '',
    });

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const profileHeaderHeader = useMemo(() => t('profile.header.header'), [t]);
    const profileHeaderParagraph = useMemo(() => t('profile.header.paragraph'), [t]);

    // 8. useEffect
    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await fetch('/api/users/0');
                const data = await response.json();
                if ( data.picture ) {
                    data.picture += '?' + new Date().getTime();
                }
                setUserData(data);
                // console.log('User data:', data);
            } catch (error) {
                console.error('Error fetching user data:', error);
            }
        };
        fetchData();
    }, []);

    return (
        <Container className="align-self-center d-flex flex-column gap-3">
                <Header header={profileHeaderHeader} paragraph={profileHeaderParagraph} />
                <ProfileForm userData={userData} />
                <Delete userData={userData} />
        </Container>
    );
};

export default Profile;
