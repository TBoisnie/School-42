/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:31:20 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/07 22:25:25 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
	: next_index(0)
{
	// Empty
}

void
PhoneBook::addContact(Contact &contact)
{
	this->contacts[this->next_index] = contact;
	this->next_index++;
}

const Contact&
PhoneBook::getContact(int index) const
{
	return this->contacts[index];
}

bool
PhoneBook::isFull() const
{
	return (this->next_index >= PHONE_BOOK_SIZE);
}

int
PhoneBook::getSize() const
{
	return this->next_index;
}