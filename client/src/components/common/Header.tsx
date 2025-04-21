

import React from 'react';
import { Stack } from 'react-bootstrap';

interface HeaderProps {
    header: string;
    paragraph: string;
    className?: string;
}

const Header: React.FC<HeaderProps> = ({
    header,
    paragraph,
    className
}) => {

    return (
        <div
            className={`
                justify-content-center text-center 
                ${className}
            `}>
            <h2>
                {header}
            </h2>
            <div>
                <p style={{ whiteSpace: 'pre-wrap' }}>
                    {paragraph}
                </p>
            </div>
        </div>
    );
};

export default Header;