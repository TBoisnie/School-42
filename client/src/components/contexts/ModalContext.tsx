import React, { createContext, useContext, useState, ReactNode, useCallback, useMemo, useEffect } from 'react';
import { Modal, Button, Stack } from 'react-bootstrap';

interface ModalContextType {
    showModal: (
        onHide: () => void,
        isSuccess: boolean,
        successHeader: string,
        successParagraph: string,
        errorHeader: string,
        errorParagraph: string
    ) => void;
    hideModal: () => void;
    showConfirmBox: (
        onHide: () => void,
        header: string,
        onAccept: () => void,
        onRefuse: () => void,
    ) => void;
}

const ModalContext = createContext<ModalContextType | undefined>(undefined);

export const ModalProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
    const [isVisible, setIsVisible] = useState(false);
    const [isSuccess, setIsSuccess] = useState(false);
    const [successHeader, setSuccessHeader] = useState('');
    const [successParagraph, setSuccessParagraph] = useState('');
    const [errorHeader, setErrorHeader] = useState('');
    const [errorParagraph, setErrorParagraph] = useState('');
    const [customOnHide, setCustomOnHide] = useState<(() => void) | null>(null);
    const [isConfirmBox, setIsConfirmBox] = useState(false);
    const [confirmBoxHeader, setConfirmBoxHeader] = useState('');
    const [onAccept, setOnAccept] = useState<(() => void) | null>(null);
    const [onRefuse, setOnRefuse] = useState<(() => void) | null>(null);

    const showModal = useCallback((
        onHide: () => void,
        isSuccess: boolean,
        successHeader: string,
        successParagraph: string,
        errorHeader: string,
        errorParagraph: string,
    ) => {
        setCustomOnHide(() => onHide);
        setIsSuccess(isSuccess);
        setSuccessHeader(successHeader);
        setSuccessParagraph(successParagraph);
        setErrorHeader(errorHeader);
        setErrorParagraph(errorParagraph);

        setIsConfirmBox(false);
        setIsVisible(true);
    }, []);

    const showConfirmBox = useCallback((
        onHide: () => void,
        header: string,
        onAccept: () => void,
        onRefuse: () => void
    ) => {
        setCustomOnHide(() => onHide);
        setConfirmBoxHeader(header);
        setOnAccept(() => onAccept);
        setOnRefuse(() => onRefuse);

        setIsConfirmBox(true);
        setIsVisible(true);
    }, []);

    const hideModal = useCallback((e?: React.MouseEvent) => {
        if (e) {
            e.stopPropagation();
        }
        if (customOnHide) {
            customOnHide();
        }
        setIsVisible(false);
    }, [customOnHide]);

    const handleOnAccept = useCallback(() => {
        setIsVisible(false);
        setTimeout(() => {
            setIsConfirmBox(false);
            if (onAccept) {
                onAccept();
            }
        }, 300);
    }, [onAccept]);

    const handleOnRefuse = useCallback(() => {
        setIsVisible(false);
        setTimeout(() => {
            setIsConfirmBox(false);
            if (onRefuse) {
                onRefuse();
            }
        }, 300);
    }, [onRefuse]);

    const handleColor = useMemo(() => {
        if (isConfirmBox) {
            return 'bg-dark text-light border-dark';
        }
        return isSuccess ? 'bg-dark text-success border-success' : 'bg-dark text-danger border-danger';
    }, [isSuccess, isConfirmBox]);

    return (
        <ModalContext.Provider value={{ showModal, hideModal, showConfirmBox }} >
            {children}
            <Modal
                show={isVisible}
                onHide={hideModal}
                onClick={isConfirmBox ? undefined : hideModal}
                centered
            >
                <Modal.Body className={`text-center border rounded border-2 ${handleColor}`}>
                    {isConfirmBox ? (
                        <Stack direction="vertical" gap={3}>
                            {confirmBoxHeader}
                            <Stack direction="horizontal" gap={3}>
                                <Button variant="primary w-100" onClick={handleOnAccept}>
                                    ✓
                                </Button>
                                <Button variant="secondary w-100" onClick={handleOnRefuse}>
                                    𐄂
                                </Button>
                            </Stack>
                        </Stack>
                    ) : (
                        isSuccess ? (
                            <div>
                                <h6>{successHeader}</h6>
                                {successParagraph}
                            </div>
                        ) : (
                            <div>
                                <h6>{errorHeader}</h6>
                                {errorParagraph}
                            </div>
                        )
                    )}
                </Modal.Body>
            </Modal>
        </ModalContext.Provider>
    );
};

export const useModal = () => {
    const context = useContext(ModalContext);
    if (context === undefined) {
        throw new Error('useModal must be used within a ModalProvider');
    }
    return context;
};