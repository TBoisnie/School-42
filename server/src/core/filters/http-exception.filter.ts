import { ExceptionFilter, Catch, ArgumentsHost, HttpException, Logger } from '@nestjs/common';
import { Request, Response } from 'express';

@Catch(HttpException)
export class HttpExceptionFilter implements ExceptionFilter {
  private readonly logger = new Logger();

  catch(exception: HttpException, host: ArgumentsHost) {
    const ctx = host.switchToHttp();
    const request = ctx.getRequest<Request>();
    const response = ctx.getResponse<Response>();
    const status = exception.getStatus() as number;
    const message = exception.message || 'An unexpected error occurred';
    const timestamp = new Date().toISOString();

    this.logger.error(message + ' ' + status, request.ip);

    response
      .status(status)
      .json({
        message: message,
      });
  }
}