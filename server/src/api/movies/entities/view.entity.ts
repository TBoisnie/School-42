import { Entity, CreateDateColumn, OneToMany, PrimaryColumn, Relation, JoinColumn, ManyToOne } from 'typeorm';
import { Users } from '../../../api/users/entities/users.entity.js';
import { Movie } from './movie.entity.js';

@Entity('movie_views')
export class MovieView
{

	@ManyToOne( () => Movie, ( movie ) => movie.views, { eager: true, onDelete: 'CASCADE'  } )
    @JoinColumn({ name: "movieImdbId" })
	movie!: Relation<Movie>;

	@PrimaryColumn()
	movieImdbId!: string;

	@ManyToOne( () => Users, ( user ) => user.seen_movies, { eager: true, onDelete: 'CASCADE'  } )
    @JoinColumn({ name: "usersId" })
	user!: Relation<Users>;

	@PrimaryColumn()
	usersId!: number;

	@CreateDateColumn()
	created_at!: Date;

}
