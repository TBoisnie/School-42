/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:48:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/14 16:02:18 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "C.hpp"

/**
 * Constructors & Destructors
 */
C::C()
{

}

C::C(const C &other)
{
	(void)other;
}

C::~C()
{

}

/**
 * Operators
 */
C&
C::operator=(const C &other)
{
	(void)other;

	return *this;
}