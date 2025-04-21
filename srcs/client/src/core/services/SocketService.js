import io from 'socket.io-client';

// Service ---------------------------------------------------------------------
export const SocketService = io('http://localhost:8080/',
	{
		autoConnect: false
	},
);
