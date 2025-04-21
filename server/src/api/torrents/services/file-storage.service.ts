import { Injectable } from '@nestjs/common';
import * as Path from 'node:path';
import * as Stream from 'node:stream';
import * as FileSystem from 'node:fs';

@Injectable()
export class FileStorageService
{
	// Todo: Replace with env variable
	// private static readonly ROOT_DIR = '/tmp/torrent-stream';

	public constructor()
	{
	}

	public path(
		...parts : string[]
	)
		: string
	{
		return Path.join( ...parts );
	}

	public exists(
		...parts : string[]
	)
	{
		return FileSystem.existsSync( this.path( ...parts ) );
	}

	public read(
		...parts : string[]
	)
		: Stream.Readable | null
	{
		const path = this.path( ...parts );

		try
		{
			FileSystem.accessSync( path, FileSystem.constants.R_OK );
		}
		catch ( err: unknown )
		{
			// console.log(`FileStorage: Access denied (${ path })`);
			return null;
		}

		return FileSystem.createReadStream( path );
	}

	public open(
		...parts : string[]
	)
		: Stream.Writable
	{
		return FileSystem.createWriteStream( this.path( ...parts ) );
	}

	public mkdir(
		...parts : string[]
	)
	{
		const dir = this.path( ...parts );

		if ( ! FileSystem.existsSync( dir ) )
		{
			FileSystem.mkdirSync( dir );
		}
	}

	public rm(
		...parts : string[]
	)
	{
		FileSystem.rmSync( this.path( ...parts ), { force: true, recursive: true } );
	}

}
