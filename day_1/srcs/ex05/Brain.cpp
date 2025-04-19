/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:26:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:52:53 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>
#include "Brain.hpp"

std::string
Brain::identify() const
{
	std::ostringstream oss;

	oss << "0x" << std::uppercase << std::hex << (unsigned long)this;

	return oss.str();
}