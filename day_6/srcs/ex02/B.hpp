/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:49:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/14 16:01:18 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_HPP
# define B_HPP

# include "Base.hpp"

class B
	: public Base
{
public:
	// Constructors & Destructors
	B();
	B(const B & other);
	~B();

	// Operators
	B& operator=(const B &other);
};

#endif