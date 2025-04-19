/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:22:28 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 15:27:43 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_WEAPON_HPP
# define A_WEAPON_HPP

# include <string>

class AWeapon
{
private:
	// Attributes
	std::string name;
	int ap_cost;
	int damage;

private:
	AWeapon();

public:
	// Constructors & Destructors
	AWeapon(const std::string & name, int ap_cost, int damage);
	AWeapon(const AWeapon & other);
	virtual ~AWeapon();

	// Operators
	AWeapon & operator=(const AWeapon & other);

	// Methods
	virtual void attack() const = 0;

	// Getters & Setters
	const std::string & getName() const;
	int	getAPCost() const;
	int getDamage() const;

	void setName(const std::string & name);
	void setAPCost(int ap_cost);
	void setDamage(int damage);
};

#endif