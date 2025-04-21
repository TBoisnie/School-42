import { Injectable } from '@nestjs/common';
import { DownloadService } from './download.service.js';
import { Response } from 'express';
import { createRequire } from 'module';
import * as fs from 'fs';

@Injectable()
export class SubtitlesService
{

	constructor(
		private readonly downloader: DownloadService,
	)
	{
	}

	public async download(
		hash: string,
		languages: string[],
		res : Response,
	)
	{
		try
		{
			const file = await this.downloader.file( hash, [ 'vtt', 'srt' ], res, languages );
			const ext = file.path.split('.').pop() ?? '';

			res.setHeader('Content-Type', 'text/vtt');

			if ( ['vtt'].includes( ext ) )
			{
				if ( file.complete )
				{
					res.download( file.path );
				}
				else
				{
					file.stream.pipe( res );
				}
				return ;
			}

			const vtt = `${file.path}.vtt`;

			if ( ! fs.existsSync(vtt) )
			{
				while ( ! fs.existsSync(file.path) )
				{
					await new Promise(resolve => setTimeout(resolve, 2000)); // Wait 2 sec
				}

				const require = createRequire(import.meta.url);
				const srt2vtt = require('srt-to-vtt');

				fs.createReadStream(file.path).pipe(srt2vtt()).pipe(fs.createWriteStream(vtt));
			}

			while ( ! fs.existsSync(vtt) )
			{
				await new Promise(resolve => setTimeout(resolve, 2000)); // Wait 2 sec
			}

			fs.createReadStream(vtt).pipe(res, { end: true });
		}
		catch( e: unknown )
		{
			// console.log("DownloadSubtitles Fail.")
		}
	}
}
