/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:49:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/14 16:00:04 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_HPP
# define A_HPP

# include "Base.hpp"

class A
	: public Base
{
public:
	// Constructors & Destructors
	A();
	A(const A & other);
	~A();

	// Operators
	A& operator=(const A &other);
};

#endif