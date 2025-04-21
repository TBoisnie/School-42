import { Controller, Get, Post, Delete, HttpStatus, Inject, HttpCode, UseGuards, Patch, Logger, HttpException, Res } from '@nestjs/common';
import { Response } from 'express';
import { UsersService } from '../services/users.service.js';
import { Users } from '../entities/users.entity.js';
import { CookieGuard } from '../../auth/guards/cookie.guard.js';
import { CreateUserDto } from '../dtos/create.dto.js';
import { PatchUserDto } from '../dtos/patch.dto.js';
import { ValidateBody } from '../../../core/decorators/validate-body.decorator.js';
import { ValidateId } from '../../../core/decorators/validate-id.decorator.js';
import { GetIp } from '../../../core/decorators/get-ip.decorator.js';
import { GetCookiePayload } from '../../../core/decorators/get-cookie-playload.decorator.js';
import { CookiePayload } from '../../auth/types/token-payload.type.js';
import { DeepPartial } from 'typeorm';

@Controller('users')
export class UsersController {
  private readonly logger = new Logger();

  constructor(
    @Inject(UsersService) private readonly usersService: UsersService
  ) { }

  // Get all users
  @Get()
  @HttpCode(HttpStatus.OK)
  @UseGuards(CookieGuard)
  public async getUsers(
    @GetIp() ip: string,
  ): Promise<DeepPartial<Users[]>> {
    const users = await this.usersService.getUsers();
    const usersPublic = users.map(user => {
      const { id, picture, username, firstName, lastName } = user;
      return { id, picture, username, firstName, lastName };
    });
    this.logger.log(`Has accessed the users`, ip);
    return usersPublic;
  }

  // Get an existing user by id
  @Get(':id')
  @HttpCode(HttpStatus.OK)
  @UseGuards(CookieGuard)
  public async getUserById(
    @GetCookiePayload() cookiePayload: CookiePayload,
    @ValidateId() id: number,
    @GetIp() ip: string
  ): Promise<DeepPartial<Users>> {
    const user = await this.usersService.getUserById(id || cookiePayload.id)
    const userPartial: DeepPartial<Users> = {
      id: user.id,
      username: user.username,
      firstName: user.firstName,
      lastName: user.lastName,
      picture: user.picture,
      email: user.email
    };
    if (id !== 0) {
      delete userPartial.email;
    }
    this.logger.log(`Has accessed the user with id ${id}`, ip);
    return userPartial;
  }

  // Create a new user
  @Post()
  @HttpCode(HttpStatus.CREATED)
  public async addUser(
    @ValidateBody(CreateUserDto) createUserDto: CreateUserDto,
    @GetIp() ip: string
  ): Promise<void> {
    await this.usersService.createUser(createUserDto);
    this.logger.log(`Has created a new user with email ${createUserDto.email}`, ip);
  }

  // Patch an existing user
  @Patch(':id')
  @HttpCode(HttpStatus.OK)
  @UseGuards(CookieGuard)
  public async updateUser(
    @GetCookiePayload() cookiePayload: CookiePayload,
    @ValidateId() id: number,
    @ValidateBody(PatchUserDto) patchUserDto: PatchUserDto,
    @GetIp() ip: string
  ): Promise<void> {
    if (cookiePayload.id !== id) {
      throw new HttpException('Forbidden', HttpStatus.FORBIDDEN);
    }
    await this.usersService.patchUser(id, patchUserDto);
    this.logger.log(`Has patched the user with id ${id}`, ip);
  }

  // Delete an existing user
  @Delete(':id')
  @HttpCode(HttpStatus.NO_CONTENT)
  @UseGuards(CookieGuard)
  public async deleteUserById(
    @GetCookiePayload() cookiePayload: CookiePayload,
    @ValidateId() id: number,
    @GetIp() ip: string,
    @Res({ passthrough: true }) res: Response
  ): Promise<void> {
    if (cookiePayload.id !== id) {
      throw new HttpException('Forbidden', HttpStatus.FORBIDDEN);
    }
    await this.usersService.deleteUserById(id);
    this.logger.log(`Has deleted the user with id ${id}`, ip);
    res.clearCookie('auth');
    res.cookie('login', false);
  }
}