/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:55:42 by tboisnie          #+#    #+#             */
/*   Updated: 2020/07/27 00:27:37 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

void
identify_from_pointer(Base *p)
{
	if (A *a = dynamic_cast<A*>(p))
	{
		std::cout << "A" << std::endl;
		return ;
	}

	if (B *b = dynamic_cast<B*>(p))
	{
		std::cout << "B" << std::endl;
		return ;
	}

	if (C *c = dynamic_cast<C*>(p))
	{
		std::cout << "C" << std::endl;
		return ;
	}
}

void
identify_from_reference(Base &p)
{
	if (A *a = dynamic_cast<A*>(&p))
	{
		std::cout << "A" << std::endl;
		return ;
	}

	if (B *b = dynamic_cast<B*>(&p))
	{
		std::cout << "B" << std::endl;
		return ;
	}

	if (C *c = dynamic_cast<C*>(&p))
	{
		std::cout << "C" << std::endl;
		return ;
	}
}

int main( void )
{
	A a;
	B b;
	C c;

	identify_from_pointer(&c);
	identify_from_pointer(&a);
	identify_from_pointer(&b);

	identify_from_reference(c);
	identify_from_reference(a);
	identify_from_reference(b);

	return 0;
}