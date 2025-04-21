import { IsOptional, IsString, Matches, Validate, ValidationArguments, ValidatorConstraint, ValidatorConstraintInterface } from 'class-validator';
import { fileTypeFromBuffer } from 'file-type';

@ValidatorConstraint({ name: 'isBase64Image', async: true })
class IsBase64ImageConstraint implements ValidatorConstraintInterface {
    async validate(base64: string, args: ValidationArguments): Promise<boolean> {
        const buffer = Buffer.from(base64, 'base64');
        const type = await fileTypeFromBuffer(buffer);

        if (type !== undefined && type.mime.startsWith('image/webp')) {
            return true;
        }

        return false;
    }

    defaultMessage(args: ValidationArguments) {
        return 'The string is not a valid Base64 encoded image';
    }
}

export class PatchUserDto {


    @Matches(/^(?=.{6,255}$)([^@]+@[^@]+\.[^@\s]{2,})$/u)
    email?: string;

    @IsOptional()
    @IsString()
    @Matches(/^(?=.*[\p{Ll}])(?=.*[\p{Lu}])(?=.*[\p{N}])(?=.*[\p{P}\p{S}])[\p{L}\p{N}\p{P}\p{S}]{8,64}$/u)
    password?: string;

    @IsString()
    @Matches(/^[\p{L}\p{N}]{4,20}$/u)
    username?: string;

    @Matches(/^[\p{L}]{2,50}$/u)
    firstName?: string;

    @IsString()
    @Matches(/^[\p{L}]{2,50}$/u)
    lastName?: string;

    @IsOptional()
    @IsString()
    @Validate(IsBase64ImageConstraint)
    picture?: string;

}
