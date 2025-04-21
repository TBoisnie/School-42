import { IsEmail, IsString, Matches, MaxLength, MinLength } from 'class-validator';

export class LoginDto {
    
    @Matches(/^(?=.{6,255}$)([^@]+@[^@]+\.[^@\s]{2,})$/u)
    email!: string;

    @IsString()
    @Matches(/^(?=.*[\p{Ll}])(?=.*[\p{Lu}])(?=.*[\p{N}])(?=.*[\p{P}\p{S}])[\p{L}\p{N}\p{P}\p{S}]{8,64}$/u)
    password!: string;
}