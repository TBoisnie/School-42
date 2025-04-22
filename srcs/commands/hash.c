#include "algorithms/hash.h"
#include "commands/hash.h"

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

// Define ----------------------------------------------------------------------
#define USAGE  \
	"usage: ft_ssl <algorithm> [-hpqr] [-s <str>]... [file]...\n" \
	"\n" \
	"Arguments:\n" \
	"  algorithm\tHashing algorithm (md5, sha256)\n" \
	"  file\t\tFile to read from\n" \
	"Flags:\n" \
	"  -h\t\tDisplay this help and exit\n" \
	"  -p\t\tEcho STDIN to STDOUT and append the checksum to STDOUT\n" \
	"  -q\t\tQuiet mode\n" \
	"  -r\t\tReverse the format of the output\n" \
	"  -s <str>\tPrint the sum of the given <str>\n" \
	"\n"

// Typedef ---------------------------------------------------------------------
typedef struct s_options t_options;
typedef struct s_state t_state;

// Enum ------------------------------------------------------------------------
enum e_flags
{
	F_HELP    = 1 << 0,
	F_IN_OUT  = 1 << 1,
	F_QUIET   = 1 << 2,
	F_REVERSE = 1 << 3,
};

// Struct ----------------------------------------------------------------------
struct s_options
{
	t_uint flags;
};

struct s_state
{
	t_char const * const name;
	t_char const * const prefix;

	t_byte const * input;
	t_size input_size;
	t_byte * const digest;
	t_size const digest_size;

	t_bool (* const hash_file)(t_byte * _buffer, t_fd _fd);
	t_void (* const hash_memory)(t_byte * _buffer, t_byte const * _mem, t_size _size);
};

// Static ----------------------------------------------------------------------
static t_void
_print_input(
	t_byte const * _input,
	t_size _size,
	t_char const * _prefix,
	t_char const * _suffix
)
{
	ft_io_out_format("%s", _prefix);

	t_size i;

	for ( i = 0 ; i < _size ; i++ )
	{
		if (
			ft_chr_is_print(_input[i])
			&& ( ! ft_chr_is_space(_input[i]) || ft_chr_is_blank(_input[i]) )
		)
		{
			ft_io_out_format("%c", _input[i]);
		}
	}

	ft_io_out_format("%s", _suffix);
}

static t_void
_print_digest(
	t_byte const * _digest,
	t_size _size
)
{
	t_size i;

	for ( i = 0 ; i < _size ; i++ )
	{
		ft_io_out_format("%02x", _digest[i]);
	}
}

static t_void
_print_stdin(
	t_options const * _options,
	t_state const * _state
)
{
	if ( FT_MEM_BIT_ISSET(_options->flags, F_IN_OUT) )
	{
		if ( FT_MEM_BIT_ISSET(_options->flags, F_QUIET) )
		{
			_print_input(_state->input, _state->input_size, "", "\n");
			_print_digest(_state->digest, _state->digest_size);
		}
		else
		{
			_print_input(_state->input, _state->input_size, "(\"", "\")= ");
			_print_digest(_state->digest, _state->digest_size);
		}
	}
	else
	{
		if ( FT_MEM_BIT_ISSET(_options->flags, F_QUIET) )
		{
			_print_digest(_state->digest, _state->digest_size);
		}
		else if ( FT_MEM_BIT_ISSET(_options->flags, F_REVERSE) )
		{
			_print_digest(_state->digest, _state->digest_size);
			_print_input(_state->input, _state->input_size, " *", "");
		}
		else
		{
			_print_input(_state->input, _state->input_size, "(", ")= ");
			_print_digest(_state->digest, _state->digest_size);
		}
	}

	ft_io_out_format("\n");
}

static t_void
_print_str(
	t_options const * _options,
	t_state const * _state
)
{
	if ( FT_MEM_BIT_ISSET(_options->flags, F_QUIET) )
	{
		_print_digest(_state->digest, _state->digest_size);
	}
	else if ( FT_MEM_BIT_ISSET(_options->flags, F_REVERSE) )
	{
		_print_digest(_state->digest, _state->digest_size);
		ft_io_out_format(" \"%s\"", _state->input);
	}
	else
	{
		ft_io_out_format("%s (\"%s\") = ", _state->prefix, _state->input);
		_print_digest(_state->digest, _state->digest_size);
	}

	ft_io_out_format("\n");
}

static t_void
_print_file(
	t_options const * _options,
	t_state const * _state
)
{
	if ( FT_MEM_BIT_ISSET(_options->flags, F_QUIET) )
	{
		_print_digest(_state->digest, _state->digest_size);
	}
	else if ( FT_MEM_BIT_ISSET(_options->flags, F_REVERSE) )
	{
		_print_digest(_state->digest, _state->digest_size);
		ft_io_out_format(" %s", _state->input);
	}
	else
	{
		ft_io_out_format("%s (%s) = ", _state->prefix, _state->input);
		_print_digest(_state->digest, _state->digest_size);
	}

	ft_io_out_format("\n");
}

