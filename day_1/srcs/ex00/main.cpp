/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 20:42:30 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/07 23:22:55 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Pony.hpp"

void
ponyOnTheStack()
{
	Pony	pony = Pony("RainbowDash", "White");

	std::cout << "The Pony named '" << pony.getName() << "' is born "
		<< pony.getColor() << "." << std::endl;

	std::cout << "PonyLand has " << Pony::getCount() << " pony." << std::endl;

	std::cout << "It tries to run for the first time and... " << std::endl;

	pony.run();
	pony.run();

	std::cout << "Success! " << pony.getName() << " ran " << pony.getRan()
		<< " meters, but it feels tired now (" << pony.getEnergy() << "%)."
		<< std::endl;

	pony.rest();

	std::cout << "So it take a nap to get its energy back (" << pony.getEnergy() << "%)."
		<< std::endl;

	for (int i = 0; i < 100; i++)
	{
		if (pony.getEnergy() <= 30)
			pony.rest();
		else
			pony.run();
	}

	std::cout << "Finally, " << pony.getName() << " grews up, and had a long life."
		<< std::endl;
	std::cout << "It died after running " << pony.getRan() << " kilometers."
		<< std::endl;
}

void
ponyOnTheHeap()
{
	Pony *pony = new Pony("PinkiePie", "Pink");

	std::cout << "The Pony named '" << pony->getName() << "' is born "
		<< pony->getColor() << "." << std::endl;

	std::cout << "PonyLand has " << Pony::getCount() << " pony." << std::endl;

	std::cout << "It tries to run for the first time and... " << std::endl;

	pony->run();

	std::cout << "Success! " << pony->getName() << " ran " << pony->getRan()
		<< " meters, but it feels tired now (" << pony->getEnergy() << "%)."
		<< std::endl;

	pony->rest();

	std::cout << "So it take a nap to get its energy back (" << pony->getEnergy() << "%)."
		<< std::endl;

	for (int i = 0; i < 75; i++)
	{
		if (pony->getEnergy() <= 20)
			pony->rest();
		else
			pony->run();
	}

	std::cout << "Finally, " << pony->getName() << " grews up, and had a long life."
		<< std::endl;
	std::cout << "It died after running " << pony->getRan() << " kilometers."
		<< std::endl;

	delete pony;
}

int
main()
{
	std::cout << "PonyLand has " << Pony::getCount() << " pony." << std::endl;
	std::cout << std::endl;
	ponyOnTheStack();
	std::cout << std::endl;
	std::cout << "PonyLand has " << Pony::getCount() << " pony." << std::endl;
	std::cout << std::endl;
	ponyOnTheHeap();
	std::cout << std::endl;
	std::cout << "PonyLand has " << Pony::getCount() << " pony." << std::endl;

	return 0;
}