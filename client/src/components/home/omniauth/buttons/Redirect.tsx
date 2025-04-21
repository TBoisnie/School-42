import React, { useCallback } from 'react';
import { Button, Image } from 'react-bootstrap';

interface Props {
    href: string;
    imgSrc: string;
    imgAlt: string;
}

const Redirect: React.FC<Props> = ({ href, imgSrc, imgAlt }) => {

    // 7. Event handlers
    const handleOnClick = useCallback((url: string) => {
        return () => {
            window.location.href = url;
        }
    }, []);

    return (
        <Button
            variant="light"
            className='w-100 d-flex justify-content-center align-items-center'
            onClick={handleOnClick(href)}
        >
            <Image
                src={imgSrc}
                alt={imgAlt}
                style={{ height: '2.25em' }}
            />
        </Button>
    );
};

export default Redirect;