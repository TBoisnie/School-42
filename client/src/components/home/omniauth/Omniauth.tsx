import React from 'react';
import { Stack } from 'react-bootstrap';
import OAuthButton from './buttons/Redirect';

const href1 = '/api/oauth/google/authorize';
const href2 = '/api/oauth/42/authorize';
const href3 = '/api/oauth/github/authorize';
const imgSrc1 = '/assets/google-logo.png';
const imgSrc2 = '/assets/42-logo.png';
const imgSrc3 = '/assets/github-logo.png';
const imgAlt1 = 'Google';
const imgAlt2 = '42';
const imgAlt3 = 'Github';

const Omniauth: React.FC = () => {

    return (
        <Stack
            direction="horizontal"
            gap={2}
        >
            <OAuthButton
                href={href1}
                imgSrc={imgSrc1}
                imgAlt={imgAlt1}
            />
            <OAuthButton
                href={href2}
                imgSrc={imgSrc2}
                imgAlt={imgAlt2}
            />
            <OAuthButton
                href={href3}
                imgSrc={imgSrc3}
                imgAlt={imgAlt3}
            />
        </Stack>
    );
};

export default Omniauth;