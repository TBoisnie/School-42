import React, { useCallback, useState } from 'react';
import { FloatingLabel, Form } from 'react-bootstrap';

interface ValidationInputProps {
    name: string;
    label: string;
    maxLength?: number;
    disabled: boolean;
    type?: string;
    className?: string;
    validator: (value: string) => string | null;
    setIsValidated: (value: boolean) => void;
    defaultValue?: string;
}

const ValidationInput: React.FC<ValidationInputProps> = ({
    name,
    label,
    maxLength = 255,
    disabled,
    type = 'text',
    className = '',
    validator,
    setIsValidated,
    defaultValue = '',
}) => {

    // 1. State
    const [error, setError] = useState<string | null>(null);
    const [isInvalid, setIsInvalid] = useState<boolean>(false);
    const [isValid, setIsValid] = useState<boolean>(false);
    const [isFocused, setIsFocused] = useState<boolean>(false);

    // 7. Event handlers
    const handleOnChange = useCallback((e: React.ChangeEvent<HTMLInputElement>) => {
        const value = e.target.value;
        const error = validator(value);
        setError(error);
        setIsValidated(!error);
        setIsInvalid(!!error);
        setIsValid(!error);
    }, []);
    const handleOnFocus = useCallback(() => {
        setIsFocused(true);
    }, []);
    const handleOnBlur = useCallback(() => {
        setIsFocused(false);
        setIsValid(false);
    }, []);

    return (
        <Form.Group className={className}>
            <FloatingLabel
                label={label}
                className="text-dark"
            >
                <Form.Control
                    name={name}
                    type={type}
                    placeholder={label}
                    maxLength={maxLength}
                    disabled={disabled}
                    isInvalid={isInvalid}
                    isValid={isValid}
                    onChange={handleOnChange}
                    onFocus={handleOnFocus}
                    onBlur={handleOnBlur}
                    defaultValue={defaultValue}
                    autoComplete="one-time-code"
                    autoCorrect="off"
                    autoCapitalize="off"
                    className={`${className}`}
                />
                {(isFocused && !!error) && (
                    <Form.Control.Feedback type="invalid">
                        {error}
                    </Form.Control.Feedback>
                )}
            </FloatingLabel>
        </Form.Group>
    );
};

export default ValidationInput;
