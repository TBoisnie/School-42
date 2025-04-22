#include "commands/hash.h"
#include "ft_ssl.h"

int
main(
	int _argc,
	char const * _argv[]
)
{
	t_command const commands[] =
	{
		{ .name = "md5",       .func = cmd_md5       },
		{ .name = "sha256",    .func = cmd_sha256    },
		{ .name = "whirlpool", .func = cmd_whirlpool },
	};

	if ( _argc < 2 )
	{
		ft_io_out_str(USAGE);
		return (1);
	}

	t_size i;
	for ( i = 0 ; i < FT_ARRAY_SIZE(commands) ; i++ )
	{
		t_command const * cmd = &commands[i];

		if ( ft_str_compare(_argv[1], cmd->name) == 0 )
		{
			return ((cmd->func)(_argc - 2, _argv + 2));
		}
	}

	ft_io_out_str(USAGE);
	return (1);
}
