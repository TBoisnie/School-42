/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:18:20 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 17:12:40 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_HPP
# define ENEMY_HPP

# include <string>

class Enemy
{
private:
	// Attributes
	std::string type;
	int hp;

private:
	Enemy();

public:
	// Constructors & Destructors
	Enemy(int hp, const std::string & type);
	Enemy(const Enemy & other);
	virtual ~Enemy();

	// Operators
	Enemy & operator=(const Enemy & other);

	// Methods
	virtual void takeDamage(int damage);

	// Getters & Setters
	const std::string & getType() const;
	int	getHP() const;

	void setType(const std::string & type);
	void setHP(int hp);
};

#endif