import { createParamDecorator, ExecutionContext, HttpException, HttpStatus } from '@nestjs/common';

export const ValidateId = createParamDecorator(
    (data: unknown, ctx: ExecutionContext) => {
        const request = ctx.switchToHttp().getRequest();
        const id = request.params.id;

        // Verify if the ID is a string and contains only digits
        if (typeof id !== 'string' || !/^\d+$/.test(id)) {
            throw new HttpException('Invalid id format', HttpStatus.BAD_REQUEST);
        }

        const numericId = Number(id);

        // Verify if the ID is a valid number
        if (
            isNaN(numericId) || 
            numericId < 0 || 
            !Number.isSafeInteger(numericId)
        ) {
            throw new HttpException('Invalid id', HttpStatus.BAD_REQUEST);
        }

        return numericId;
    },
);