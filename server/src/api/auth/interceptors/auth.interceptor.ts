import { Injectable, NestInterceptor, ExecutionContext, CallHandler } from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap } from 'rxjs/operators';

// Execution order
// 1. Middleware
// 2. Guards
// 3. Interceptors
// 4. Controllers
// 5. Pipes (Interceptor again)

export class AuthInterceptor implements NestInterceptor {
  intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
    const request = context.switchToHttp().getRequest();

    // console.log('Interceptor');

    return next.handle().pipe(
      tap(response => {
        // console.log('Pipe (Interceptor again)');
      }),
    );
  }
}
