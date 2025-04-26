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
# error "Fibonnaci Heap is not supported by Standard Template Library (STL)"
#else
// # define NS  ft
# include "fibonacci_heap.hpp"
#endif

#define CTN  NS::fibonacci_heap< int >

namespace NS
{
std::ostream &
operator<<(
	std::ostream & out,
	NS::pair< int, std::string > const & p
)
{
	return (out << '[' << p.first << ", " << p.second << ']' );
}
}

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
	std::vector< int > v;
	std::vector< int >::iterator vit_a;
	std::vector< int >::iterator vit_b;

	for ( int i = 0 ; i < 16 ; ++i )
	{
		int str = Random::GetInt();

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
	{
		CTN::allocator_type  allocator;   UNUSED( allocator );
		CTN::size_type       size;        UNUSED( size );
		CTN::difference_type difference;  UNUSED( difference );

		CTN::key_type        key;           UNUSED( key );
		CTN::value_type      value;         UNUSED( value );
		CTN::reference       ref = value;   UNUSED( ref );
		CTN::const_reference cref = value;  UNUSED( cref );
		CTN::pointer         ptr;           UNUSED( ptr );
		CTN::const_pointer   cptr;          UNUSED( cptr );

		CTN::key_compare    cmp;  UNUSED( cmp );

		CTN::iterator               it;    UNUSED( it );
		CTN::const_iterator         cit;   UNUSED( cit );
		CTN::reverse_iterator       rit;   UNUSED( rit );
		CTN::const_reverse_iterator crit;  UNUSED( crit );
	}

	LOG( "Constructor ------------------------------------------------------" );
	LOG( "- Default ----------------------" );
	{
		CTN ctn;

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );
	}
	LOG( "- Range ------------------------" );
	LOG( "- Size 1 -----------------------" );
	{
		CTN ctn;
		ctn.push( 10 );

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );
	}
	LOG( "- Size 9 -----------------------" );
	{
		CTN ctn;
		ctn.push( 40 );
		ctn.push( 50 );
		ctn.push( 80 );
		ctn.push( 90 );
		ctn.push( 70 );
		ctn.push( 60 );
		ctn.push( 30 );
		ctn.push( 20 );
		ctn.push( 10 );

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );
	}
	LOG( "- Range ------------------------" );
	{
		CTN const ctn( v.begin(), v.end() );
		CTN copy( ctn );

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );
	}

	LOG( "Operator ---------------------------------------------------------" );
	LOG( "- Assignment -------------------" );
	{
		CTN const ctn( v.begin(), v.end() );
		CTN other;

		other = ctn;

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );
		LOG_RANGE( other.begin(), other.end() );
		LOG_RANGE( other.rbegin(), other.rend() );
	}

	LOG( "Method -----------------------------------------------------------" );
	LOG( "- Observer ---------------------" );
	{
		CTN ctn;

		typename CTN::allocator_type alloc = ctn.get_allocator(); UNUSED( alloc );
		typename CTN::key_compare cmp = ctn.key_comp(); UNUSED( cmp );
	}

	LOG( "- Access -----------------------" );
	{
		LOG( "-- Non Const" );
		CTN ctn( v.begin(), v.end() );

		LOG( "ctn.top() = " << ctn.top() );
		ILLEGAL( ctn.top() = Random::GetString(); )
		LOG( "ctn.top() = " << ctn.top() );
	}
	{
		LOG( "-- Const" );
		CTN const ctn( v.begin(), v.end() );

		LOG( "ctn.top() = " << ctn.top() );
		ILLEGAL( ctn.top() = Random::GetString(); )
		LOG( "ctn.top() = " << ctn.top() );
	}
	LOG( "- Capacity ---------------------" );
	{
		CTN const ctn( v.begin(), v.end() );

		LOG( "ctn.size() = " << ctn.size() );
		LOG( "ctn.max_size() = " << ctn.max_size() );
		LOG( "ctn.empty() = " << ctn.empty() );
	}
	LOG( "- Modifier ---------------------" );
	{
		CTN ctn( v.begin(), v.end() );

		LOG( "-- Push" );
		ctn.push( Random::GetInt() );
		LOG( ctn.top() );
		ctn.push( Random::GetInt() );
		LOG( ctn.top() );
		ctn.push( Random::GetInt() );
		LOG( ctn.top() );

		LOG( "-- Pop" );
		while ( ! ctn.empty() )
		{
			LOG( ctn.top() );
			ctn.pop();
		}

		ctn.push( Random::GetInt() );
		ctn.push( Random::GetInt() );
		ctn.push( Random::GetInt() );
		ctn.push( Random::GetInt() );

		LOG( "-- Pop" );
		while ( ! ctn.empty() )
		{
			LOG( ctn.top() );
			ctn.pop();
		}
	}
	LOG( "- Operation -------------------" );
	{
		CTN ctn( v.begin(), v.end() );

		CTN::value_type value;
		CTN::iterator it;

		LOG( "-- Find" );
		value = v[ Random::GetInt( 0, v.size() - 1 ) ];
		LOG( "find( " << value << " ) = " << *ctn.find( value ) );
		value = v[ Random::GetInt( 0, v.size() - 1 ) ];
		LOG( "find( " << value << " ) = " << *ctn.find( value ) );
		value = v[ Random::GetInt( 0, v.size() - 1 ) ];
		LOG( "find( " << value << " ) = " << *ctn.find( value ) );

		if ( ctn.find( 4242 ) != ctn.end() )
		{
			LOG( "ERROR: find( 4242 ) != ctn.end()" );
		}

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );

		LOG( "-- Decrease Key" );
		it = ctn.begin();
		ft::advance( it, Random::GetInt( 0, ctn.size() - 1 ) );
		LOG( "decrease_key( " << *it << " )" );
		ctn.decrease_key( it, -21 );

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );

		it = ctn.begin();
		ft::advance( it, Random::GetInt( 0, ctn.size() - 1 ) );
		LOG( "decrease_key( " << *it << " )" );
		ctn.decrease_key( it, -42, ft::assign_to< CTN::value_type >() );

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );

		LOG( "-- Merge" );
		CTN other( v.begin(), v.end() );
		ctn.merge(other);

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );

		LOG( "-- Pop" );
		while ( ! ctn.empty() )
		{
			LOG( ctn.top() );
			ctn.pop();
		}
	}
	{
		CTN const ctn( v.begin(), v.end() );

		LOG( "-- Find" );
		CTN::value_type value;
		value = v[ Random::GetInt( 0, v.size() - 1 ) ];
		LOG( "find( " << value << " ) = " << *ctn.find( value ) );
		value = v[ Random::GetInt( 0, v.size() - 1 ) ];
		LOG( "find( " << value << " ) = " << *ctn.find( value ) );
		value = v[ Random::GetInt( 0, v.size() - 1 ) ];
		LOG( "find( " << value << " ) = " << *ctn.find( value ) );

		if ( ctn.find( 4242 ) != ctn.end() )
		{
			LOG( "ERROR: find( 4242 ) != ctn.end()" );
		}
	}

	{
		LOG( "Special " );

		typedef ft::fibonacci_heap< ft::pair< int, std::string > >  fh;

		fh ctn;

		ctn.push( ft::make_pair( Random::GetInt(), Random::GetString() ) );
		ctn.push( ft::make_pair( Random::GetInt(), Random::GetString() ) );
		ctn.push( ft::make_pair( Random::GetInt(), Random::GetString() ) );
		ctn.push( ft::make_pair( Random::GetInt(), Random::GetString() ) );
		ctn.push( ft::make_pair( Random::GetInt(), Random::GetString() ) );

		fh::iterator it = ctn.begin();
		ft::advance( it, Random::GetInt( 1, ctn.size() - 1 ) );

		ILLEGAL( *it = ft::make_pair( Random::GetInt(), Random::GetString() ); )
		ILLEGAL( it->first = Random::GetInt(); )
		ILLEGAL( it->second = Random::GetString(); )

		LOG_RANGE( ctn.begin(), ctn.end() );

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
		ctn.push( "Random::GetString()" );
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
