/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:48:10 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/09 01:50:50 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

int main (int ac, char *av[])
{
	if (ac != 4)
	{
		std::cout << "Error: 'replace' require 3 arguments : \"filename\" \"string from\" \"string to\"" << std::endl;
		return 1;
	}

	std::string filename = av[1];
	std::string from = av[2];
	std::string to = av[3];

	std::ifstream file_in(filename.c_str(), std::ios::in);
	if (!file_in.is_open())
	{
		std::cout << "Error: Could not open input file." << std::endl;
		return 1;
	}

	std::ofstream file_out((filename + ".replace").c_str(), std::ios::out | std::ios::trunc);
	if (!file_out.is_open())
	{
		std::cout << "Error: Could not open ouput file." << std::endl;
		file_in.close();
		return 1;
	}

	file_in.seekg(0, std::ios::end);

	const std::streampos size = file_in.tellg();

	file_in.seekg(0);

	std::string str = std::string(size, ' ');

	file_in.read(&str[0], size);

	std::string::size_type pos = 0;
	while ((pos = str.find(from, pos)) != std::string::npos)
	{
        str.replace(pos, from.length(), to);
        pos += to.length();
    }

	file_out << str;

	file_in.close();
	file_out.close();

	return 0;
}