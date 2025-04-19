/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:21:12 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/22 15:08:36 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Character.hpp"
#include "Enemy.hpp"
#include "RadScorpion.hpp"
#include "SuperMutant.hpp"
#include "AWeapon.hpp"
#include "PlasmaRifle.hpp"
#include "PowerFist.hpp"

int main()
{
	Character me("Isaac");

	Enemy * enemy_rs = new RadScorpion();
	Enemy * enemy_sm = new SuperMutant();

	AWeapon * weapon_pr = new PlasmaRifle();
	AWeapon * weapon_pf = new PowerFist();

	std::cout << std::endl;

	// Character
	std::cout << me;

	std::cout << std::endl;

	// Weapon - Plasma Rifle
	me.equip(weapon_pr);
	std::cout << me;

	std::cout << std::endl;

	me.attack(enemy_rs);
	std::cout << enemy_rs->getType() << " has " << enemy_rs->getHP() << "hp" << std::endl;
	me.attack(enemy_sm);
	std::cout << enemy_sm->getType() << " has " << enemy_sm->getHP() << "hp" << std::endl;

	std::cout << std::endl;

	// Weapon - Power Fist
	me.equip(weapon_pf);
	std::cout << me;

	std::cout << std::endl;

	me.attack(enemy_rs);
	std::cout << enemy_rs->getType() << " has " << enemy_rs->getHP() << "hp" << std::endl;
	me.attack(enemy_sm);
	std::cout << enemy_sm->getType() << " has " << enemy_sm->getHP() << "hp" << std::endl;

	std::cout << std::endl;

	// Rest
	std::cout << me;
	me.recoverAP();
	me.recoverAP();
	me.recoverAP();
	me.recoverAP();
	std::cout << me;

	std::cout << std::endl;

	// Kill - Enemies
	me.attack(enemy_rs);
	me.attack(enemy_sm);
	me.attack(enemy_sm);
	me.attack(enemy_sm);
	std::cout << me;

	std::cout << std::endl;

	me.equip(NULL);
	std::cout << me;

	delete weapon_pr;
	delete weapon_pf;

	return 0;
}