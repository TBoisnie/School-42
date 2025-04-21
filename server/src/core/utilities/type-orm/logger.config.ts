import * as fs from 'fs';
import * as path from 'path';
import { createLogger as winstonCreateLogger, format, transports } from 'winston';
import { fileURLToPath } from 'url';
import { dirname } from 'path';


// Initialize the logger for the application with the Winston logger library and the log file.
export function initializeLogger() {
    const logsDir = path.join(dirname(fileURLToPath(import.meta.url)), '..', '..', '..', '..', 'logs');
    if (!fs.existsSync(logsDir)) {
        fs.mkdirSync(logsDir, { recursive: true });
    }
    const logFileName = `sql_${new Date().toISOString().replace(/[:.]/g, '-')}.log`;
    const logger = winstonCreateLogger({
        level: 'info',
        format: format.combine(
            format.timestamp(),
            format.printf(({ timestamp, level, message }) => {
                return `${timestamp} [${level}]: ${message}`;
            })
        ),
        transports: [
            new transports.File({ filename: path.join(logsDir, logFileName) })
        ],
    });

    const customLogger = {
        log: (level: string, message: any) => {
            logger.log({ level, message });
        },
        logQuery: (query: string) => {
            logger.info(query);
        },
        logQueryError: (error: string, query: string) => {
            logger.error(`Error: ${error} Query: ${query}`);
        },
        logQuerySlow: (time: number, query: string) => {
            logger.warn(`Slow Query (${time}ms): ${query}`);
        },
        logSchemaBuild: (message: string) => {
            logger.info(message);
        },
        logMigration: (message: string) => {
            logger.info(message);
        },
    };

    return customLogger;
}
