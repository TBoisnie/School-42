/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:58:31 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/03 00:50:34 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

// ------------------------------------
// -- Getters & Setters
// ------------------------------------

std::string
Contact::getFirstName() const
{
	return this->first_name;
}

std::string
Contact::getLastName() const
{
	return this->last_name;
}

std::string
Contact::getNickname() const
{
	return this->nickname;
}

std::string
Contact::getLogin() const
{
	return this->login;
}

std::string
Contact::getPostalAddress() const
{
	return this->postal_address;
}

std::string
Contact::getEmailAddress() const
{
	return this->email_address;
}

std::string
Contact::getPhoneNumber() const
{
	return this->phone_number;
}

std::string
Contact::getBirthdayDate() const
{
	return this->birthday_date;
}

std::string
Contact::getFavoriteMeal() const
{
	return this->favorite_meal;
}

std::string
Contact::getDarkestSecret() const
{
	return this->darkest_secret;
}

void
Contact::setFirstName(std::string first_name)
{
	this->first_name = first_name;
}

void
Contact::setLastName(std::string last_name)
{
	this->last_name = last_name;
}

void
Contact::setNickname(std::string nickname)
{
	this->nickname = nickname;
}

void
Contact::setLogin(std::string login)
{
	this->login = login;
}

void
Contact::setPostalAddress(std::string postal_address)
{
	this->postal_address = postal_address;
}

void
Contact::setEmailAddress(std::string email_address)
{
	this->email_address = email_address;
}

void
Contact::setPhoneNumber(std::string phone_number)
{
	this->phone_number = phone_number;
}

void
Contact::setBirthdayDate(std::string birthday_date)
{
	this->birthday_date = birthday_date;
}

void
Contact::setFavoriteMeal(std::string favorite_meal)
{
	this->favorite_meal = favorite_meal;
}

void
Contact::setDarkestSecret(std::string darkest_secret)
{
	this->darkest_secret = darkest_secret;
}
