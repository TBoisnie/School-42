/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 18:19:04 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:48:28 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie
{
	public:
		static int alive;

		Zombie();
		Zombie(std::string type, std::string name);
		~Zombie();

		void announce() const;

	private:
		std::string type;
		std::string name;

		static std::string getRandomName();
};

#endif
