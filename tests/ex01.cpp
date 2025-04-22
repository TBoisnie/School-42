
#include <iostream>
#include <iomanip>
#include "../srcs/Types.hpp"
#include "../srcs/ReadySetBoole.hpp"


// =============================================================================
// Types
// =============================================================================
struct Test
{
	u32 values[2];
	u32 expected;
};

// =============================================================================
// Main
// =============================================================================
int main( void )
{
	Test const tests[] = {
		// Custom
		{ .values = { 0, 0 },                   .expected = static_cast<u32>(0) * 0 },
		{ .values = { 0, 1 },                   .expected = static_cast<u32>(0) * 1 },
		{ .values = { 1, 1 },                   .expected = static_cast<u32>(1) * 1 },
		{ .values = { 42, 58 },                 .expected = static_cast<u32>(42) * 58 },
		{ .values = { 15'084, 53'234 },         .expected = static_cast<u32>(15'084) * 53'234 },
		{ .values = { 15'084'345, 53'234'876 }, .expected = static_cast<u32>(15'084'345) * 53'234'876 },
		{ .values = { 4'294'967'295, 0 },       .expected = static_cast<u32>(4'294'967'295) * 0 },
		{ .values = { 4'294'967'295, 1 },       .expected = static_cast<u32>(4'294'967'295) * 1 },
		{ .values = { 4'294'967'295, 2 },       .expected = static_cast<u32>(4'294'967'295) * 2 },
	};

	for (Test const & test : tests)
	{
		std::cout << std::setw(12) << std::left << "Formula:";
		std::cout << std::left << test.values[0] << " * " << test.values[1] << "\n";

		std::cout << std::setw(12) << std::left << "Expected:";
		std::cout << std::setw(12) << test.expected << "\n";

		std::cout << std::setw(12) << std::left << "Actual:";
		auto actual = ReadySetBoole::multiplier(test.values[0], test.values[1]);
		std::cout << std::setw(12) << actual << "\n";

		std::cout << std::endl;
	}

	return 0;
}
