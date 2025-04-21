import { Entity, CreateDateColumn, Column, UpdateDateColumn, OneToMany, PrimaryColumn } from 'typeorm';
import { Torrent } from '../../torrents/entities/torrent.entity.js';
import { Comment } from '../../comments/entities/comment.entity.js';
import { MovieView } from './view.entity.js';

@Entity('movies')
export class Movie
{
	@PrimaryColumn()
	imdb_id!: string;

	@Column()
	title!: string;

	@OneToMany( () => Comment, ( comment ) => comment.movie, { lazy: true } )
	comments!: Promise< Comment[] >;

	@OneToMany( () => Torrent, ( torrent ) => torrent.movie, { eager: true, cascade: ['insert', 'update'] } )
	torrents!: Torrent[];

	@OneToMany( () => MovieView, ( view ) => view.movie, { lazy: true })
	views!: Promise< MovieView[] >;

	@CreateDateColumn()
	created_at!: Date;

	@UpdateDateColumn()
	updated_at!: Date;
}
