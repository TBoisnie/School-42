
#include <iostream>
#include <iomanip>
#include "../srcs/Types.hpp"
#include "../srcs/ReadySetBoole.hpp"


// =============================================================================
// Types
// =============================================================================
struct Test
{
	u32 values[1];
	u32 expected;
};

// =============================================================================
// Main
// =============================================================================
int main( void )
{
	Test const tests[] = {
		// From subject
		{ .values = { 0 },          .expected = 0 },
		{ .values = { 1 },          .expected = 1 },
		{ .values = { 2 },          .expected = 3 },
		{ .values = { 3 },          .expected = 2 },
		{ .values = { 4 },          .expected = 6 },
		{ .values = { 5 },          .expected = 7 },
		{ .values = { 6 },          .expected = 5 },
		{ .values = { 7 },          .expected = 4 },
		{ .values = { 8 },          .expected = 12 },
		// Custom
		{ .values = { 4'294'967'295 }, .expected = 2'147'483'648 },
		{ .values = { 2'863'311'530 }, .expected = 4'294'967'295 },
	};

	for (Test const & test : tests)
	{
		std::cout << std::setw(12) << std::left << "Formula:";
		std::cout << std::left << "gray_code(" << test.values[0] << ")" << "\n";

		std::cout << std::setw(12) << std::left << "Expected:";
		std::cout << std::setw(12) << test.expected <<  "\n";

		std::cout << std::setw(12) << std::left << "Actual:";
		auto actual = ReadySetBoole::gray_code(test.values[0]);
		std::cout << std::setw(12) << actual << "\n";

		std::cout << std::endl;
	}

	return 0;
}
