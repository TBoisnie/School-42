import { Entity, PrimaryGeneratedColumn, Column, BeforeInsert, BeforeUpdate, OneToMany } from 'typeorm';
import * as bcrypt from 'bcrypt';
import { Comment } from '../../comments/entities/comment.entity.js';
import { MovieView } from '../../../api/movies/entities/view.entity.js';

@Entity()
export class Users {
  @PrimaryGeneratedColumn()
  id!: number;

  @Column({ type: 'varchar', length: 20 })
  username!: string;

  @Column({ type: 'varchar', length: 255, unique: true })
  email!: string;

  @Column({ type: 'varchar', length: 60, nullable: true })
  password?: string;

  @Column({ type: 'varchar', length: 50 })
  firstName!: string;

  @Column({ type: 'varchar', length: 50 })
  lastName!: string;

  @Column({ type: 'varchar', length: 255, nullable: true })
  picture?: string;

  @Column({ type: 'varchar', length: 50, nullable: true })
  googleId?: string;

  @Column({ type: 'varchar', length: 50, nullable: true })
  fortyTwoId?: string;

  @Column({ type: 'varchar', length: 50, nullable: true })
  githubId?: string;

  @OneToMany( () => Comment, ( comment ) => comment.author, { lazy: true, onDelete: 'CASCADE' })
  comments?: Promise< Comment[] >;

  @OneToMany( () => MovieView, ( view ) => view.user, { lazy: true, onDelete: 'CASCADE' })
  seen_movies?: Promise< MovieView[] >

  @BeforeInsert()
  @BeforeUpdate()
  async hashPassword() {
    if (this.password) {
      const salt = await bcrypt.genSalt(10);
      this.password = await bcrypt.hash(this.password, salt);
    }
  }
}
