/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:24:51 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/27 18:03:29 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONTACT_HPP_
# define _CONTACT_HPP_

# include <string>

class Contact
{
	public:
	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getNickname() const;
	std::string getLogin() const;
	std::string getPostalAddress() const;
	std::string getEmailAddress() const;
	std::string getPhoneNumber() const;
	std::string getBirthdayDate() const;
	std::string getFavoriteMeal() const;
	std::string getDarkestSecret() const;

	void setFirstName(std::string first_name);
	void setLastName(std::string last_name);
	void setNickname(std::string nickname);
	void setLogin(std::string login);
	void setPostalAddress(std::string postal_address);
	void setEmailAddress(std::string email_address);
	void setPhoneNumber(std::string phone_number);
	void setBirthdayDate(std::string birthday_date);
	void setFavoriteMeal(std::string favorite_meal);
	void setDarkestSecret(std::string darkest_secret);

	private:
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string login;
	std::string postal_address;
	std::string email_address;
	std::string phone_number;
	std::string birthday_date;
	std::string favorite_meal;
	std::string darkest_secret;
};

#endif