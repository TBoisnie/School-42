
import Server from './server.js';

const server = new Server();
server.bootstrap().catch((error) => {
    console.error('Error starting server:', error);
    process.exit(1);
});