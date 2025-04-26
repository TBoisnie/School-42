#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <list>

#define LOG( STR ) \
	std::cout << STR << '\n'
#define LOG_RANGE( BEGIN, END ) \
	print( BEGIN, END )
#define LOG_URANGE( CTN, BEGIN, END ) \
	do { \
		std::list< CTN::value_type > l( BEGIN, END ); \
		l.sort(); \
		print( l.begin(), l.end() ); \
	} while (0)

namespace tester
{

/**
 * Print
 */
template <
	typename T
>
void
print(
	T const begin,
	T const end
)
{
	for ( T it = begin ; it != end ; ++it )
	{
		std::cout << '`' << *it << '`' << " ";
	}

	std::cout << '\n';
}

}

#endif
