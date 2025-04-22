
#include <iostream>
#include <iomanip>
#include "../srcs/Types.hpp"
#include "../srcs/ReadySetBoole.hpp"


// =============================================================================
// Types
// =============================================================================
struct Test
{
	u16 values[2];
};

// =============================================================================
// Main
// =============================================================================
int main( void )
{
	Test const tests[] = {
		// Custom
		{
			.values = { 0, 0 },
		},
		{
			.values = { 0, 65'535 },
		},
		{
			.values = { 65'535, 0 },
		},
		{
			.values = { 1, 1 },
		},
		{
			.values = { 1, 65'535 },
		},
		{
			.values = { 65'535, 1 },
		},
		{
			.values = { 65'535, 65'535 },
		},
		{
			.values = { 65'535, 65'534 },
		},
		{
			.values = { 65'534, 65'535 },
		},
		{
			.values = { 23'463, 34'562 },
		},
	};

	for (Test const & test : tests)
	{
		std::cout << std::setw(12) << std::left << "Values: ";
		std::cout << test.values[0] << " " << test.values[1] << "\n";

		std::cout << std::setw(12) << std::left << "Expected: ";
		std::cout << "[[0,1]]" << "\n";

		std::cout << std::setw(12) << std::left << "Map: " ;
		auto result = ReadySetBoole::map(test.values[0], test.values[1]);
		std::cout << std::fixed << std::setprecision(12) << result << "\n";

		std::cout << std::setw(12) << std::left << "Reverse: " ;
		auto reverse = ReadySetBoole::reverse_map(result);
		std::cout << reverse.first << " " << reverse.second << "\n";

		std::cout << std::endl;
	}

	return 0;
}
