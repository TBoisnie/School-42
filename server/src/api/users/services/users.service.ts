import { HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { Users } from '../entities/users.entity.js';
import { DeepPartial, Repository } from 'typeorm';
import { InjectRepository } from '@nestjs/typeorm';
import { promises as fs } from 'fs';
import * as path from 'path';

@Injectable()
export class UsersService {

  constructor(
    @InjectRepository(Users)
    private readonly usersRepository: Repository<Users>,
  ) { }

  async getUsers(): Promise<Users[]> {
    return await this.usersRepository.find();
  }

  async createUser(userData: Partial<Users>): Promise<Users> {
    // Check if the user already exists
    const user = await this.usersRepository.findOne({ where: { email: userData.email } });
    if (user) {
      throw new HttpException('User already exists', HttpStatus.CONFLICT);
    }
    const entity = this.usersRepository.create(userData);
    return await this.usersRepository.save(entity);
  }

  async registerByProvider(profile: any): Promise<number> {

    if (profile.provider === '42') {
      // Check if the user already exists by provider
      const userByProvider = await this.usersRepository.findOne({ where: { fortyTwoId: profile._json.id } });
      if (userByProvider) {
        return userByProvider.id;
      }
      // Check if the user already exists by email
      const userByEmail = await this.usersRepository.findOne({ where: { email: profile._json.email } });
      if (userByEmail) {
        userByEmail.fortyTwoId = profile._json.id;
        await this.usersRepository.save(userByEmail);
        return userByEmail.id;
      }
      // Create a new user
      const userData: DeepPartial<Users> = {
        username: profile._json.login,
        firstName: profile._json.first_name,
        lastName: profile._json.last_name,
        email: profile._json.email,
        picture: profile._json.image.link,
        fortyTwoId: profile._json.id,
      };
      const entity = this.usersRepository.create(userData);
      return (await this.usersRepository.save(userData)).id;

    } else if (profile.provider === 'google') {
      // Check if the user already exists by provider
      const userByProvider = await this.usersRepository.findOne({ where: { googleId: profile.id } });
      if (userByProvider) {
        return userByProvider.id;
      }
      // Check if the user already exists by email
      const userByEmail = await this.usersRepository.findOne({ where: { email: profile._json.email } });
      if (userByEmail) {
        userByEmail.googleId = profile._json.sub;
        await this.usersRepository.save(userByEmail);
        return userByEmail.id;
      }
      // Create a new user
      const userData: DeepPartial<Users> = {
        username: (profile._json.given_name[0] + profile._json.family_name).toLowerCase().slice(0, 20) || profile._json.email.split('@')[0],
        firstName: profile._json.given_name || 'undefined',
        lastName: profile._json.family_name || 'undefined',
        email: profile._json.email,
        picture: profile._json.picture || '',
        googleId: profile._json.sub
      };
      const entity = this.usersRepository.create(userData);
      return (await this.usersRepository.save(entity)).id;

    } else if (profile.provider === 'github') {
      // Check if the user already exists by provider
      const userByProvider = await this.usersRepository.findOne({ where: { githubId: profile.id } });
      if (userByProvider) {
        return userByProvider.id;
      }
      // Check if the user already exists by email
      const userByEmail = await this.usersRepository.findOne({ where: { email: profile._json.email } });
      if (userByEmail) {
        userByEmail.githubId = profile._json.id;
        await this.usersRepository.save(userByEmail);
        return userByEmail.id;
      }
      // Create a new user
      const userData: DeepPartial<Users> = {
        username: profile._json.login,
        firstName: profile._json.name?.split(' ')[0] || 'undefined',
        lastName: profile._json.name?.split(' ')[1] || 'undefined',
        email: profile._json.email || profile.emails[0].value,
        picture: profile._json.avatar_url,
        githubId: profile._json.id,
      };
      const entity = this.usersRepository.create(userData);
      return (await this.usersRepository.save(entity)).id;

    } else {
      throw new HttpException('Invalid provider', HttpStatus.BAD_REQUEST);
    }
  }

  async patchUser(id: number, userData: Partial<Users>): Promise<Users> {
    // Check if the user exists
    let user = await this.usersRepository.findOne({ where: { id } });
    if (!user) {
      throw new HttpException('User not found', HttpStatus.NOT_FOUND);
    }
    // Check if the email is already taken
    if (userData.email) {
      const email = await this.usersRepository.findOne({ where: { email: userData.email } });
      if (email && email.id !== id) {
        throw new HttpException('Email already taken', HttpStatus.CONFLICT);
      }
      user.email = userData.email;
    }

    if (userData.picture && !userData.picture.startsWith('/pictures/')) {
      const buffer = Buffer.from(userData.picture, 'base64');
      const { fileTypeFromBuffer } = await import('file-type');
      const type = await fileTypeFromBuffer(buffer);
      if (type === undefined || !type.mime.startsWith('image/webp')) {
        throw new HttpException('Invalid image', HttpStatus.BAD_REQUEST);
      }
      const projectRoot = process.cwd();
      const imagesDir = path.join(projectRoot, '..', 'client', 'public', 'pictures');
      await fs.mkdir(imagesDir, { recursive: true });
      const fileName = `${user.id}.${type.ext}`;
      const filePath = path.join(imagesDir, fileName);
      await fs.writeFile(filePath, buffer);
      user.picture = '/pictures/' + fileName;
    }

    if (userData.username) {
      user.username = userData.username;
    }

    if (userData.firstName) {
      user.firstName = userData.firstName;
    }

    if (userData.lastName) {
      user.lastName = userData.lastName;
    }

    if (userData.password) {
      user.password = userData.password;
    }

    // console.log(userData);
    // console.log(user);

    return await this.usersRepository.save(user);
  }

  async getUserById(id: number): Promise<Users> {
    const user = await this.usersRepository.findOne({ where: { id } });
    // Check if the user exists
    if (!user) {
      throw new HttpException('User not found', HttpStatus.NOT_FOUND);
    }
    return user;
  }

  async deleteUserById(id: number): Promise<void> {
    const DeleteResult = await this.usersRepository.delete(id);
    // Check if the user exists
    if (DeleteResult.affected === 0) {
      throw new HttpException('User not found', HttpStatus.NOT_FOUND);
    }
  }
}
