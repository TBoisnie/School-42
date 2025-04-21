import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UsersController } from './controllers/users.controller.js';
import { UsersService } from './services/users.service.js';
import { Users } from './entities/users.entity.js';
import { AuthService } from '../auth/services/auth.service.js';

@Module({
  imports: [
    TypeOrmModule.forFeature([Users])
  ],
  controllers: [
    UsersController
  ],
  providers: [
    UsersService,
    AuthService
  ],
  exports: [
    UsersService,
  ]
})
export class UsersModule { }
