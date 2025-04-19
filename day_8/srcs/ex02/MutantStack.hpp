/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:29:41 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/30 18:22:30 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

# include <stack>

template <typename T, typename C = std::deque<T> >
class MutantStack
	: public std::stack<T, C>
{
public:
	typedef typename C::iterator			iterator;
	typedef typename C::reverse_iterator	reverse_iterator;

	iterator begin()			{ return this->c.begin();  }
	iterator end()				{ return this->c.end();    }
	reverse_iterator rbegin()	{ return this->c.rbegin(); }
	reverse_iterator rend()		{ return this->c.rend();   }
};

#endif
