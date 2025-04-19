/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:12:11 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:22:09 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

# include <string>
# include "ClapTrap.hpp"

class FragTrap
	: virtual public ClapTrap
{
private:
	FragTrap();

public:
	// Constructors & Destructors
	FragTrap(const std::string & name);
	FragTrap(const FragTrap & other);
	virtual ~FragTrap();

	// Operators
	FragTrap & operator=(const FragTrap & other);

	// Methods
	void vaulthunter_dot_exe(const std::string & target);

private:
	// Private Methods
	void pauseAttack(const std::string & target);
	void charmAttack(const std::string & target);
	void magicAttack(const std::string & target);
	void fakeAttack(const std::string & target);
	void ccAttack(const std::string & target);
};

#endif