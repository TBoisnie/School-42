/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:48:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/14 16:02:01 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"

/**
 * Constructors & Destructors
 */
A::A()
{

}

A::A(const A &other)
{
	(void)other;
}

A::~A()
{

}

/**
 * Operators
 */
A&
A::operator=(const A &other)
{
	(void)other;

	return *this;
}