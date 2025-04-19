/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterface.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 20:48:49 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/27 18:36:31 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONSOLE_INTERFACE_HPP_
# define _CONSOLE_INTERFACE_HPP_

# include "PhoneBook.hpp"
# include "Contact.hpp"

class ConsoleInterface
{
public:
	static bool getInputString(std::string &input);
	static bool getInputInt(int &input);

	static bool fillContact(Contact &contact);

	static void showMessage(const std::string message);
	static void showContact(const Contact &contact);
	static void showPhoneBookTable(const PhoneBook &phone_book);

private:
	ConsoleInterface();
};

#endif