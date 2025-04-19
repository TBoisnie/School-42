/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:47:29 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/29 17:47:24 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Array.hpp"

int main( void )
{
	Array<std::string> str_arr(15);
	str_arr[0] = "Hello";
	str_arr[1] = "World";
	str_arr[2] = "!";
	str_arr[7] = "Middle";
	str_arr[13] = "Almost";
	str_arr[14] = "END";

	std::cout << "str_arr ("<< str_arr.size() << "): ";
	for (unsigned int i = 0; i < str_arr.size(); ++i)
		std::cout << "`" << str_arr[i] << "` ";
	std::cout << std::endl;

	try
	{
		str_arr[9999] = "Fail";
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	const Array<std::string> str_cpy(str_arr);

	str_arr[14] = "Never ending!";
	// str_cpy[2] = "FAIL";	// Can not modify on const object

	std::cout << "str_arr ("<< str_arr.size() << "): ";
	for (unsigned int i = 0; i < str_arr.size(); ++i)
		std::cout << "`" << str_arr[i] << "` ";
	std::cout << std::endl;

	std::cout << "str_cpy ("<< str_cpy.size() << "): ";
	for (unsigned int i = 0; i < str_cpy.size(); ++i)
		std::cout << "`" << str_cpy[i] << "` ";
	std::cout << std::endl;

	return 0;
}