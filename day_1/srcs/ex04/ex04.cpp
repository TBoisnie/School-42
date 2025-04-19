/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex04.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:22:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/03 01:54:57 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int
main()
{
	std::string str = "HI THIS IS BRAIN";
	std::string *p_str = &str;
	std::string &r_str = str;

	std::cout << *p_str << std::endl;
	std::cout << r_str << std::endl;

	return 0;
}