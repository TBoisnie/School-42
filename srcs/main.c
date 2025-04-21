#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PIPE_OUT	0
#define PIPE_IN		1

#define IO_IN		0
#define IO_OUT		1
#define IO_ERR		2

#define EXIT_OK		0
#define EXIT_ERR	1

// Structs / Enums
typedef enum	e_type
{
	NONE  = 0,
	PIPED = 1,
	END   = 2
}				t_type;

typedef struct	s_cmd
{
	char ** args;

	int pipes[2];

	t_type type;

	struct s_cmd * prev;
	struct s_cmd * next;
}				t_cmd;

// Generals
size_t
str_length(
	const char * str
)
{
	const char * start = str;

	while (*str)
		++str;

	return (str - start);
}

ssize_t
str_cmp(
	const char * str_a,
	const char * str_b
)
{
	return strcmp(str_a, str_b);
}

void
io_put_err(
	const char * str
)
{
	write(IO_ERR, str, str_length(str));
}

void
sys_exit(
	const char * str
)
{
	if (str)
		io_put_err(str);
	else
		io_put_err("error: fatal\n");

	exit(EXIT_ERR);
}

// Commands
t_cmd *
cmd_new()
{
	t_cmd * cmd = NULL;

	if (!(cmd = malloc(sizeof(t_cmd))))
		sys_exit(NULL);

	cmd->args = NULL;
	cmd->type = NONE;
	cmd->prev = NULL;
	cmd->next = NULL;

	return (cmd);
}

size_t
cmd_args_count(
	const t_cmd * cmd
)
{
	size_t count = 0;

	while (cmd->args && cmd->args[count])
		++count;

	return (count);
}

void
cmd_args_add(
	t_cmd * cmd,
	char * arg
)
{
	size_t args_count = cmd_args_count(cmd);
	char ** args_tmp = NULL;

	if (!(args_tmp = malloc(sizeof(char*) * (args_count + 2))))
		sys_exit(NULL);

	size_t i = 0;

	while (i < args_count)
	{
		args_tmp[i] = cmd->args[i];
		++i;
	}
	args_tmp[i++] = arg;
	args_tmp[i] = NULL;

	free(cmd->args);
	cmd->args = args_tmp;
}

void
cmd_clear(
	t_cmd * cmd
)
{
	t_cmd * next = cmd;

	while (cmd)
	{
		next = cmd->next;

		// No need to delete each args,
		// they are pointers to `char *` from main() char * av[]`.
		free(cmd->args);
		free(cmd);

		cmd = next;
	}
}


// Parsing
t_cmd *
parse_cmds(
	int ac,
	char * av[]
)
{
	t_cmd * first = NULL;
	t_cmd * current = NULL;

	int i = 1;

	while (i < ac)
	{
		if (!str_cmp(av[i], ";"))
		{
			if (current && cmd_args_count(current) > 0)
				current->type = END;
		}
		else if (!str_cmp(av[i], "|"))
		{
			current->type = PIPED;
		}
		else
		{
			if (!first)
			{
				current = cmd_new();
				first = current;
			}
			if (current->type != NONE)
			{
				current->next = cmd_new();
				current->next->prev = current;
				current = current->next;
			}

			cmd_args_add(current, av[i]);
		}

		++i;
	}

	if (current && current->type == NONE)
	{
		current->type = END;
	}

	return (first);
}

// Execution
int
execute(
	t_cmd * cmd,
	char * env[]
)
{
	int exit_code = EXIT_ERR;
	int status = 0;
	pid_t pid = 0;

	if (cmd->type == PIPED && pipe(cmd->pipes))
		sys_exit(NULL);

	if ((pid = fork()) == -1)
		sys_exit(NULL);

	if (pid == 0) // Child
	{
		if (cmd->type == PIPED)
			close(cmd->pipes[PIPE_OUT]);
		if (cmd->type == PIPED && dup2(cmd->pipes[PIPE_IN], IO_OUT) < 0)
			sys_exit(NULL);
		if (cmd->prev && cmd->prev->type == PIPED && dup2(cmd->prev->pipes[PIPE_OUT], IO_IN) < 0)
			sys_exit(NULL);
		if ((status = execve(cmd->args[0], cmd->args, env)))
		{
			io_put_err("error: cannot execute ");
			io_put_err(cmd->args[0]);
			io_put_err("\n");
		}
		if (cmd->type == PIPED)
			close(cmd->pipes[PIPE_IN]);
		exit(status);
	}
	else // Parent
	{
		if (cmd->type == PIPED)
			close(cmd->pipes[PIPE_IN]);

		if (waitpid(pid, &status, 0) < 0)
			sys_exit(NULL);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);

		if (cmd->prev && cmd->prev->type == PIPED)
			close(cmd->prev->pipes[PIPE_OUT]);
	}

	return (exit_code);
}

int
run(
	t_cmd * cmds,
	char * env[]
)
{
	int exit_code = EXIT_OK;

	t_cmd * current = cmds;

	while (current)
	{
		if (!str_cmp(current->args[0], "cd"))
		{
			if (cmd_args_count(current) < 2)
			{
				io_put_err("error: cd: bad arguments\n");
			}
			else
			{
				exit_code = EXIT_OK;

				if (chdir(current->args[1]))
				{
					io_put_err("error: cd: cannot change directory to ");
					io_put_err(current->args[1]);
					io_put_err("\n");

					exit_code = EXIT_ERR;
				}
			}
		}
		else
		{
			exit_code = execute(current, env);
		}

		current = current->next;
	}

	return (exit_code);
}

// Main
int
main(
	int ac,
	char * av[],
	char * env[]
)
{
	int exit_code = EXIT_OK;

	t_cmd * cmds = parse_cmds(ac, av);

	exit_code = run(cmds, env);

	cmd_clear(cmds);

	// (void)env;
	// getchar();

	return (exit_code);
}