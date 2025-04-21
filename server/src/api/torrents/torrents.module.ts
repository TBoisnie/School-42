import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Torrent } from './entities/torrent.entity.js';
import { SearchService } from './services/search.service.js';
import { DownloadService } from './services/download.service.js';
import { StreamingService } from './services/streaming.service.js';
import { FileStorageService } from './services/file-storage.service.js';
import { SubtitlesService } from './services/subtitles.service.js';

@Module({
	imports: [
		TypeOrmModule.forFeature([ Torrent ]),
	],
	controllers: [
	],
	providers: [
		SearchService,
		DownloadService,
		FileStorageService,
		StreamingService,
		SubtitlesService,
	],
	exports: [
		SearchService,
		StreamingService,
		SubtitlesService,
	],
})
export class TorrentsModule
{
}
