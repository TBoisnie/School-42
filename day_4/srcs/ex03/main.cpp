/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:34:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 16:09:29 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"

int main()
{
	ICharacter * me = new Character("me");
	ICharacter * enemy = new Character("enemy");

	IMateriaSource* src = new MateriaSource();

	AMateria * materia;

	Ice * ice = new Ice();
	Cure * cure = new Cure();

	src->learnMateria(ice);
	src->learnMateria(cure);

	materia = src->createMateria("ice");
	me->equip(materia);
	materia = src->createMateria("cure");
	me->equip(materia);

	me->use(0, *enemy);
	me->use(1, *enemy);

	std::cout << "---------------" << std::endl;

	{
		Character * c_a = new Character("nobody");

		c_a->equip(src->createMateria("ice"));
		c_a->equip(src->createMateria("cure"));
		c_a->equip(src->createMateria("ice"));

		c_a->use(0, *enemy);
		c_a->use(0, *enemy);
		c_a->use(0, *enemy);
		c_a->use(1, *enemy);
		c_a->use(2, *enemy);

		std::cout << std::endl;

		materia = c_a->getMateria(0);
		std::cout
			<< "Character's (c_a) materia (0) has type " << materia->getType()
			<< " and " << materia->getXP() << "xp." << std::endl;
		materia = c_a->getMateria(1);
		std::cout
			<< "Character's (c_a) materia (1) has type " << materia->getType()
			<< " and " << materia->getXP() << "xp." << std::endl;
		materia = c_a->getMateria(2);
		std::cout
			<< "Character's (c_a) materia (2) has type " << materia->getType()
			<< " and " << materia->getXP() << "xp." << std::endl;

		c_a->unequip(2);

		delete materia;

		std::cout << std::endl;

		Character c_b(*c_a);

		materia = c_b.getMateria(0);
		std::cout
			<< "Character's (c_b) materia (0) has type " << materia->getType()
			<< " and " << materia->getXP() << "xp." << std::endl;
		materia = c_b.getMateria(1);
		std::cout
			<< "Character's (c_b) materia (1) has type " << materia->getType()
			<< " and " << materia->getXP() << "xp." << std::endl;

		std::cout << std::endl;

		c_a->use(0, *enemy);

		materia = c_a->getMateria(0);
		std::cout
			<< "Character's (c_a) materia (0) has type " << materia->getType()
			<< " and " << materia->getXP() << "xp." << std::endl;
		materia = c_b.getMateria(0);
		std::cout
			<< "Character's (c_b) materia (0) has type " << materia->getType()
			<< " and " << materia->getXP() << "xp." << std::endl;

		delete c_a;
	}

	std::cout << "---------------" << std::endl;

	delete me;
	delete enemy;
	delete src;
	delete ice;
	delete cure;

	return 0;
}