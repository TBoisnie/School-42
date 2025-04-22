#include <algorithm>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "../srcs/Types.hpp"
#include "../srcs/ReadySetBoole.hpp"


// =============================================================================
// Types
// =============================================================================
struct Test
{
	char const * formula;
	std::vector<std::set<i32>> values;
	std::set<i32> expected;
};

// =============================================================================
// Main
// =============================================================================
int main( void )
{
	Test const tests[] = {
		// Subject
		{
			.formula = "AB&",
			.values = {
				{ 0, 1, 2 },
				{ 0, 3, 4 },
			},
			.expected = { 0 },
		},
		{
			.formula = "AB|",
			.values = {
				{ 0, 1, 2 },
				{ 3, 4, 5 },
			},
			.expected = { 0, 1, 2, 3, 4, 5 }
		},
		{
			.formula = "A!",
			.values = {
				{ 0, 1, 2 },
			},
			.expected = {  },
		},
		// Custom
		{
			.formula = "AB^",
			.values = {
				{ 0, 1, 2 },
				{ 0, 4, 5 },
			},
			.expected = { 1, 2, 4, 5 },
		},
		{
			.formula = "AB=",
			.values = {
				{ 0, 1, 2 },
				{ 0, 4, 5 },
			},
			.expected = { 0 },
		},
		{
			.formula = "AB=",
			.values = {
				{ 0, 1, 2 },
				{ 0, 1, 2 },
			},
			.expected = { 0, 1, 2 },
		},
		{
			.formula = "AB>",
			.values = {
				{ 0, 1, 2 },
				{ 0, 1, 3 },
			},
			.expected = { 0, 1, 3 },
		},
		{
			.formula = "AB>",
			.values = {
				{ 0, 1, 2 },
				{ 0, 1, 2 },
			},
			.expected = { 0, 1, 2 },
		},
	};

	auto printSet = [](auto const & set) {
		std::cout << "{ ";
		std::for_each(set.begin(), set.end(), [](auto const & element) {
			std::cout << element << " ";
		});
		std::cout << "}\n";
	};

	auto printSetVector = [&printSet](auto const & vector) {
		std::for_each(vector.begin(), vector.end(), [&printSet](auto const & set) {
			printSet(set);
		});
	};

	for (Test const & test : tests)
	{
		std::cout << std::setw(12) << std::left << "Formula:";
		std::cout << std::left << test.formula << "\n";

		std::cout << std::setw(12) << std::left << "Values:" << "\n";
		printSetVector(test.values);

		std::cout << std::setw(12) << std::left << "Expected:" << "\n";
		printSet(test.expected);

		std::cout << std::setw(12) << std::left << "Actual:" << "\n";
		try
		{
			auto result = ReadySetBoole::eval_set(test.formula, test.values);
			printSet(result);
		}
		catch (std::exception const & e)
		{
			std::cerr << e.what() << '\n';
		}


		std::cout << std::endl;
	}

	return 0;
}
