import { createParamDecorator, ExecutionContext, HttpException, HttpStatus } from '@nestjs/common';
import { plainToInstance } from 'class-transformer';
import { validate } from 'class-validator';

export const ValidateBody = createParamDecorator(
    async (value: any, ctx: ExecutionContext) => {
        const request = ctx.switchToHttp().getRequest();
        const body = request.body;

        // console.log(body);

        // Check if the body is empty
        if (!body || Object.keys(body).length === 0) {
            throw new HttpException('Request body is empty', HttpStatus.BAD_REQUEST);
        }

        const dto = plainToInstance(value, body, { enableImplicitConversion: true });
        const errors = await validate(dto);
        
        // console.log(errors);

        // Check if the body is valid
        if (errors.length > 0) {
            throw new HttpException('Validation failed', HttpStatus.BAD_REQUEST);
        }
        return dto;
    },
);