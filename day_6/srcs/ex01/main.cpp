/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:43:37 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/14 15:32:30 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <new>
#include <cstdlib>
#include <ctime>

#define STRING_SIZE 8

struct Data
{
	std::string s1;
	int n;
	std::string s2;
};

void*
serialize(void)
{
	std::srand(std::time(NULL));
	static const std::string alnum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	void *mem = NULL;
	try
	{
		mem = operator new(2 * STRING_SIZE * sizeof(char) + sizeof(int));
	}
	catch (std::bad_alloc &e)
	{
		std::cout << "Bad Allocation : Raw memory serialize." << std::endl;
		return NULL;
	}

	char *mem_s1 = static_cast<char*>(mem);
	for (size_t i = 0; i < STRING_SIZE; i++)
		mem_s1[i] = alnum[std::rand() % alnum.length()];

	int *mem_n = reinterpret_cast<int*>(&mem_s1[STRING_SIZE]);
	mem_n[0] = std::rand();

	char *mem_s2 = reinterpret_cast<char*>(&mem_n[1]);
	for (size_t i = 0; i < STRING_SIZE; i++)
		mem_s2[i] = alnum[std::rand() % alnum.length()];

	return mem;
}

Data*
deserialize(void* raw)
{
	Data *data = NULL;

	if (raw == NULL)
		return NULL;

	try
	{
		data = new Data();

		char *mem_s1 = static_cast<char*>(raw);
		data->s1 = std::string(mem_s1, STRING_SIZE);

		int *mem_n = reinterpret_cast<int*>(&mem_s1[STRING_SIZE]);
		data->n = mem_n[0];

		char *mem_s2 = reinterpret_cast<char*>(&mem_n[1]);
		data->s2 = std::string(mem_s2, STRING_SIZE);

	}
	catch (std::exception &e)
	{
		std::cout << "Bad Allocation : Data deserialize." << std::endl;
	}

	return data;
}

int main( void )
{
	std::srand(std::time(NULL));

	void *raw = serialize();
	Data *data = deserialize(raw);

	if (data)
	{
		std::cout << data->s1 << std::endl;
		std::cout << data->n << std::endl;
		std::cout << data->s2 << std::endl;
	}

	delete data;
	operator delete(raw);

	return 0;
}