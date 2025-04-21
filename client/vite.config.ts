import { defineConfig, ProxyOptions } from 'vite';
import react from '@vitejs/plugin-react';
import fs from 'fs';
import path, { dirname } from 'path';
import { fileURLToPath } from 'url';

export default defineConfig({
    plugins: [
        react(),
    ],
    build: {
        outDir: 'client',
    },
    server: {
        https: {
            key: fs.readFileSync(path.resolve(dirname(fileURLToPath(import.meta.url)), '..', 'server.key')),
            cert: fs.readFileSync(path.resolve(dirname(fileURLToPath(import.meta.url)), '..', 'server.crt')),
            rejectUnauthorized: false,
        },
        host: '0.0.0.0',
        port: 5173,
        watch: {
            usePolling: true,
            interval: 1000,
        },
        proxy: {
            '/api': {
                target: 'https://localhost:3000',
                changeOrigin: true,
                secure: false,
                configure: (proxy, options) => {
                    proxy.on('proxyReq', (proxyReq, req) => {
                        // console.log('Proxying request:', req.url);
                    });
                    proxy.on('proxyRes', (proxyRes, req, res) => {
                        // console.log('Received response from target:', proxyRes.statusCode);
                        proxyRes.on('data', (chunk) => {
                            // console.log('Response chunk:', chunk.toString());
                        });
                    });
                    proxy.on('error', (err, req, res) => {
                        console.error('Proxy error:', err);
                    });
                },
            } as ProxyOptions,
            // '/oauth/42/callback': {
            //     target: 'https://localhost:3000',
            //     changeOrigin: true,
            //     secure: false,
            //     rewrite: (path: string) => path.replace(/^\/oauth\/42\/callback/, '/api/oauth/42/callback'),
            // },
            // '/oauth/google/callback': {
            //     target: 'https://localhost:3000',
            //     changeOrigin: true,
            //     secure: false,
            //     rewrite: (path: string) => path.replace(/^\/oauth\/google\/callback/, '/api/oauth/google/callback'),
            // },
        },
    },
});
