/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:32:57 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 02:13:17 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
public:
	Fixed();
	Fixed(const Fixed &other);
	Fixed(const int n);
	Fixed(const float f);
	~Fixed();

	Fixed& operator=(const Fixed &other);

	float toFloat(void) const;
	int toInt(void) const;

	int getRawBits() const;
	void setRawBits(const int raw);

private:
	static const int bits;

	int value;
};

std::ostream& operator<<(std::ostream& out, const Fixed &obj);

#endif