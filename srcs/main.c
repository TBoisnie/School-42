
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

// Typedef
typedef enum e_io
{
	IO_IN  = 0,
	IO_OUT = 1,
	IO_ERR = 2
} t_io;
typedef enum e_sys
{
	SYS_EXIT_OK  = 0,
	SYS_EXIT_ERR = 1
} t_sys;
typedef int t_fd;

// General
void io_put_err(const char * str)
{
	write(IO_ERR, str, strlen(str));
}

void sys_exit()
{
	io_put_err("Fatal error\n");

	exit(SYS_EXIT_ERR);
}

char * str_join(char * str, char * suffix)
{
	size_t str_len    = !str    ? 0 : strlen(str);
	size_t suffix_len = !suffix ? 0 : strlen(suffix);

	char * joined = malloc(sizeof(char) * (str_len + suffix_len + 1));

	if (!joined)
		sys_exit();

	joined[0] = '\0';
	if (str)    strcat(joined, str);
	if (suffix) strcat(joined, suffix);

	return joined;
}

// Special
char * get_line(char * buffer)
{
	if (!buffer)
		return NULL;

	char * line = NULL;
	size_t i = 0;

	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			line = malloc(sizeof(char) * (i + 2));

			if (!line)
				sys_exit();

			buffer[i] = '\0';

			strcpy(line, buffer);
			line[i+0] = '\n';
			line[i+1] = '\0';

			strcpy(buffer, &buffer[i+1]);

			break ;
		}

		++i;
	}

	return line;
}

// Message
typedef struct s_message
{
	char * content;
	size_t length;
	size_t offset;

	struct s_message * next;
} t_message;

t_message * message_new()
{
	t_message * message = malloc(sizeof(t_message));

	if (!message)
		sys_exit();

	message->content = NULL;
	message->length = 0;
	message->offset = 0;
	message->next = NULL;

	return message;
}

t_message * messages_push(t_message * messages, t_message * message)
{
	if (!messages)
		return message;

	t_message * last = messages;

	while (last->next)
		last = last->next;

	last->next = message;

	return messages;
}

t_message * messages_delete_first(t_message * messages)
{
	if (!messages)
		return NULL;

	t_message * next = messages->next;

	free(messages->content);
	free(messages);

	return next;
}

t_message * messages_clear(t_message * messages)
{
	while (messages)
		messages = messages_delete_first(messages);

	return messages;
}

// Client
typedef unsigned t_id;
typedef struct s_client
{
	t_id id;
	t_fd fd;

	struct sockaddr_in addr;

	char * buffer;
	t_message * messages;

	struct s_client * prev;
	struct s_client * next;
} t_client;

t_client * client_new()
{
	static t_id id = 0;

	t_client * client = malloc(sizeof(t_client));

	if (!client)
		sys_exit();

	client->id = id++;
	client->fd = -1;

	bzero(&client->addr, sizeof(client->addr));

	client->buffer = NULL;
	client->messages = NULL;

	client->prev = NULL;
	client->next = NULL;

	return client;
}

t_client * clients_push(t_client * clients, t_client * client)
{
	if (!clients)
		return client;

	t_client * last = clients;

	while (last->next)
		last = last->next;

	last->next = client;
	client->prev = last;

	return clients;
}

t_client * clients_delete(t_client * clients, t_client * client)
{
	if (!client->prev)
		clients = client->next;

	if (client->prev) client->prev->next = client->next;
	if (client->next) client->next->prev = client->prev;

	close(client->fd);
	messages_clear(client->messages);
	free(client->buffer);
	free(client);

	return clients;
}

t_client * clients_clear(t_client * clients)
{
	while (clients)
		clients = clients_delete(clients, clients);

	return clients;
}

// Server
typedef uint16_t t_port;
typedef struct s_server
{
	t_fd fd;
	t_port port;

	struct sockaddr_in addr;

	fd_set master_set;

	t_client * clients;
} t_server;

