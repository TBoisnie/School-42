/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 23:01:14 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 01:39:31 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ISquad.hpp"
#include "Squad.hpp"
#include "ISpaceMarine.hpp"
#include "TacticalMarine.hpp"
#include "AssaultTerminator.hpp"

int main()
{

	ISquad * squad = new Squad();

	ISpaceMarine * unit_tm = new TacticalMarine();
	ISpaceMarine * unit_at = new AssaultTerminator();

	std::cout << std::endl;

	squad->push(unit_tm);
	squad->push(unit_at);
	std::cout << "Squad has " << squad->getCount() << " units." << std::endl;

	squad->push(unit_tm);
	squad->push(unit_at->clone());
	std::cout << "Squad has " << squad->getCount() << " units." << std::endl;

	std::cout << std::endl;

	for (int i = 0; i < squad->getCount(); ++i)
	{
		ISpaceMarine * cur = squad->getUnit(i);
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}

	std::cout << "--------------" << std::endl;

	{
		Squad * s_a = new Squad();

		s_a->push(unit_at->clone());
		s_a->push(unit_tm->clone());
		std::cout << std::endl << "Squad (s_a) has " << s_a->getCount() << " units." << std::endl;

		std::cout << std::endl;

		Squad s_b(*s_a);
		std::cout << std::endl << "Squad (s_b) has " << s_b.getCount() << " units." << std::endl;

		std::cout << std::endl;

		delete s_a;

		std::cout << std::endl;

		for (int i = 0; i < 5; ++i)
		{
			s_b.push(unit_at->clone());
			s_b.push(unit_tm->clone());
		}
		std::cout << std::endl << "Squad (s_b) has " << s_b.getCount() << " units." << std::endl;

		std::cout << std::endl;

		for (int i = 0; i < s_b.getCount(); ++i)
		{
			s_b.getUnit(i)->battleCry();
		}

		std::cout << std::endl;
	}

	std::cout << "--------------" << std::endl;

	delete squad;

	return 0;
}