#include <string>
#include <vector>

#include "../utils/Preprocessor.hpp"
#include "../utils/Logger.hpp"
#include "../utils/Time.hpp"
#include "../utils/Random.hpp"

/**
 * Define
 */
#ifndef NS
# define NS  std
# include <queue>
#else
// # define NS  ft
# include "queue.hpp"
#endif

#define CTN  NS::priority_queue< std::string >

/**
 * Main
 */
int
main()
{
	// Initialization ----------------------------------------------------------
	using tester::Random;
	using tester::Time;
	using tester::print;

	Random::init();

	// Base --------------------------------------------------------------------
	std::vector< std::string > v;

	for ( int i = 0 ; i < 16 ; ++i )
	{
		std::string str = Random::GetString();

		 // Add some duplicates
		if ( i % 4 == 0 )
		{
			v.push_back( str );
		}

		v.push_back( str );
	}

#ifndef PERFORMANCE_MODE
{
	LOG( "Type -------------------------------------------------------------" );
	CTN::container_type  container;  UNUSED( container );
	CTN::value_compare   compare;    UNUSED( compare );
	CTN::size_type       size;       UNUSED( size );
	CTN::value_type      value;      UNUSED( value );

	LOG( "Constructor ------------------------------------------------------" );
	LOG( "- Default ----------------------" );
	{
		CTN ctn;
	}
	{
		CTN ctn( NS::greater< std::string > );
	}
	{
		CTN ctn( NS::less< std::string >, CTN::container_type );
	}
	LOG( "- Range ------------------------" );
	{
		CTN ctn( v.begin(), v.end() );
	}
	{
		CTN ctn( v.begin(), v.end(), NS::less< std::string >() );
	}
	{
		CTN ctn( v.begin(), v.end(), NS::less< std::string >(), CTN::container_type() );
	}

	LOG( "Method -----------------------------------------------------------" );
	LOG( "- Access -----------------------" );
	{
		CTN ctn( v.begin(), v.end() );

		LOG( "ctn.top() = " << ctn.top() );
		ILLEGAL( ctn.top() = Random::GetString(); )
		LOG( "ctn.top() = " << ctn.top() );
	}
	LOG( "- Capacity ---------------------" );
	{
		CTN const ctn( v.begin(), v.end() );

		LOG( "ctn.size() = " << ctn.size() );
		LOG( "ctn.empty() = " << ctn.empty() );
	}
	LOG( "- Modifier ---------------------" );
	{
		CTN ctn( v.begin(), v.end() );

		LOG( "-- Push" );
		ctn.push( Random::GetString() );
		LOG( ctn.top() );
		ctn.push( Random::GetString() );
		LOG( ctn.top() );
		ctn.push( Random::GetString() );
		LOG( ctn.top() );

		LOG( "-- Pop" );
		while ( ! ctn.empty() )
		{
			LOG( ctn.top() );
			ctn.pop();
		}
	}
}
#else // PERFORMANCE_MDOE
{
	Time start = Time::Now();

	CTN ctn;

	Time push = Time::Now();
	while( ctn.size() < 1000000 )
	{
		ctn.push( Random::GetString() );
	}
	LOG( "Time Push (us): " << Time::Now().Sub( push ).ToMicroSecond() );

	Time pop = Time::Now();
	while ( ctn.size() > 250000 )
	{
		ctn.pop();
	}
	LOG( "Time Pop (us): " << Time::Now().Sub( pop ).ToMicroSecond() );

	LOG( "Time Total (us): " << Time::Now().Sub( start ).ToMicroSecond() );
}
#endif // PERFORMANCE_MDOE

}
