import { Matches } from 'class-validator';

export class ResetDto {
    
    @Matches(/^(?=.{6,255}$)([^@]+@[^@]+\.[^@\s]{2,})$/u)
    email!: string;
}