import { IsEmail, IsString, Matches, MaxLength } from 'class-validator';

// /^ - start of the string 
// \p - Unicode property escapes (ES2018) 
// /u - Unicode flag for regular expressions (ES6) 

// Ll - lowercase letter  
// Lu - uppercase letter 
// \d - digit 
// P - punctuation 
// S - symbol example: !@#$%^&*()_+{}:"<>?|[];',./\-=
// L - letter

export class CreateUserDto {

  @Matches(/^(?=.{6,255}$)([^@]+@[^@]+\.[^@\s]{2,})$/u)
  email!: string;

  @IsString()
  @Matches(/^(?=.*[\p{Ll}])(?=.*[\p{Lu}])(?=.*[\p{N}])(?=.*[\p{P}\p{S}])[\p{L}\p{N}\p{P}\p{S}]{8,64}$/u)
  password!: string;

  @IsString()
  @Matches(/^[\p{L}\p{N}]{4,20}$/u)
  username!: string;

  @Matches(/^[\p{L}]{2,50}$/u)
  firstName!: string;

  @IsString()
  @Matches(/^[\p{L}]{2,50}$/u)
  lastName!: string;

}