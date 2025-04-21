import fs from 'fs';
import path from 'path';
import { AppModule } from './app.module.js';
import { NestFactory } from '@nestjs/core';
import { INestApplication, Logger } from '@nestjs/common';
import { HttpExceptionFilter } from './core/filters/http-exception.filter.js';
import { ConfigService } from '@nestjs/config';
import nodemailer from 'nodemailer';
import { fileURLToPath } from 'url';
import { dirname } from 'path';


class Server {
  private app!: INestApplication;
  private readonly logger = new Logger(Server.name);

  constructor() { }

  // const code = 'AUTHORIZATION_CODE';
  //   try {
  //     const data = querystring.stringify({
  //       code: code,
  //       client_id: configService.get<string>('GOOGLE_CLIENT_ID'),
  //       client_secret: configService.get<string>('GOOGLE_CLIENT_SECRET'),
  //       redirect_uri: configService.get<string>('GOOGLE_CALLBACK_URL'),
  //       grant_type: 'authorization_code',
  //     });
  //     const TOKEN_URL = 'https://oauth2.googleapis.com/token';
  //     const response = await fetch(TOKEN_URL, {
  //       method: 'POST',
  //       headers: {
  //         'Content-Type': 'application/x-www-form-urlencoded',
  //       },
  //       body: data,
  //     });
  //     const dataResponse = await response.json();
  //     console.log(dataResponse);
  //   } catch (error) {
  //     console.error(error);
  //   }
  //   exit(1);
  // }

  public async bootstrap(): Promise<void> {
    const pathToCertificats = path.join(dirname(fileURLToPath(import.meta.url)), '..', '..');
    const httpsOptions = {
      key: fs.readFileSync(path.join(pathToCertificats, 'server.key')),
      cert: fs.readFileSync(path.join(pathToCertificats, 'server.crt')),
    };

    // Create the Nest application instance with the AppModule and the HTTPS options.
    this.app = await NestFactory.create(AppModule, { logger: false, httpsOptions, bodyParser: false });
    const configService = this.app.get(ConfigService);

    // Set the global exception filter to the HttpExceptionFilter.
    this.app.useGlobalFilters(new HttpExceptionFilter());

    // Set the global prefix for all routes.
    this.app.setGlobalPrefix('api');

    // Start the server on the specified port.
    const port = Number(configService.get<string>('HTTPS_PORT'));
    await this.app.listen(port, async () => {
      this.logger.log(`Server running at https://localhost:${port}`);

      // Send an email with the server running message.
      if (configService.get<string>('GMAIL_SEND_EMAIL_TEST') === 'true') {
        const transporter = nodemailer.createTransport({
          service: 'gmail',
          auth: {
            type: 'OAuth2',
            user: configService.get<string>('GMAIL_USER'),
            clientId: configService.get<string>('GOOGLE_CLIENT_ID'),
            clientSecret: configService.get<string>('GOOGLE_CLIENT_SECRET'),
            refreshToken: configService.get<string>('GMAIL_REFRESH_TOKEN'),
          },
        });
        // console.log('Sending test email...');
        const recipients = {
          from: configService.get<string>('GMAIL_USER'),
          to: configService.get<string>('GMAIL_USER'),
          subject: 'Test email',
          text: 'This is a test email.'
        };
        const info = await transporter.sendMail(recipients);
        // console.log('Email sent: (' + info.response + ') to ' + recipients.to);
      }
    });
  }
}

export default Server;
