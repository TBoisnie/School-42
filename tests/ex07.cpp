
#include <iostream>
#include <iomanip>
#include "../srcs/ReadySetBoole.hpp"


// =============================================================================
// Types
// =============================================================================
struct Test
{
	char const * values[1];
	bool expected;
};

// =============================================================================
// Main
// =============================================================================
int main( void )
{
	Test const tests[] = {
		// From subject
		{ .values = { "AB|" },  .expected = true },
		{ .values = { "AB&" },  .expected = true },
		{ .values = { "AA!&" }, .expected = false },
		{ .values = { "AA^" },  .expected = false },
		// Custom
		{ .values = { "AA>" },  .expected = true },
		{ .values = { "AB>" },  .expected = true },
		{ .values = { "AB=" },  .expected = true },
		{ .values = { "AA!=" }, .expected = false },
	};

	for (Test const & test : tests)
	{
		std::cout << std::setw(12) << std::left << "Formula:";
		std::cout << std::left << test.values[0] << "\n";

		std::cout << std::setw(12) << std::left << "Expected:";
		std::cout << test.expected <<  "\n";

		std::cout << std::setw(12) << std::left << "Actual:";
		try
		{
			auto actual = ReadySetBoole::sat(test.values[0]);
			std::cout << actual << "\n";
		}
		catch (std::exception const & e)
		{
			std::cerr << e.what() << '\n';
		}

		std::cout << std::endl;
	}

	return 0;
}
