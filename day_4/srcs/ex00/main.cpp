/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 20:50:53 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/22 14:47:46 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sorcerer.hpp"
#include "Victim.hpp"
#include "Peon.hpp"

int main()
{
	Sorcerer robert("Robert", "the Magnificent");

	Victim jim("Jimmy");
	Peon joe("Joe");

	std::cout << std::endl;
	{
		Sorcerer robert_cpy(robert);
		Victim jim_cpy(jim);
		Peon joe_cpy(joe);

		robert = robert_cpy;
		jim = jim_cpy;
		joe = joe_cpy;
	}
	std::cout << std::endl;

	std::cout << robert << jim << joe;

	robert.polymorph(jim);
	robert.polymorph(joe);

	std::cout << std::endl;

	return 0;
}