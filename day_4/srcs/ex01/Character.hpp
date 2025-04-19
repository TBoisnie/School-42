/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:39:18 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 14:49:01 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <string>
# include "AWeapon.hpp"
# include "Enemy.hpp"

class Character
{
private:
	// Attributes
	std::string name;
	int ap;
	AWeapon * weapon;

private:
	Character();

public:
	// Constructors & Destructors
	Character(const std::string & name);
	Character(const Character & other);
	~Character();

	// Operators
	Character & operator=(const Character & other);

	// Methods
	void recoverAP();
	void equip(AWeapon * weapon);
	void attack(Enemy * enemy);

	// Getters & Setters
	const std::string & getName() const;
	const AWeapon * getWeapon() const;
	int getAP() const;
};

// Overload
std::ostream & operator<<(std::ostream & out, const Character & character);

#endif