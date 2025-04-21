import { Injectable } from '@nestjs/common';
import FluentFFMpeg from 'fluent-ffmpeg';
import { DownloadService } from './download.service.js';
import { Response } from 'express';

@Injectable()
export class StreamingService
{

	public constructor(
		private readonly downloader: DownloadService,
	)
	{
	}

	public async stream(
		hash: string,
		res : Response,
	)
		: Promise< void >
	{
		const file = await this.downloader.file( hash, [ 'mp4', 'webm', 'mkv', 'mov' ], res );
		const ext = file.path.split('.').pop() ?? '';

		if ( ['mp4', 'webm'].includes( ext ) )
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

		return new Promise( ( resolve, reject ) =>
		{
			let resolved = false;

			res.setHeader('Content-Type', 'video/mp4');

			// console.log("Stream File Convert");
			// https://www.ffmpeg.org/ffmpeg-all.html#Advanced-options
			// https://www.ffmpeg.org/ffmpeg-all.html#Fragmentation
			// https://ffmpeg.org/ffmpeg-formats.html#hls-2
			const cmd = FluentFFMpeg(file.stream)
				.toFormat('mp4')
				.outputOptions([
					'-preset ultrafast',
					// '-tune zerolatency',
					// '-map 0',
					// '-map 0:v',
					// '-map 0:s',
					// '-c copy',
					// '-c:a aac',
					// '-c:v copy',
					// '-c:s mov_text',
					// '-b:a 128k',
					// '-b:v 3500k',
					'-sn', // disable subtitle
					'-movflags frag_keyframe+empty_moov',
					// '-movflags +faststart+frag_keyframe+empty_moov',
				])
				.on('start', (cmd) =>
				{
					// console.log("Stream File Convert START: ", cmd);
				})
				.on('progress', ({ percent, targetSize }) =>
				{
					// console.log("Stream File Convert PROGRESS: ", percent, targetSize);
					if ( ! resolved )
					{
						// console.log("Stream File Convert RESOLVED");
						resolved = true;
						resolve();
					}
				})
				.on('end', (out) =>
				{
					// console.log("Stream File Convert END: ", out);
				})
				.on('error', ( err ) =>
				{
					// console.log("Stream File Convert INFO: ");
					reject( new Error(`Streaming: Convertion failed (${ err.message })`));
				})
				.on('stderr', (line) =>
				{
					// console.log("Stream File Convert STDERR: ", line);
				})
				.pipe(res,{ end:true })
			;

			res.on('close', () => { 
				// console.log("Streaming: Response closed."); 
				cmd.destroy(); 
			});
		});
	}

}
