import React, { useEffect, useMemo, useState } from 'react';
import { Container, Stack } from 'react-bootstrap';
import Header from '../common/Header';
import { useTranslation } from 'react-i18next';
import { useNavigate } from 'react-router-dom';

const Users: React.FC = () => {
    // 1. useState
    const [usersData, setUsersData] = useState([]);
    const [isLoading, setIsLoading] = useState(true);

    // 5. useCustom
    const { t } = useTranslation();
    const navigate = useNavigate();

    // 6. useCallback / useMemo
    const headerTranslation = useMemo(() => t('users.header.header'), [t]);
    const paragraphTranslation = useMemo(() => t('users.header.paragraph'), [t]);

    // 8. useEffect
    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await fetch('/api/users');
                const data = await response.json();
                setUsersData(data);
                setIsLoading(false);
            } catch (error) {
                console.error('Error fetching users data:', error);
            }
        };
        fetchData();
    }, []);

    if (!usersData) {
        return (
            <Container fluid className="w-100 h-100 d-flex justify-content-center align-items-center">
                No users found.
            </Container>
        );
    }

    return (
        <Container fluid className="d-flex flex-column gap-3  align-self-center">
            <Header header={headerTranslation} paragraph={paragraphTranslation} />
            <Stack direction="vertical" gap={2}>
                {usersData.map((user: any) => (
                    <div
                        key={user.id}
                        className="
                        d-flex align-items-center 
                        gap-3 
                        bg-light text-dark rounded p-2   
                        "
                        onClick={() => navigate(`/users/${user.id}`)}
                        style={{ cursor: 'pointer' }}
                    >
                        {user.id}
                        <img
                            src={user.picture}
                            className="rounded-circle"
                            style={{ width: '3rem', height: '3rem' }}
                        />
                        {user.username} - {user.firstName} {user.lastName}
                    </div>
                ))}
            </Stack>
        </Container>
    )
};

export default Users;
