import React from 'react';
import Picture from 'react-bootstrap/Image';

interface Props {
    defautImage: string | null;
}

const PictureInput: React.FC<Props> = ({
    defautImage
}) => {

    return (
        <Picture
            rounded
            src={defautImage || '/assets/default-picture.webp'}
            alt="Preview"
            className="w-100 aspect-ratio-1x1 object-fit-cover bg-light"
        />
    );
};

export default PictureInput;
