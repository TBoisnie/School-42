/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:32:57 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 02:10:27 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed
{
public:
	Fixed();
	Fixed(const Fixed &other);
	~Fixed();

	Fixed& operator=(const Fixed &other);

	int getRawBits() const;
	void setRawBits(const int raw);

private:
	static const int bits;

	int value;
};

#endif
