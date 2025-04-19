/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 20:32:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:41:05 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONY_H
# define PONY_H

# include <string>

class Pony
{
public:
	static int getCount();

	Pony(std::string name, std::string color);
	~Pony();

	void run();
	void rest();

	const std::string getName() const;
	const std::string getColor() const;
	int getEnergy() const;
	int getRan() const;

private:
	static int count;

	std::string	name;
	std::string	color;
	int	energy;
	int	ran;
};

#endif