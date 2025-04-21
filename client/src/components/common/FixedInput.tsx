import React from 'react';
import { FloatingLabel, Form } from 'react-bootstrap';

interface ValidationInputProps {
    name: string;
    label: string;
    className?: string;
    defaultValue: string;
}

const FixedInput: React.FC<ValidationInputProps> = ({
    name,
    label,
    className = '',
    defaultValue,
}) => {

    return (
        <Form.Group className={className}>
            <FloatingLabel
                label={label}
            >
                <Form.Control
                    name={name}
                    type='text'
                    placeholder={label}
                    disabled 
                    defaultValue={defaultValue}
                    className={`${className} `}
                />
            </FloatingLabel>
        </Form.Group>
    );
};

export default FixedInput;
