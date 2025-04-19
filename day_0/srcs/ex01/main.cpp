/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:48:57 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/07 22:25:39 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ConsoleInterface.hpp"
#include "PhoneBook.hpp"

int
main()
{
	PhoneBook	phone_book;
	std::string	cmd;

	while (std::cin.good())
	{
		ConsoleInterface::showMessage("\e[93mWhat do you want to do (ADD, SEARCH, EXIT) ?\e[0m");

		if (!ConsoleInterface::getInputString(cmd))
		{
			ConsoleInterface::showMessage("\e[91mInvalid input.\e[0m");
			break;
		}

		if (cmd.compare("EXIT") == 0)
		{
			break;
		}
		else if (cmd.compare("ADD") == 0)
		{
			if (phone_book.isFull())
				ConsoleInterface::showMessage("Your phone book is full. You can not add any more contact. :(");
			else
			{
				Contact contact;

				if (!ConsoleInterface::fillContact(contact))
					ConsoleInterface::showMessage("\e[91mInvalid input.\e[0m");
				else
					phone_book.addContact(contact);
			}
		}
		else if (cmd.compare("SEARCH") == 0)
		{
			int	wanted_index;

			ConsoleInterface::showPhoneBookTable(phone_book);
			ConsoleInterface::showMessage("\e[93mWhich contact do you want to see ?\e[0m");

			if (!ConsoleInterface::getInputInt(wanted_index))
				ConsoleInterface::showMessage("\e[91mContact index must be an integer.\e[0m");
			else if (wanted_index < 0 || wanted_index >= phone_book.getSize())
				ConsoleInterface::showMessage("\e[91mInvalid contact index.\e[0m");
			else
				ConsoleInterface::showContact(phone_book.getContact(wanted_index));
		}
	}

	if (std::cin.eof())
		ConsoleInterface::showMessage("\e[91mStandard input has been closed.\e[0m");

	return (0);
}
