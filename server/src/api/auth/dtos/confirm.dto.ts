import { IsString, Matches } from 'class-validator';

export class ConfirmDto {
    
    @IsString()
    @Matches(/^(?=.*[\p{Ll}])(?=.*[\p{Lu}])(?=.*[\p{N}])(?=.*[\p{P}\p{S}])[\p{L}\p{N}\p{P}\p{S}]{8,64}$/u)
    password!: string;
}