static t_int
_hash_stdin(
	t_options const * _options,
	t_state * _state,
	t_char const *** _args_ptr
)
{
	t_int status = 0;
	t_char const ** args = *_args_ptr;

	if ( FT_MEM_BIT_ISSET(_options->flags, F_IN_OUT) )
	{
		t_byte buffer[512];
		t_ssize length;

		while ( (length = read(FT_IO_CONSOLE_FD_IN, buffer, sizeof(buffer))) > 0 )
		{
			t_byte * join = ft_mem_join(_state->input, buffer, _state->input_size, length);

			free((t_char *) _state->input);

			_state->input = join;
			_state->input_size += length;

			if ( ! _state->input )
			{
				status |= 1;
				ft_io_err_format("ft_ssl: %s: stdin: ft_str_join failed\n", _state->name);
				break;
			}
		}

		if ( _state->input )
		{
			(_state->hash_memory)(_state->digest, _state->input, _state->input_size);
			_print_stdin(_options, _state);
		}

		free((t_char *) _state->input);
	}
	else if ( ! *args )
	{
		t_bool failed = (_state->hash_file)(_state->digest, FT_IO_CONSOLE_FD_IN);

		_state->input = "stdin";
		_state->input_size = 5;

		if ( failed )
		{
			status |= 1;
			ft_io_err_format("ft_ssl: %s: %s: %s\n", _state->name, _state->input, strerror(errno));
		}
		else
		{
			_print_stdin(_options, _state);
		}
	}

	return (status);
}

static t_int
_hash_strings(
	t_options const * _options,
	t_state * _state,
	t_char const *** _args_ptr
)
{
	t_int status = 0;
	t_char const ** args = *_args_ptr;

	while ( *args )
	{
		if ( ft_str_compare("-s", *args) )
		{
			break;
		}

		_state->input = *++args;

		if ( ! _state->input )
		{
			status |= 1;
			ft_io_err_format("ft_ssl: %s: invalid option -'s': missing value\n", _state->name);
			break;
		}

		(_state->hash_memory)(_state->digest, _state->input, ft_str_length(_state->input));
		_print_str(_options, _state);

		args++;
	}

	*_args_ptr = args;

	return (status);
}

static t_int
_hash_files(
	t_options const * _options,
	t_state * _state,
	t_char const *** _args_ptr
)
{
	t_int status = 0;
	t_char const ** args = *_args_ptr;

	while ( *args )
	{
		_state->input = *args++;

		t_fd const fd = open(_state->input, O_RDONLY);

		if ( fd == -1 )
		{
			status |= 1;
			ft_io_err_format("ft_ssl: %s: %s: %s\n", _state->name, _state->input, strerror(errno));
			continue;
		}

		t_bool const failed = (_state->hash_file)(_state->digest, fd);

		if ( failed )
		{
			status |= 1;
			ft_io_err_format("ft_ssl: %s: %s: %s\n", _state->name, _state->input, strerror(errno));
		}
		else
		{
			_print_file(_options, _state);
		}

		close(fd);
	}

	*_args_ptr = args;

	return (status);
}

static t_int
_execute(
	t_state * _state,
	t_char const * _args[]
)
{
	t_options options =
	{
		.flags = 0,
	};

	// Flags
	while ( *_args )
	{
		if ( (*_args)[0] != '-' || (*_args)[1] == 's' )
		{
			break;
		}

		t_char const * arg = *_args++;

		if ( arg[1] == '\0' )
		{
			ft_io_err_format("ft_ssl: %s: invalid option -''\n", _state->name);
			return (1);
		}

		while ( *++arg != '\0' )
		{
			switch ( *arg )
			{
				case 'h':
					ft_io_out_str(USAGE);
					return (0);
				case 'r':
					FT_MEM_BIT_SET(options.flags, F_REVERSE);
					break;
				case 'q':
					FT_MEM_BIT_SET(options.flags, F_QUIET);
					break;
				case 'p':
					FT_MEM_BIT_SET(options.flags, F_IN_OUT);
					break;
				default:
					ft_io_err_format("ft_ssl: %s: invalid option -'%c'\n", _state->name, *arg);
					return (1);
			}
		}
	}

	t_int status = 0;

	status |= _hash_stdin(&options, _state, &_args);
	status |= _hash_strings(&options, _state, &_args);
	status |= _hash_files(&options, _state, &_args);

	return (status);
}

// Function --------------------------------------------------------------------
t_int
cmd_md5(
	t_uint _argc,
	t_char const * _argv[]
)
{
	t_byte digest[MD5_DIGEST_SIZE];

	t_state state =
	{
		.name = "md5",
		.prefix = "MD5",
		.input = nullptr,
		.input_size = 0,
		.digest = digest,
		.digest_size = MD5_DIGEST_SIZE,
		.hash_file = &md5_file,
		.hash_memory = &md5_memory,
	};

	return (_execute(&state, _argv));
}

t_int
cmd_sha256(
	t_uint _argc,
	t_char const * _argv[]
)
{
	t_byte digest[SHA256_DIGEST_SIZE];

	t_state state =
	{
		.name = "sha256",
		.prefix = "SHA256",
		.input = nullptr,
		.input_size = 0,
		.digest = digest,
		.digest_size = SHA256_DIGEST_SIZE,
		.hash_file = &sha256_file,
		.hash_memory = &sha256_memory,
	};

	return (_execute(&state, _argv));
}

t_int
cmd_whirlpool(
	t_uint _argc,
	t_char const * _argv[]
)
{
	t_byte digest[WHIRLPOOL_DIGEST_SIZE];

	t_state state =
	{
		.name = "whirlpool",
		.prefix = "WHIRLPOOL",
		.input = nullptr,
		.input_size = 0,
		.digest = digest,
		.digest_size = WHIRLPOOL_DIGEST_SIZE,
		.hash_file = &whirlpool_file,
		.hash_memory = &whirlpool_memory,
	};

	return (_execute(&state, _argv));
}
