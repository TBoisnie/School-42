/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 21:33:06 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/07 22:24:40 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHONE_BOOK_HPP_
# define _PHONE_BOOK_HPP_

# include "Contact.hpp"

# define PHONE_BOOK_SIZE 8

class PhoneBook
{
public:
	PhoneBook();
	void	addContact(Contact &contact);
	const Contact&	getContact(int index) const;
	bool	isFull() const;
	int		getSize() const;

private:
	int		next_index;
	Contact contacts[PHONE_BOOK_SIZE];
};

#endif