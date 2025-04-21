import { MiddlewareConsumer, Module, NestModule, RequestMethod } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { UsersModule } from './api/users/users.module.js';
import { initializeLogger } from './core/utilities/type-orm/logger.config.js';
import { StaticMiddleware } from './core/middlewares/static.middleware.js';
import { JsonMiddleware } from './core/middlewares/json.middleware.js';
import { UrlencodedMiddleware } from './core/middlewares/urlencoded.middleware.js';
import path from 'path';
import cors from 'cors';
import { AuthModule } from './api/auth/auth.module.js';
import { CookieMiddleware } from './core/middlewares/cookie.middleware.js';
import { QueryMiddleware } from './core/middlewares/query.middleware.js';
import { MoviesModule } from './api/movies/movies.module.js';
import { TorrentsModule } from './api/torrents/torrents.module.js';
import { CommentsModule } from './api/comments/comments.module.js';
import { fileURLToPath } from 'url';
import { dirname } from 'path';
import { ServeStaticModule } from '@nestjs/serve-static';
import { ScheduleModule } from '@nestjs/schedule';
import { CacheModule } from '@nestjs/cache-manager';

@Module({
    imports: [
        ServeStaticModule.forRoot({
            rootPath: path.join(dirname(fileURLToPath(import.meta.url)), '..', 'storage'),
            serveRoot: '/static',
        }),
        ScheduleModule.forRoot(),
        // CacheModule.register({
        //     ttl: 5 * 60 * 1000,
        //     isGlobal: true,
        // }),
        ConfigModule.forRoot({
            isGlobal: true,
            envFilePath: path.join(dirname(fileURLToPath(import.meta.url)), '..', '..', '.env'),
        }),
        TypeOrmModule.forRootAsync({
            imports: [ConfigModule],
            inject: [ConfigService],
            useFactory: async (configService: ConfigService) => ({
                type: configService.get<string>('DATABASE_TYPE') as any,
                host: configService.get<string>('DATABASE_HOST'),
                port: configService.get<number>('DATABASE_PORT'),
                username: configService.get<string>('DATABASE_USERNAME'),
                password: configService.get<string>('DATABASE_PASSWORD'),
                database: configService.get<string>('DATABASE_NAME'),
                autoLoadEntities: true,
                synchronize: true, // ⚠️ should be false in production
                logging: true,
                logger: initializeLogger(),
            }),
        }),
        UsersModule,
        AuthModule,
        CommentsModule,
        MoviesModule,
        TorrentsModule,
    ],
})
export class AppModule implements NestModule {
    private httpsPort: string;

    constructor(private configService: ConfigService) {
        this.httpsPort = this.configService.get<string>('HTTPS_PORT') as string;
    }

    configure(consumer: MiddlewareConsumer) {
        consumer
            .apply(
                StaticMiddleware,
                cors({
                    origin: [
                        `http://localhost:${this.httpsPort}`,
                    ],
                    methods: ['GET', 'POST', 'DELETE', 'PATCH'],
                    credentials: true,
                }),
                CookieMiddleware,
                JsonMiddleware,
                UrlencodedMiddleware,
                QueryMiddleware,
            )
            .forRoutes({ path: '*', method: RequestMethod.ALL });
    }
}
