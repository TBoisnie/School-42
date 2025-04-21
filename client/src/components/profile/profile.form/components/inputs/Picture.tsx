import React, { useCallback, useEffect, useState } from 'react';
import { Form } from 'react-bootstrap';
import Picture from 'react-bootstrap/Image';
import imageCompression from 'browser-image-compression';

interface Props {
    setCompressedImage: (file: File) => void;
    defautImage: string | null;
}

const PictureInput: React.FC<Props> = ({
    setCompressedImage,
    defautImage
}) => {

    // 1. State
    const [imagePreview, setImagePreview] = useState<string | null>(null);

    // 7. Event handlers
    const handleFileChange = useCallback(async (event: React.ChangeEvent<HTMLInputElement>) => {
        const file = event.target.files?.[0];
        if (file) {
            //console.log(`Original file size: ${file.size / 1024} KB`);

            const img = new Image();
            img.src = URL.createObjectURL(file);

            img.onload = async () => {
                const canvas = document.createElement('canvas');
                const ctx = canvas.getContext('2d');
                const size = 128;

                let targetWidth, targetHeight;

                // Determine the dimensions for resizing
                if (img.width < img.height) {
                    targetWidth = size;
                    targetHeight = (img.height / img.width) * targetWidth; // Maintain aspect ratio
                } else {
                    targetHeight = size;
                    targetWidth = (img.width / img.height) * targetHeight; // Maintain aspect ratio
                }

                // Resize the image
                canvas.width = targetWidth;
                canvas.height = targetHeight;
                ctx?.drawImage(img, 0, 0, targetWidth, targetHeight);

                // Now, crop to 512x512
                const croppedCanvas = document.createElement('canvas');
                const croppedCtx = croppedCanvas.getContext('2d');
                croppedCanvas.width = size;
                croppedCanvas.height = size;

                // Calculate offsets for cropping
                const offsetX = (targetWidth - size) / 2;
                const offsetY = (targetHeight - size) / 2;

                if (croppedCtx) {
                    // Draw the centered crop on the new canvas
                    croppedCtx.drawImage(canvas, offsetX, offsetY, size, size, 0, 0, size, size);

                    // Convert the canvas to a WebP Blob and update the state
                    croppedCanvas.toBlob(async (blob) => {
                        if (blob) {
                            const webpBlob = await new Promise<Blob | null>((resolve) => {
                                const webpCanvas = document.createElement('canvas');
                                const webpCtx = webpCanvas.getContext('2d');
                                webpCanvas.width = size;
                                webpCanvas.height = size;
                                webpCtx?.drawImage(croppedCanvas, 0, 0, size, size);
                                webpCanvas.toBlob(resolve, 'image/webp');
                            });

                            if (webpBlob) {
                                const webpFile = new File([webpBlob], file.name.replace(/\.[^.]+$/, '.webp'), { type: 'image/webp' });
                                //console.log(`WebP file size: ${webpFile.size / 1024} KB`);
                                setImagePreview(URL.createObjectURL(webpFile));

                                // Compress the WebP image
                                const compressedFile = await imageCompression(webpFile, {
                                    maxSizeMB: 1,
                                    useWebWorker: true,
                                });
                                //console.log(`Compressed file size: ${compressedFile.size / 1024} KB`);
                                setCompressedImage(compressedFile);
                            }
                        }
                    }, 'image/webp');
                }
            };

            img.onerror = (error) => {
                //console.error("Error loading image", error);
            };
        }
    }, [setCompressedImage]);

    useEffect(() => {
        //console.log(imagePreview, defautImage);
    });

    return (
        <Form.Group controlId="picture" className='position-relative'
            style={{ 
                maxHeight: '100%', 
                maxWidth: '7.75rem',
                height: '100%',
            }}
        >
            <Form.Control
                type="file"
                accept="image/*"
                onChange={handleFileChange}
                className='cursor-pointer position-absolute opacity-0 h-100'
            />
            <Picture
                rounded
                src={imagePreview || defautImage || '/assets/default-picture.webp'}
                alt="Preview"
            />
        </Form.Group>
    );
};

export default PictureInput;
