/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:48:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/14 16:02:07 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "B.hpp"

/**
 * Constructors & Destructors
 */
B::B()
{

}

B::B(const B &other)
{
	(void)other;
}

B::~B()
{

}

/**
 * Operators
 */
B&
B::operator=(const B &other)
{
	(void)other;

	return *this;
}