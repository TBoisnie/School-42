import { createParamDecorator, ExecutionContext, BadRequestException, HttpException, HttpStatus } from '@nestjs/common';

export const ValidateCode = createParamDecorator(
  (_: unknown, ctx: ExecutionContext) => {
    const request = ctx.switchToHttp().getRequest();
    const code = request.query.token;

    // Check if the code is missing or invalid
    if (!code) {
      throw new BadRequestException('Code is missing');
    }

    if (typeof code !== 'string') {
      throw new BadRequestException('Code must be a string');
    }

    if (code.trim().length !== 48) {
      throw new BadRequestException('Code must be exactly 40 characters long');
    }

    return code;
  },
);