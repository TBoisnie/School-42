/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:32:38 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/04 17:19:38 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHI_H
# define PHI_H

# include "config/config.h"

void	phi_set_status(t_config *c, size_t pos, t_phi_status s, int lock);
int		phi_live_start(t_config *c, t_args *args);
int		phi_live_wait(t_config *c);

#endif
