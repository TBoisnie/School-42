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
# include <list>
#else
// # define NS  ft
# include "list.hpp"
#endif

#define CTN  NS::list< std::string >

/**
 * RemoveIfPredicate
 */
bool
remove_if_predicate(
	std::string const & str
)
{
	return ( str.size() <= 4 );
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
	std::vector< std::string >::iterator vit_a;
	std::vector< std::string >::iterator vit_b;

	LOG( "Type -------------------------------------------------------------" );
	CTN::allocator_type   allocator;   UNUSED( allocator );
	CTN::size_type        size;        UNUSED( size );
	CTN::difference_type  difference;  UNUSED( difference );

	CTN::value_type       value;                    UNUSED( value );
	CTN::reference        reference       = value;  UNUSED( reference );
	CTN::const_reference  const_reference = value;  UNUSED( const_reference );
	CTN::pointer          pointer;                  UNUSED( pointer );
	CTN::const_pointer    const_pointer;            UNUSED( const_pointer );

	CTN::iterator               iterator;                UNUSED( iterator );
	CTN::const_iterator         const_iterator;          UNUSED( const_iterator );
	CTN::reverse_iterator       reverse_iterator;        UNUSED( reverse_iterator );
	CTN::const_reverse_iterator const_reverse_iterator;  UNUSED( const_reverse_iterator );

	LOG( "Constructor ------------------------------------------------------" );
	LOG( "- Default ----------------------" );
	{
		CTN ctn;

		LOG_RANGE( ctn.begin(), ctn.end() );
	}
	{
		CTN ctn( allocator );

		LOG_RANGE( ctn.begin(), ctn.end() );
	}
	LOG( "- Fill -------------------------" );
	{
		CTN ctn( Random::GetInt( 8, 32 ) );

		LOG_RANGE( ctn.begin(), ctn.end() );
	}
	{
		CTN ctn( Random::GetInt( 8, 32 ), "Hello World" );

		LOG_RANGE( ctn.begin(), ctn.end() );
	}
	{
		CTN ctn( Random::GetInt( 8, 32 ), "Hello World", allocator );

		LOG_RANGE( ctn.begin(), ctn.end() );
	}
	LOG( "- Range ------------------------" );
	{
		CTN ctn( v.begin(), v.end() );

		LOG_RANGE( ctn.begin(), ctn.end() );
	}
	{
		CTN ctn( v.begin(), v.end(), allocator );

		LOG_RANGE( ctn.begin(), ctn.end() );
	}
	LOG( "- Copy -------------------------" );
	{
		CTN other( v.begin(), v.end() );
		CTN ctn( other );

		LOG_RANGE( ctn.begin(), ctn.end() );
	}

	LOG( "Operator ---------------------------------------------------------" );
	LOG( "- Assignation ------------------" );
	{
		CTN other( v.begin(), v.end() );
		CTN ctn = other;
	}
	LOG( "- Relational -------------------" );
	{
		CTN x( v.begin(), v.end() );
		CTN y( x );

		LOG( "-- Same " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );
		LOG( "x <  y : " << ( x <  y ) );
		LOG( "x <= y : " << ( x <= y ) );
		LOG( "x >  y : " << ( x >  y ) );
		LOG( "x >= y : " << ( x >= y ) );

		y.erase( y.begin() );

		LOG( "-- Different " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );
		LOG( "x <  y : " << ( x <  y ) );
		LOG( "x <= y : " << ( x <= y ) );
		LOG( "x >  y : " << ( x >  y ) );
		LOG( "x >= y : " << ( x >= y ) );
	}

	LOG( "Method -----------------------------------------------------------" );
	LOG( "- Observer ---------------------" );
	{
		CTN ctn;

		CTN::allocator_type allocator( ctn.get_allocator() );
	}
	LOG( "- Iterator ---------------------" );
	{
		LOG( "-- Non Const" );
		CTN ctn( v.begin(), v.end() );

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );
	}
	{
		LOG( "-- Const" );
		CTN const ctn( v.begin(), v.end() );

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( ctn.rbegin(), ctn.rend() );
	}
	LOG( "- Access -----------------------" );
	{
		LOG( "-- Non Const" );
		CTN ctn( v.begin(), v.end() );

		LOG( "ctn.front() = " << ctn.front() );
		ctn.front() = Random::GetString();
		LOG( "ctn.front() = " << ctn.front() );


		LOG( "ctn.back() = " << ctn.back() );
		ctn.back() = Random::GetString();
		LOG( "ctn.back() = " << ctn.back() );
	}
	{
		LOG( "-- Const" );
		CTN const ctn( v.begin(), v.end() );

		LOG( "ctn.front() = " << ctn.front() );
		ILLEGAL( ctn.front() = Random::GetString(); )
		LOG( "ctn.front() = " << ctn.front() );

		LOG( "ctn.back() = " << ctn.back() );
		ILLEGAL( ctn.back() = Random::GetString(); )
		LOG( "ctn.back() = " << ctn.back() );
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

		LOG( "-- Push / Pop Front" );
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.push_front( Random::GetString() );
		ctn.push_front( Random::GetString() );
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.pop_front();
		LOG_RANGE( ctn.begin(), ctn.end() );

		LOG( "-- Push / Pop Back" );
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.push_back( Random::GetString() );
		ctn.push_back( Random::GetString() );
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.pop_back();
		LOG_RANGE( ctn.begin(), ctn.end() );

		LOG( "-- Resize" );
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.resize( 8 );
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.resize( 16 );
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.resize( 32, Random::GetString() );
		LOG_RANGE( ctn.begin(), ctn.end() );

		CTN other;

		LOG( "-- Swap" );
		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );
		ctn.swap( other );
		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );

		LOG( "-- Clear" );
		ctn.clear();
		LOG_RANGE( ctn.begin(), ctn.end() );

		LOG( "-- Assign" );
		ctn.assign( Random::GetInt( 8, 16 ), Random::GetString() );
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.assign( Random::GetInt( 24, 48 ), Random::GetString() );
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.assign( v.begin(), v.end() );
		LOG_RANGE( ctn.begin(), ctn.end() );

		CTN::iterator it;

		LOG( "-- Insert" );
		ctn.insert( ctn.begin(), Random::GetString() );

		it = ctn.begin();
		NS::advance( it, Random::GetInt( 4, 12 ) );

		ctn.insert( it, Random::GetString() );
		LOG_RANGE( ctn.begin(), ctn.end() );

		ctn.insert( ctn.begin(), Random::GetInt( 5, 10 ), Random::GetString() );
		LOG_RANGE( ctn.begin(), ctn.end() );

		it = ctn.begin();
		NS::advance( it, Random::GetInt( 4, 12 ) );

		ctn.insert( it, Random::GetInt( 5, 10 ), Random::GetString() );
		LOG_RANGE( ctn.begin(), ctn.end() );

		vit_a = v.begin();
		NS::advance( vit_a, Random::GetInt( 0, 4 ) );
		vit_b = vit_a;
		NS::advance( vit_b, Random::GetInt( 0, 4 ) );

		ctn.insert( ctn.begin(), vit_a, vit_b );
		LOG_RANGE( ctn.begin(), ctn.end() );

		it = ctn.begin();
		NS::advance( it, 8 );

		ctn.insert( it, vit_a, vit_b );
		LOG_RANGE( ctn.begin(), ctn.end() );

		LOG( "-- Erase" );
		ctn.erase( ctn.begin() );
		LOG_RANGE( ctn.begin(), ctn.end() );

		it = ctn.begin();
		NS::advance( it, 8 );

		ctn.erase( it );
		LOG_RANGE( ctn.begin(), ctn.end() );

		CTN::iterator it_a( ctn.begin() );
		NS::advance( it_a, Random::GetInt( 0, 4 ) );
		CTN::iterator it_b( it_a );
		NS::advance( it_b, Random::GetInt( 1, 4 ) );

		ctn.erase( it_a, it_b );
		LOG_RANGE( ctn.begin(), ctn.end() );
	}

	LOG( "- Operation --------------------" );
	{
		CTN ctn;
		CTN other;

		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );

		LOG( "-- Sort" );
		ctn.sort();
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.push_front( *v.begin() );
		ctn.sort();
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.insert( ctn.begin(), v.begin(), v.end() );
		ctn.sort();
		LOG_RANGE( ctn.begin(), ctn.end() );
		ctn.sort();
		other.sort();
		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );

		LOG( "-- Merge" );
		ctn.merge( other );
		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );
		other.push_front( *v.begin() );
		ctn.merge( other );
		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );
		other.insert( other.begin(), v.begin() + Random::GetInt( 2, 6 ), v.end() - Random::GetInt( 2, 6 ) );
		ctn.merge( other );
		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );

		LOG( "-- Unique" );
		ctn.unique();
		LOG_RANGE( ctn.begin(), ctn.end() );

		LOG( "-- Reverse" );
		ctn.reverse();
		LOG_RANGE( ctn.begin(), ctn.end() );

		other.assign( v.begin(), v.end() - Random::GetInt( 2, 4 ) );

		CTN::iterator it;

		it = ctn.begin();
		NS::advance( it, Random::GetInt( 0, 8 ) );

		LOG( "-- Splice After" );
		ctn.splice( it, other, other.begin() );
		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );

		it = ctn.begin();
		NS::advance( it, Random::GetInt( 0, 8 ) );

		CTN::iterator first = other.begin();
		NS::advance( first, Random::GetInt( 0, 2 ) );
		CTN::iterator last = first;
		NS::advance( last, Random::GetInt( 1, 4 ) );

		ctn.splice( it, other, first, last );
		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );

		it = ctn.begin();
		NS::advance( it, Random::GetInt( 0, 8 ) );

		ctn.splice( it, other );
		LOG_RANGE( ctn.begin(), ctn.end() );
		LOG_RANGE( other.begin(), other.end() );

		it = ctn.begin();
		NS::advance( it, Random::GetInt( 0, 8 ) );

		std::string element = *it;

		LOG( "-- Remove" );
		ctn.remove( element );
		LOG_RANGE( ctn.begin(), ctn.end() );

		LOG( "-- Remove If" );
		ctn.remove_if( remove_if_predicate );
		LOG_RANGE( ctn.begin(), ctn.end() );
	}

	LOG( "Iterator ---------------------------------------------------------" );
	LOG( "- Constructor ------------------" );
	LOG( " -- Default" );
	{
		CTN::iterator it;
	}
	LOG( " -- Copy " );
	{
		LOG( "--- Non Const" );
		CTN ctn( v.begin(), v.end() );

		CTN::iterator it( ctn.begin() );
		LOG_RANGE( it, ctn.end() );
	}
	{
		LOG( "--- Const" );
		CTN const ctn( v.begin(), v.end() );

		CTN::const_iterator it( ctn.begin() );
		LOG_RANGE( it, ctn.end() );
	}
	{
		LOG( "--- Non Const -> Const" );
		CTN ctn( v.begin(), v.end() );

		CTN::const_iterator first( ctn.begin() );
		CTN::const_iterator last( ctn.end() );
		LOG_RANGE( first, last );
	}
	{
		LOG( "--- Const -> Non Const" );
		CTN const ctn( v.begin(), v.end() );

		ILLEGAL( CTN::iterator it( ctn.begin() ); )
	}
	LOG( "- Operator ---------------------" );
	LOG( "-- Assignation" );
	{
		CTN ctn( v.begin(), v.end() );

		CTN::iterator it;
		it = ctn.begin();

		LOG_RANGE( it, ctn.end() );
	}
	LOG( "-- Access" );
	{
		LOG( "--- Non Const" );
		CTN ctn( v.begin(), v.end() );

		CTN::iterator it( ctn.begin() );

		LOG( "*it = " << *it );
		*it = Random::GetString();
		LOG( "*it = " << *it );
		LOG( "it->size() = " << it->size() );
	}
	{
		LOG( "--- Const" );
		CTN const ctn( v.begin(), v.end() );

		CTN::const_iterator it( ctn.begin() );

		LOG( "*it = " << *it );
		ILLEGAL( *it = Random::GetString(); )
		LOG( "*it = " << *it );
		LOG( "it->size() = " << it->size() );
	}
	LOG( "-- Arithmetic" );
	{
		CTN const ctn( v.begin(), v.end() );

		CTN::const_iterator it( ctn.begin() );
		NS::advance( it, Random::GetInt( 4, 8 ) );

		LOG( "*it = " << *it );
		LOG( "*( ++it ) = " << *( ++it ) );
		LOG( "*( it++ ) = " << *( it++ ) );
		LOG( "*it = " << *it );

		LOG( "*it = " << *it );
		LOG( "*( --it ) = " << *( --it ) );
		LOG( "*( it-- ) = " << *( it-- ) );
		LOG( "*it = " << *it );
	}
	LOG( "-- Relational" );
	{
		LOG( "--- Non Const" );
		CTN ctn( v.begin(), v.end() );

		CTN::iterator x( ctn.begin() );
		CTN::iterator y( ctn.begin() );

		LOG( "---- Same " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );

		NS::advance( y, Random::GetInt( 1, 8 ) );

		LOG( "---- Different " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );
	}
	{
		LOG( "--- Const" );
		CTN const ctn( v.begin(), v.end() );

		CTN::const_iterator x( ctn.begin() );
		CTN::const_iterator y( ctn.begin() );

		LOG( "---- Same " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );

		NS::advance( y, Random::GetInt( 1, 8 ) );

		LOG( "---- Different " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );
	}
	{
		LOG( "--- Const / Non Const" );
		CTN ctn( v.begin(), v.end() );

		CTN::const_iterator x( ctn.begin() );
		CTN::iterator y( ctn.begin() );

		LOG( "---- Same " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );

		NS::advance( y, Random::GetInt( 1, 8 ) );

		LOG( "---- Different " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );
	}

	LOG( "Function ---------------------------------------------------------" );
	LOG( "- Swap -------------------------" );
	{
		CTN x( v.begin(), v.end() );
		CTN y;

		NS::swap( x, y );

		LOG_RANGE( x.begin(), x.end() );
		LOG_RANGE( y.begin(), y.end() );
	}
}
#else // PERFORMANCE_MDOE
{
	Time start = Time::Now();

	CTN ctn;

	Time insert = Time::Now();
	ctn.insert( ctn.begin(), 1000000, "Random::GetString()" );
	LOG( "Time Insert (us): " << Time::Now().Sub( insert ).ToMicroSecond() );

	CTN::iterator first( ctn.begin() );
	NS::advance( first, 100000 );
	CTN::iterator last( first );
	NS::advance( last, 250000 );

	Time erase = Time::Now();
	ctn.erase( first, last );
	LOG( "Time Erase (us): " << Time::Now().Sub( erase ).ToMicroSecond() );

	Time assign = Time::Now();
	ctn.assign( 1000000, "Random::GetString()" );
	LOG( "Time Assign (us): " << Time::Now().Sub( assign ).ToMicroSecond() );

	ctn.clear();
	for ( int i = 0 ; i < 1000000 ; ++i )
	{
		ctn.push_front( Random::GetString() );
	}

	Time sort = Time::Now();
	ctn.sort();
	LOG( "Time Sort (us): " << Time::Now().Sub( sort ).ToMicroSecond() );

	Time unique = Time::Now();
	ctn.unique();
	LOG( "Time Unique (us): " << Time::Now().Sub( unique ).ToMicroSecond() );

	CTN other;
	for ( int i = 0 ; i < 1000000 ; ++i )
	{
		other.push_front( Random::GetString() );
	}
	other.sort();

	Time merge = Time::Now();
	ctn.merge( other );
	LOG( "Time Merge (us): " << Time::Now().Sub( merge ).ToMicroSecond() );

	Time remove = Time::Now();
	ctn.remove_if( remove_if_predicate );
	LOG( "Time Remove If (us): " << Time::Now().Sub( remove ).ToMicroSecond() );

	LOG( "Time Total (us): " << Time::Now().Sub( start ).ToMicroSecond() );
}
#endif // PERFORMANCE_MDOE

}
