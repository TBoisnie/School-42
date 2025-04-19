/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:49:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/14 16:04:17 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_HPP
# define C_HPP

# include "Base.hpp"

class C
	: public Base
{
public:
	// Constructors & Destructors
	C();
	C(const C & other);
	~C();

	// Operators
	C& operator=(const C &other);
};

#endif