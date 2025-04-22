
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <algorithm> // Sort
#include "../srcs/Types.hpp"
#include "../srcs/ReadySetBoole.hpp"


// =============================================================================
// Types
// =============================================================================
struct Test
{
	std::set<i32> values[1];
	std::vector<std::set<i32>> expected;
};

// =============================================================================
// Main
// =============================================================================
int main( void )
{
	Test const tests[] = {
		// Custom
		{
			.values = { {  } },
			.expected = {
				{  },
			}
		},
		{
			.values = { { 0 } },
			.expected = {
				{  },
				{ 0 },
			}
		},
		{
			.values = { { 0, 1 } },
			.expected = {
				{  },
				{ 0 },
				{ 1 },
				{ 0, 1 },
			}
		},
		{
			.values = { { -1, 0, 1 } },
			.expected = {
				{  },
				{ -1 },
				{  0 },
				{  1 },
				{ -1, 0 },
				{ -1, 1 },
				{  0, 1 },
				{ -1, 0, 1 }
			}
		},
		{
			.values = { { 1, 2, 3, 4, 5 } },
			.expected = {
				{ },
				{ 1 },
				{ 2 },
				{ 3 },
				{ 4 },
				{ 5 },
				{ 1, 2 },
				{ 1, 3 },
				{ 1, 4 },
				{ 1, 5 },
				{ 2, 3 },
				{ 2, 4 },
				{ 2, 5 },
				{ 3, 4 },
				{ 3, 5 },
				{ 4, 5 },
				{ 1, 2, 3 },
				{ 1, 2, 4 },
				{ 1, 2, 5 },
				{ 1, 3, 4 },
				{ 1, 3, 5 },
				{ 1, 4, 5 },
				{ 2, 3, 4 },
				{ 2, 3, 5 },
				{ 2, 4, 5 },
				{ 3, 4, 5 },
				{ 1, 2, 3, 4 },
				{ 1, 2, 3, 5 },
				{ 1, 2, 4, 5 },
				{ 1, 3, 4, 5 },
				{ 2, 3, 4, 5 },
				{ 1, 2, 3, 4, 5 },
			}
		},
	};

	auto printSet = [](auto const & set) {
		std::cout << "{ ";
		std::for_each(set.begin(), set.end(), [](auto const & element) {
			std::cout << element << " ";
		});
		std::cout << "}";
	};

	auto printSetVector = [&printSet](auto const & vector) {
		std::for_each(vector.begin(), vector.end(), [&printSet](auto const & set) {
			printSet(set);
			std::cout << "\n";
		});
	};

	for (Test const & test : tests)
	{
		std::cout << std::setw(12) << std::left << "Formula:";
		printSet(test.values[0]);
		std::cout << "\n";

		std::cout << std::setw(12) << std::left << "Expected:" << "\n";
		printSetVector(test.expected);

		std::cout << std::setw(12) << std::left << "Actual:" << "\n";
		auto actual = ReadySetBoole::powerset(test.values[0]);

		// Optionnal: Increasing readability for peer review.
		std::sort(actual.begin(), actual.end(), [](auto const & a, auto const & b) {
			return (
				a.size() == b.size()
					? a < b
					: a.size() < b.size()
			);
		});

		printSetVector(actual);

		std::cout << std::endl;
	}

	return 0;
}
