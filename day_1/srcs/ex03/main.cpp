/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 20:24:53 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:44:09 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ZombieHorde.hpp"

int main()
{
	unsigned n = 10;

	std::cout << "Your raid has " << Zombie::alive << " zombie." << std::endl;

	{
		ZombieHorde zh = ZombieHorde(n);
		zh.announce();

		std::cout << "Your raid has " << Zombie::alive << " zombies." << std::endl;
	}

	std::cout << "Your raid has " << Zombie::alive << " zombie." << std::endl;

	return 0;
}
