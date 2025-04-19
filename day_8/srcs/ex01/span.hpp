/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 20:07:14 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 01:02:43 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>

class Span
{
private:
	unsigned int max_size;
	std::vector<int> values;

private:
	Span();

public:
	Span(unsigned int max_size);
	Span(const Span & other);
	~Span();

	Span& operator=(const Span & other);

	void addNumber(int n);
	long shortestSpan();
	long longestSpan();

	// Function to insert multiple values from another container
	template<typename It>
	void
	addRange(const It beg, const It end)
	{
		unsigned int dist = std::distance(beg, end);

		if (this->max_size - this->values.size() < dist)
			throw std::runtime_error("AddNumbers() : Trying to insert too much values.");

		this->values.insert(this->values.end(), beg, end);
	}
};

#endif