void server_start(t_server * server, t_port port)
{
	server->fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server->fd == -1)
		sys_exit();

	server->port = port;

	bzero(&server->addr, sizeof(server->addr));

	server->addr.sin_family = AF_INET;
	server->addr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	server->addr.sin_port = htons(port);

	if ((bind(server->fd, (const struct sockaddr *)&server->addr, sizeof(server->addr))) != 0)
		sys_exit();
	if (listen(server->fd, 10) != 0)
		sys_exit();

	FD_ZERO(&server->master_set);
	FD_SET(server->fd, &server->master_set);

	server->clients = NULL;
}

void server_stop(t_server * server)
{
	close(server->fd);
	clients_clear(server->clients);
}

t_client * server_accept(t_server * server)
{
	t_client * client = client_new();
	socklen_t addr_len = sizeof(client->addr);

	client->fd = accept(server->fd, (struct sockaddr *)&client->addr, &addr_len);

	if (client->fd == -1)
		sys_exit();

	FD_SET(client->fd, &server->master_set);

	server->clients = clients_push(server->clients, client);

	return client;
}

t_client * server_cancel(t_server * server, t_client * client)
{
	t_client * prev = client->prev;

	FD_CLR(client->fd, &server->master_set);

	server->clients = clients_delete(server->clients, client);

	return prev;
}

void server_broadcast(t_server * server, t_client * sender, char * content)
{
	t_client * client = server->clients;
	t_message * message = NULL;
	size_t content_len = strlen(content);

	while (client)
	{
		if (&*client != &*sender)
		{
			message = message_new();
			message->content = str_join(content, NULL);
			message->length  = content_len;

			client->messages = messages_push(client->messages, message);
		}

		client = client->next;
	}
}

void server_recv(t_server * server, t_client * client, char * buffer_server, char * buffer_client)
{
	char * old_content = client->buffer;
	client->buffer = str_join(old_content, buffer_client);
	free(old_content);

	char * line = NULL;
	char * content = NULL;
	while ((line = get_line(client->buffer)))
	{
		content = str_join(buffer_server, line);

		server_broadcast(server, client, content);

		free(content);
		free(line);
	}
}

void server_send(t_client * client)
{
	t_message * message = client->messages;

	if (!message)
		return ;

	char * content = message->content + message->offset;
	ssize_t send_len = send(client->fd, content, strlen(content), MSG_DONTWAIT);

	if (send_len <= 0)
		return ;

	message->offset += send_len;

	if (message->offset >= message->length)
		client->messages = messages_delete_first(client->messages);
}

void server_loop(t_server * server)
{
	char buffer_server[64];
	char buffer_client[1024 * 128];

	fd_set read_set;
	fd_set write_set;

	t_fd max_fd = server->fd;

	while (1)
	{
		// Select
		read_set = server->master_set;
		write_set = server->master_set;

		if (select(max_fd + 1, &read_set, &write_set, NULL, NULL) < 0)
			continue ;

		// Server
		if (FD_ISSET(server->fd, &read_set))
		{
			t_client * client = server_accept(server);

			if (client->fd > max_fd)
				max_fd = client->fd;

			sprintf(buffer_server, "server: client %d just arrived\n", client->id);
			server_broadcast(server, client, buffer_server);
		}

		// Clients
		t_client * client = server->clients;
		while (client)
		{
			// Write
			if (FD_ISSET(client->fd, &write_set))
			{
				server_send(client);
			}

			// Read
			if (FD_ISSET(client->fd, &read_set))
			{
				ssize_t recv_len = recv(client->fd, buffer_client, sizeof(buffer_client) - 1, MSG_DONTWAIT);

				// Quit
				if (recv_len == 0)
				{
					sprintf(buffer_server, "server: client %d just left\n", client->id);
					server_broadcast(server, client, buffer_server);

					client = server_cancel(server, client);
				}
				// Message
				else if (recv_len > 0)
				{
					buffer_client[recv_len] = '\0';

					sprintf(buffer_server, "client %d: ", client->id);

					server_recv(server, client, buffer_server, buffer_client);
				}
			}

			client = client ? client->next : server->clients;
		}
	}
}

// Main
int main(int ac, char *av[])
{
	if (ac != 2)
	{
		io_put_err("Wrong number of arguments\n");
		exit(SYS_EXIT_ERR);
	}

	t_server server;

	server_start(&server, atoi(av[1]));
	server_loop(&server);
	server_stop(&server);

	return SYS_EXIT_OK;
}
