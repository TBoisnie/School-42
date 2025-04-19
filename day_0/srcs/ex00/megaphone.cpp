/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:50:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/07 22:21:17 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main (int ac, char *av[])
{
	if (ac <= 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	else
	{
		std::string	str;

		for (int i = 1; i < ac ; i++)
		{
			for (char *cursor = av[i]; *cursor; cursor++)
			{
				str.append(1, toupper(*cursor));
			}
		}

		std::cout << str << std::endl;
	}

	return (0);
}