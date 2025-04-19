/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 21:18:23 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 21:33:23 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "command/command.h"
# include "environnement/env.h"

typedef struct	s_state
{
	int		file_in;
	int		file_out;
	t_bool	append;
	char	*word;
	int		error_code;
	int		in_quote;
}				t_state;

void			parser_state_init(t_state *state);
t_bool			parser_state_is_clean(t_state *st);

t_cmd			*parser_parse(char *str, t_env env, int prev_exit_code,
					int *error);

char			*parser_backslash(t_state *st, char *cursor);
char			*parser_d_quote(t_state *st, char *cursor, t_env env,
					int exit_code);
char			*parser_s_quote(t_state *st, char *cursor);
char			*parser_default(t_state *st, char *cursor);
char			*parser_pipe(t_cmd *left, t_state *st, char *cursor);
char			*parser_redirect_in(t_state *st, char *cursor);
char			*parser_redirect_out(t_state *st, char *cursor);
char			*parser_variable(t_state *st, char *cursor, t_env env,
					int exit_code);

unsigned		get_bs_count(char *str, char *end);
char			*remove_mult_space(char *str);

char			*parser_get_next(char *str);
t_cmd			*parser_save_word(t_cmd *cmd, t_state *st);

t_cmd			*check_execute(t_cmd *cmd, t_env env);
int				check_command(char *line, t_env *env);

#endif
