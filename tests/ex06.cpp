
#include <iostream>
#include <iomanip>
#include "../srcs/ReadySetBoole.hpp"


// =============================================================================
// Types
// =============================================================================
struct Test
{
	char const * values[1];
	char const * expected;
};

// =============================================================================
// Main
// =============================================================================
int main( void )
{
	Test const tests[] = {
		// From subject
		{ .values = { "AB&!" },    .expected = "A!B!|" },
		{ .values = { "AB|!" },    .expected = "A!B!&" },
		{ .values = { "AB|C&" },   .expected = "AB|C&" },
		{ .values = { "AB|C|D|" }, .expected = "ABCD|||" },
		{ .values = { "AB&C&D&" }, .expected = "ABCD&&&" },
		{ .values = { "AB&!C!|" }, .expected = "A!B!C!||" },
		{ .values = { "AB|!C!&" }, .expected = "A!B!C!&&" },
		// Custom
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
			auto actual = ReadySetBoole::conjunctive_normal_form(test.values[0]);
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
