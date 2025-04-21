import React from 'react';
import { Container, Stack } from 'react-bootstrap';
import Username from './inputs/Username';
import FirstName from './inputs/FirstName';
import LastName from './inputs/LastName';
import Picture from './inputs/Picture';

interface Props {
    userData: {
        username: string;
        firstName: string;
        lastName: string;
        picture: string;
    }
}

const DetailStack: React.FC<Props> = ({ userData }) => {

    return (
            <Stack direction="horizontal" gap={2}>
<div className='rounded-2 d-flex justify-content-center align-items-center'
            style={{ width: '12rem', height: '12rem', overflow: 'hidden' }}>
                        <Picture
                defautImage={userData.picture}
            />
            </div>
            <Stack direction="vertical" gap={2}>
            <Username
                defaultValue={userData.username}
            />
            <FirstName
                defaultValue={userData.firstName}
            />
            <LastName
                defaultValue={userData.lastName}
            />
            </Stack>

        </Stack>
    );
};

export default DetailStack;