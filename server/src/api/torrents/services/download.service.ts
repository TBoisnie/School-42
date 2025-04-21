import { Injectable } from '@nestjs/common';
import { Cron } from '@nestjs/schedule';
import * as Stream from 'node:stream';
import * as FileSystem from 'node:fs/promises';
import TorrentStream from 'torrent-stream';
import { Response } from 'express';

@Injectable()
export class DownloadService
{

	private static readonly TRACKERS =
	[
		'udp://open.demonii.com:1337/announce',
		'udp://p4p.arenabg.com:1337',
		'udp://glotorrents.pw:6969/announce',
		'udp://torrent.gresille.org:80/announce',
		'udp://tracker.openbittorrent.com:80',
		'udp://tracker.opentrackr.org:1337/announce',
		'udp://tracker.coppersurfer.tk:6969/announce',
		'udp://tracker.internetwarriors.net:1337/announce',
		'udp://tracker.leechers-paradise.org:6969/announce',
		'udp://tracker.pirateparty.gr:6969/announce',
		'udp://tracker.cyberia.is:6969/announce'
	] as const;

	private static readonly TMP_DIR = '/tmp' as const;

	public constructor()
	{
	}

	public async file(
		hash: string,
		accepted_extensions: string[],
		res: Response,
		languages?: string[],
	)
		: Promise< { path: string, stream: Stream.Readable, complete: boolean } >
	{
		return new Promise(( resolve, reject ) =>
		{
			const engine = TorrentStream( this._getMagnetLink( hash ), { tmp: DownloadService.TMP_DIR, verify: true } );

			let file: globalThis.TorrentStream.TorrentFile | undefined = undefined;
			let resolved = false;
			let stream : Stream.Readable | undefined = undefined;

			const response = (complete: boolean) => ({ path: `${DownloadService.TMP_DIR}/torrent-stream/${ hash.toLocaleLowerCase() }/${file?.path}`, stream: stream!, complete });

			res.on('close', () => engine.destroy(() => {
				// console.log("Downloader: Client Connection Closed")
			}));

			engine.on('ready', () =>
			{
				// console.log("Downloader: TorrentEngine - Ready");
				engine.files.forEach((f) => {
					// console.log("File: ", f.name, f.length)
				});
				file = engine.files
					.sort((a, b) => b.length - a.length)
					.filter((f) => accepted_extensions.includes(f.name.split('.').pop() ?? ''))
					.find((f) => languages ? languages.some((l) => f.name.split('.').includes(l)) : true)
				;

				if ( ! file )
				{
					engine.destroy(() => {
						// console.log('DownloaderReady: !file -> Destroy')
					});
					res.status(404).send(); // Todo: Verify
					return reject( new Error("Downloader: TorrentEngine - File Not Found (FILE_NOT_FOUND)") );
				}

				stream = file.createReadStream();
				// console.log("Downloader: TorrentEngine - Start", file.name);
			});

			const THRESHOLD = 10;

			engine.on('download', ( piece ) =>
			{
				// console.log("Downloader: TorrentEngine - Piece", file?.name, piece);

				if ( resolved )
				{
					// console.log("Downloader: TorrentEngine - Resolved", file?.name, piece);
					return ;
				}

				if ( +piece < +THRESHOLD )
				{
					// console.log("Downloader: TorrentEngine - Waiting", file?.name, piece);
					return ;
				}

				// console.log("Downloader: TorrentEngine - Resolve");
				resolved = true;
				return resolve( response(false) );
			});

			engine.on('idle', () =>
			{
				engine.destroy(() => { /* console.log(`Downloader: TorrentEngine - Destroy (${ hash })`) */ });

				if ( resolved )
				{
					return ;
				}

				// console.log("Downloader: TorrentEngine - Complete");
				resolved = true;
				return resolve( response(true) );
			});

		});
	}

	private _getMagnetLink(
		hash: string,
	)
		: string
	{
		const trackers = DownloadService.TRACKERS.map(( tracker ) => `&tr=${ tracker }`).join('');

		return `magnet:?xt=urn:btih:${ hash }${ trackers }`;
	}

	@Cron('0 3 * * * *') // Every day at 3:00 AM
	private async _clean()
	{
		const ROOT = `${DownloadService.TMP_DIR}/torrent-stream`;
		const THRESHOLD = new Date();
		THRESHOLD.setMonth(THRESHOLD.getMonth() - 1);

		try
		{
			const files = await FileSystem.readdir( ROOT );

			for ( const file of files )
			{
				const path = `${ROOT}/${file}`;

				// console.log("Torrent: Checking", path);

				if ( ! await this._hasBeenModifiedSince( path , THRESHOLD ) )
				{
					// console.log("Torrent: Removing", path);
					FileSystem.rm( path, { recursive: true } );
				}
			}
		}
		catch (e: unknown)
		{
			console.log(`DownloadService: ${e}`)
		}
	}

	private async _hasBeenModifiedSince(
		path: string,
		threshold: Date,
	)
		: Promise< boolean >
	{
		const hasExpired = async ( p: string ) =>
		{
			const stats = await FileSystem.stat( p );
			return ( stats.atime < threshold && stats.mtime < threshold && stats.ctime < threshold );
		};

		try
		{
			if ( (await FileSystem.lstat(path)).isDirectory() )
			{
				const files = await FileSystem.readdir( path, { recursive: true } )

				for ( const file of files )
				{
					if ( await hasExpired( `${path}/${file}` ) )
					{
						return false;
					}
				}
			}
			else
			{
				if ( await hasExpired( path ) )
				{
					return false;
				}
			}

		}
		catch ( err: unknown )
		{
		}

		return true;
	}

}
