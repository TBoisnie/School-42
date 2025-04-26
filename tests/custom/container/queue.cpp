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

#define CTN  NS::queue< std::string >

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
	CTN::size_type       size;       UNUSED( size );
	CTN::value_type      value;      UNUSED( value );

	LOG( "Constructor ------------------------------------------------------" );
	LOG( "- Default ----------------------" );
	{
		CTN ctn;
	}

	LOG( "Operator ---------------------------------------------------------" );

	LOG( "- Relational -------------------" );
	{
		CTN x( NS::deque< std::string >( v.begin(), v.end() ) );
		CTN y( x );

		LOG( "-- Same " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );
		LOG( "x <  y : " << ( x <  y ) );
		LOG( "x <= y : " << ( x <= y ) );
		LOG( "x >  y : " << ( x >  y ) );
		LOG( "x >= y : " << ( x >= y ) );

		y.pop();

		LOG( "-- Different " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );
		LOG( "x <  y : " << ( x <  y ) );
		LOG( "x <= y : " << ( x <= y ) );
		LOG( "x >  y : " << ( x >  y ) );
		LOG( "x >= y : " << ( x >= y ) );
	}

	LOG( "Method -----------------------------------------------------------" );
	LOG( "- Access -----------------------" );
	{
		LOG( "-- Non Const" );
		CTN ctn( NS::deque< std::string >( v.begin(), v.end() ) );

		LOG( "ctn.front() = " << ctn.front() );
		ctn.front() = Random::GetString();
		LOG( "ctn.front() = " << ctn.front() );


		LOG( "ctn.back() = " << ctn.back() );
		ctn.back() = Random::GetString();
		LOG( "ctn.back() = " << ctn.back() );
	}
	{
		LOG( "-- Const" );
		CTN const ctn( NS::deque< std::string >( v.begin(), v.end() ) );

		LOG( "ctn.front() = " << ctn.front() );
		ILLEGAL( ctn.front() = Random::GetString(); )
		LOG( "ctn.front() = " << ctn.front() );

		LOG( "ctn.back() = " << ctn.back() );
		ILLEGAL( ctn.back() = Random::GetString(); )
		LOG( "ctn.back() = " << ctn.back() );
	}
	LOG( "- Capacity ---------------------" );
	{
		CTN const ctn( NS::deque< std::string >( v.begin(), v.end() ) );

		LOG( "ctn.size() = " << ctn.size() );
		LOG( "ctn.empty() = " << ctn.empty() );
	}
	LOG( "- Modifier ---------------------" );
	{
		CTN ctn( NS::deque< std::string >( v.begin(), v.end() ) );

		LOG( "-- Push" );
		ctn.push( Random::GetString() );
		LOG( ctn.front() << " / " << ctn.back() );
		ctn.push( Random::GetString() );
		LOG( ctn.front() << " / " << ctn.back() );
		ctn.push( Random::GetString() );
		LOG( ctn.front() << " / " << ctn.back() );

		LOG( "-- Pop" );
		while ( ! ctn.empty() )
		{
			LOG( ctn.front() << " / " << ctn.back() );
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
