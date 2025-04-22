
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
		{
			.values = { "AB&C|" },
			.expected =
				"| A | B | C | = |\n"
				"|---|---|---|---|\n"
				"| 0 | 0 | 0 | 0 |\n"
				"| 0 | 0 | 1 | 1 |\n"
				"| 0 | 1 | 0 | 0 |\n"
				"| 0 | 1 | 1 | 1 |\n"
				"| 1 | 0 | 0 | 0 |\n"
				"| 1 | 0 | 1 | 1 |\n"
				"| 1 | 1 | 0 | 1 |\n"
				"| 1 | 1 | 1 | 1 |\n"
		},
		// Custom
		{
			.values = { "AB&C!D|^" },
			.expected =
				"| A | B | C | D | = |\n"
				"|---|---|---|---|---|\n"
				"| 0 | 0 | 0 | 0 | 1 |\n"
				"| 0 | 0 | 0 | 1 | 1 |\n"
				"| 0 | 0 | 1 | 0 | 0 |\n"
				"| 0 | 0 | 1 | 1 | 1 |\n"
				"| 0 | 1 | 0 | 0 | 1 |\n"
				"| 0 | 1 | 0 | 1 | 1 |\n"
				"| 0 | 1 | 1 | 0 | 0 |\n"
				"| 0 | 1 | 1 | 1 | 1 |\n"
				"| 1 | 0 | 0 | 0 | 1 |\n"
				"| 1 | 0 | 0 | 1 | 1 |\n"
				"| 1 | 0 | 1 | 0 | 0 |\n"
				"| 1 | 0 | 1 | 1 | 1 |\n"
				"| 1 | 1 | 0 | 0 | 0 |\n"
				"| 1 | 1 | 0 | 1 | 0 |\n"
				"| 1 | 1 | 1 | 0 | 1 |\n"
				"| 1 | 1 | 1 | 1 | 0 |\n"
		},
	};

	for (Test const & test : tests)
	{
		std::cout << std::setw(12) << std::left << "Formula:";
		std::cout << std::left << test.values[0] << "\n";

		std::cout << std::setw(12) << std::left << "Expected:" << "\n";
		std::cout << test.expected;

		std::cout << std::setw(12) << std::left << "Actual:" << "\n";
		try
		{
			ReadySetBoole::print_truth_table(test.values[0]);
		}
		catch (std::exception const & e)
		{
			std::cerr << e.what() << '\n';
		}

		std::cout << std::endl;
	}

	return 0;
}
