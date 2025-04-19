/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterface.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:11:37 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/01 22:16:58 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <limits>
#include "ConsoleInterface.hpp"

bool
ConsoleInterface::getInputString(std::string &input)
{
	getline(std::cin, input, '\n');

	if (std::cin.fail() || std::cin.eof())
	{
		if (!std::cin.eof())
			std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return false;
	}

	return true;
}

bool
ConsoleInterface::getInputInt(int &input)
{
	std::cin >> input;

	if (std::cin.fail() || std::cin.eof())
	{
		if (!std::cin.eof())
			std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return false;
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return true;
}

void
ConsoleInterface::showMessage(const std::string message)
{
	std::cout << message << std::endl;
}

bool
ConsoleInterface::fillContact(Contact &contact)
{
	std::string input;

	showMessage("\e[93mThanks to fill contact informations :\e[0m");

	showMessage("First name :");
	if (!getInputString(input))
		return false;
	contact.setFirstName(input);

	showMessage("Last name :");
	if (!getInputString(input))
		return false;
	contact.setLastName(input);

	showMessage("Nickname :");
	if (!getInputString(input))
		return false;
	contact.setNickname(input);

	showMessage("Login :");
	if (!getInputString(input))
		return false;
	contact.setLogin(input);

	showMessage("Postal Address :");
	if (!getInputString(input))
		return false;
	contact.setPostalAddress(input);

	showMessage("Email Address :");
	if (!getInputString(input))
		return false;
	contact.setEmailAddress(input);

	showMessage("Phone Number :");
	if (!getInputString(input))
		return false;
	contact.setPhoneNumber(input);

	showMessage("Birthday Date :");
	if (!getInputString(input))
		return false;
	contact.setBirthdayDate(input);

	showMessage("Favorite Meal :");
	if (!getInputString(input))
		return false;
	contact.setFavoriteMeal(input);

	showMessage("Darkest Secret :");
	if (!getInputString(input))
		return false;
	contact.setDarkestSecret(input);

	return true;
}

void
ConsoleInterface::showContact(const Contact &contact)
{
	std::cout << contact.getFirstName() << std::endl;
	std::cout << contact.getLastName() << std::endl;
	std::cout << contact.getNickname() << std::endl;
	std::cout << contact.getLogin() << std::endl;
	std::cout << contact.getPostalAddress() << std::endl;
	std::cout << contact.getEmailAddress() << std::endl;
	std::cout << contact.getPhoneNumber() << std::endl;
	std::cout << contact.getBirthdayDate() << std::endl;
	std::cout << contact.getFavoriteMeal() << std::endl;
	std::cout << contact.getDarkestSecret() << std::endl;
}

void
ConsoleInterface::showPhoneBookTable(const PhoneBook &phone_book)
{
	const size_t width = 10;

	for (int i = 0; i < phone_book.getSize(); i++)
	{
		const Contact &contact = phone_book.getContact(i);

		std::cout << std::setw(width) << i;

		std::cout << std::setw(0) << "|";

		if (contact.getFirstName().length() > width)
			std::cout << std::setw(width - 1) << contact.getFirstName().substr(0, width - 1) << ".";
		else
			std::cout << std::setw(width) << contact.getFirstName();

		std::cout << std::setw(0) << "|";

		if (contact.getLastName().length() > width)
			std::cout << std::setw(width - 1) << contact.getLastName().substr(0, width - 1) << ".";
		else
			std::cout << std::setw(width) << contact.getLastName();

		std::cout << std::setw(0) << "|";

		if (contact.getNickname().length() > width)
			std::cout << std::setw(width - 1) << contact.getNickname().substr(0, width - 1) << ".";
		else
			std::cout << std::setw(width) << contact.getNickname();

		std::cout << std::setw(0) << std::endl;
	}
}

