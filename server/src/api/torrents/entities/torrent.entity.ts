import { Entity, CreateDateColumn, UpdateDateColumn, ManyToOne, PrimaryColumn, Column } from 'typeorm';
import { Movie } from '../../movies/entities/movie.entity.js';

@Entity('torrents')
export class Torrent
{
	@PrimaryColumn()
	hash!: string;

	@Column({ nullable: true })
	quality?: string;

	@ManyToOne(() => Movie, ( movie ) => movie.torrents, { lazy: true })
	movie!: Promise< Movie >;

	@CreateDateColumn()
	created_at!: Date;

	@UpdateDateColumn()
	updated_at!: Date;
}
