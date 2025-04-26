#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <string>
#include <cstdlib>

#ifndef SEED
# define SEED  0
#endif

namespace tester
{

class Random
{
	// Method ------------------------------------------------------------------
public:
	static void
	init(
		unsigned int seed = SEED
	)
	{
		srand( seed );
	}

	static int
	GetInt(
		int min = 0,
		int max = 100
	)
	{
		return ( min + rand() % ( max - min + 1 ) );
	}

	static float
	GetFloat(
		float min = 0.0,
		float max = 100.0
	)
	{
		return ( min + ( (float) rand() / (float) RAND_MAX ) * ( max - min ) );
	}

	static std::string
	GetString(
		unsigned int min = 3,
		unsigned int max = 10,
		std::string const & characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_"
	)
	{
		if ( characters.empty() )
		{
			return "";
		}

		std::string::size_type const length = Random::GetInt( min, max );
		std::string str;

		for ( std::string::size_type i = 0 ; i < length; ++i )
		{
			str.push_back(characters[ Random::GetInt( 0, characters.size() - 1 ) ] );
		}

		return str;
	}
};

}

#endif
