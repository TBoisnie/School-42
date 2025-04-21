import { Entity, PrimaryGeneratedColumn, CreateDateColumn, Column, ManyToOne, UpdateDateColumn, Relation } from 'typeorm';
import { Users } from '../../users/entities/users.entity.js';
import { Movie } from '../../movies/entities/movie.entity.js';

@Entity('comments')
export class Comment
{
	@PrimaryGeneratedColumn()
	id!: number;

	@ManyToOne( () => Users, ( user ) => user.comments, { eager: true, onDelete: 'CASCADE' } )
	author!: Relation< Users >;

	@ManyToOne( () => Movie, ( movie ) => movie.comments, { lazy: true } )
	movie!: Promise< Movie >;

	@Column({ nullable: false })
	movieImdbId!: string;

	@Column()
	content!: string;

	@CreateDateColumn()
	created_at!: Date;

	@UpdateDateColumn()
	updated_at!: Date;
}
