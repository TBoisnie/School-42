/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 18:48:20 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:43:23 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_EVENT_HPP
# define ZOMBIE_EVENT_HPP

# include <string>
# include "Zombie.hpp"

class ZombieEvent
{
public:
	ZombieEvent(std::string type);

	Zombie* newZombie(std::string name) const;
	Zombie* randomChump() const;

	void setZombieType(std::string type);

private:
	std::string type;

	std::string getRandomName() const;
};

#endif
