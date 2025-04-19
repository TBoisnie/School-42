/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 22:53:46 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 23:40:47 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cerrno>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <limits>

int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cout << "Invalid number of arguments. (./convert \"value\")" << std::endl;
		return 1;
	}

	std::string str(av[1]);

	// Check special values
	bool isInf = (
		str == "-inf" || str == "- inf" || str == "+inf" || str == "+ inf" ||
		str == "-inff" || str == "- inff" || str == "+inff" || str == "+ inff"
	);
	bool isNan = (
		str == "nan" || str == "nanf"
	);

	// Store into largest 'container'
	double value = 0.0;
	if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
		value = static_cast<double>(str[1]);
	else
		value = static_cast<double>(std::strtod(str.c_str(), NULL));

	// Char
	char c = static_cast<char>(value);
	std::cout << "char: ";
	if (isInf || isNan || (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max()))
		std::cout << "impossible";
	else if (!std::isprint(c))
		std::cout << "Non displayable";
	else
		std::cout << "'" << c << "'";
	std::cout << std::endl;

	// Int
	int i = static_cast<int>(value);
	std::cout << "int: ";
	if (isInf || isNan || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
		std::cout << "impossible";
	else
		std::cout << i;
	std::cout << std::endl;

	// Float
	float f = static_cast<float>(value);
	std::cout << "float: ";
	if (isInf || isNan)
		std::cout << value << "f";
	else if (value < -std::numeric_limits<float>::max() || value > std::numeric_limits<float>::max())
		std::cout << "impossible";
	else
		std::cout << std::fixed << std::setprecision(1) << f << "f";
	std::cout << std::endl;

	// Double
	double d = static_cast<double>(value);
	std::cout << "double: ";
	if (isInf || isNan)
		std::cout << value;
	else if (value < -std::numeric_limits<double>::max() || value > std::numeric_limits<double>::max() || errno == ERANGE)
		std::cout << "impossible";
	else
		std::cout << std::fixed << std::setprecision(1) << d;
	std::cout << std::endl;

	return 0;
}