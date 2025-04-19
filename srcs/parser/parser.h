/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:49:54 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/10 22:33:31 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <sys/types.h>
# include "../cube3d.h"

void	valid_wall(t_config *c);

void	set_sprite(t_config *c, int x);
void	set_player(t_config *c, char dir, int x);

void	parse_definition(t_config *c, char *line);
void	parse_texture(t_config *c, char *line, t_texture_index index);
void	parse_color(t_config *c, char *line, int sky);
void	parse_world(t_config *c, int fd, char **line, ssize_t *c_read);

void	parse(t_config *c, char *filepath);

#endif
