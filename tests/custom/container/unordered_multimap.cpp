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
# include <unordered_map>
#else
// # define NS  ft
# include "unordered_map.hpp"
#endif

#define CTN  NS::unordered_multimap< int, std::string >

namespace NS
{
std::ostream &
operator<<(
	std::ostream & out,
	NS::pair< int, std:: string > const & p
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
	std::vector< int > k;
	std::vector< NS::pair< int, std::string > > v;

	for ( int i = 0 ; i < 16 ; ++i )
	{
		int index = Random::GetInt();

		 // Add some duplicates
		if ( i % 4 == 0 )
		{
			v.push_back( NS::make_pair( index, Random::GetString() ) );
		}

		v.push_back( NS::make_pair( index, Random::GetString() ) );
		k.push_back( index );
	}

#ifndef PERFORMANCE_MODE
{
	std::vector< NS::pair< int, std::string > >::iterator vit_b;
	std::vector< NS::pair< int, std::string > >::iterator vit_a;

	LOG( "Type -------------------------------------------------------------" );
	CTN::allocator_type   allocator;   UNUSED( allocator );
	CTN::size_type        size;        UNUSED( size );
	CTN::difference_type  difference;  UNUSED( difference );

	CTN::hasher     hasher;     UNUSED( hasher );
	CTN::key_equal  key_equal;  UNUSED( key_equal );

	CTN::key_type         key = 0;                  UNUSED( key );
	CTN::mapped_type      mapped;                   UNUSED( mapped );
	CTN::value_type       value;                    UNUSED( value );
	CTN::reference        reference       = value;  UNUSED( reference );
	CTN::const_reference  const_reference = value;  UNUSED( const_reference );
	CTN::pointer          pointer;                  UNUSED( pointer );
	CTN::const_pointer    const_pointer;            UNUSED( const_pointer );

	CTN::iterator               iterator;              UNUSED( iterator );
	CTN::const_iterator         const_iterator;        UNUSED( const_iterator );
	CTN::local_iterator         local_iterator;        UNUSED( local_iterator );
	CTN::const_local_iterator   const_local_iterator;  UNUSED( const_local_iterator );

	LOG( "Constructor ------------------------------------------------------" );
	LOG( "- Default ----------------------" );
	{
		CTN ctn;
	}
	{
		CTN ctn( allocator );
	}
	LOG( "- Fill -------------------------" );
	{
		CTN ctn( Random::GetInt( 10, 10 ) );

		LOG( "Buckets: " << ctn.bucket_count() );
	}
	{
		CTN ctn( Random::GetInt( 8, 32 ), hasher );

		LOG( "Buckets: " << ctn.bucket_count() );
	}
	{
		CTN ctn( Random::GetInt( 8, 32 ), hasher, key_equal );

		LOG( "Buckets: " << ctn.bucket_count() );
	}
	{
		CTN ctn( Random::GetInt( 8, 32 ), hasher, key_equal, allocator );

		LOG( "Buckets: " << ctn.bucket_count() );
	}
	LOG( "- Range ------------------------" );
	{
		CTN ctn( v.begin(), v.end() );

		LOG( "Buckets: " << ctn.bucket_count() );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
	}
	{
		CTN ctn( v.begin(), v.end(), Random::GetInt( 24, 32 ) );

		LOG( "Buckets: " << ctn.bucket_count() );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
	}
	{
		CTN ctn( v.begin(), v.end(), Random::GetInt( 24, 32 ), hasher );

		LOG( "Buckets: " << ctn.bucket_count() );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
	}
	{
		CTN ctn( v.begin(), v.end(), Random::GetInt( 24, 32 ), hasher, key_equal );

		LOG( "Buckets: " << ctn.bucket_count() );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
	}
	{
		CTN ctn( v.begin(), v.end(), Random::GetInt( 24, 32 ), hasher, key_equal, allocator );

		LOG( "Buckets: " << ctn.bucket_count() );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
	}
	LOG( "- Copy -------------------------" );
	{
		CTN other( v.begin(), v.end() );
		CTN ctn( other );

		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
	}
	{
		CTN other( v.begin(), v.end() );
		CTN ctn( other, allocator );

		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
	}

	LOG( "Operator ---------------------------------------------------------" );
	LOG( "- Assignation ------------------" );
	{
		CTN other( v.begin(), v.end() );
		CTN ctn = other;

		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
	}
	LOG( "- Relational -------------------" );
	{
		CTN x( v.begin(), v.end() );
		CTN y( x );

		LOG( "-- Same " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );

		y.erase( Random::GetInt( 4, 8 ) );

		LOG( "-- Different " );
		LOG( "x == y : " << ( x == y ) );
		LOG( "x != y : " << ( x != y ) );
	}

	LOG( "Method -----------------------------------------------------------" );
	LOG( "- Observer ---------------------" );
	{
		CTN ctn;

		CTN::allocator_type allocator( ctn.get_allocator() ); UNUSED(allocator);
		CTN::hasher hash( ctn.hash_function() ); UNUSED(hash);
		CTN::key_equal equal( ctn.key_eq() ); UNUSED(equal);
	}
	LOG( "- Iterator ---------------------" );
	{
		LOG( "-- Non Const" );
		CTN ctn( v.begin(), v.end() );

		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
		int index = Random::GetInt( 1, ctn.bucket_count() ) - 1;
		LOG_URANGE( CTN, ctn.begin( index ), ctn.end( index ) );
	}
	{
		LOG( "-- Const" );
		CTN const ctn( v.begin(), v.end() );

		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
		int index = Random::GetInt( 1, ctn.bucket_count() ) - 1;
		LOG_URANGE( CTN, ctn.begin( index ), ctn.end( index ) );
	}
	LOG( "- Capacity ---------------------" );
	{
		CTN const ctn( v.begin(), v.end() );

		LOG( "ctn.size() = " << ctn.size() );
		LOG( "ctn.max_size() = " << ctn.max_size() );
		LOG( "ctn.empty() = " << ctn.empty() );
	}
	LOG( "- Bucket -----------------------" );
	{
		CTN const ctn( v.begin(), v.end() );

		int kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		int index = Random::GetInt( 0, ctn.bucket_count() - 1 );

		LOG( "ctn.bucket( " << kk << " ) = " << ctn.bucket( kk ) );
		LOG( "ctn.bucket_size( " << index << " ) = " << ctn.bucket_size( index ) );
		LOG( "ctn.bucket_count() = " << ctn.bucket_count() );
		LOG( "ctn.max_bucket_count() = " << ctn.max_bucket_count() );
	}
	LOG( "- Hash Policy ------------------" );
	{
		CTN ctn( v.begin(), v.end() );

		LOG( "ctn.load_factor() = " << ctn.load_factor() );
		LOG( "ctn.max_load_factor() = " << ctn.max_load_factor() );
		ctn.max_load_factor( Random::GetFloat( 0.25, 2 ) );
		LOG( "ctn.max_load_factor() = " << ctn.max_load_factor() );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
		LOG( "ctn.max_load_factor() = " << ctn.max_load_factor() );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
		ctn.rehash( Random::GetInt( 8, 32 ) );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
	}
	LOG( "- Lookup -----------------------" );
	{
		LOG( "-- Non Const");
		CTN ctn( v.begin(), v.end() );

		int kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		LOG( "ctn.count( " << kk << " )" << ctn.count( kk ) );
		kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		LOG( "ctn.count( " << kk << " )" << ctn.count( kk ) );
		kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		LOG( "ctn.count( " << kk << " )" << ctn.count( kk ) );

		kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		LOG( "ctn.find( " << kk << " ) = " << *ctn.find( kk ) );

		kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		NS::pair< CTN::iterator, CTN::iterator > range = ctn.equal_range( kk );
		LOG_URANGE( CTN, range.first, range.second );
	}
	{
		LOG( "-- Const");
		CTN const ctn( v.begin(), v.end() );

		int kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		LOG( "ctn.count( " << kk << " )" << ctn.count( kk ) );
		kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		LOG( "ctn.count( " << kk << " )" << ctn.count( kk ) );
		kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		LOG( "ctn.count( " << kk << " )" << ctn.count( kk ) );

		kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		LOG( "ctn.find( " << kk << " ) = " << *ctn.find( kk ) );

		kk = k[ Random::GetInt( 0, k.size() - 1 ) ];
		NS::pair< CTN::const_iterator, CTN::const_iterator > range = ctn.equal_range( kk );
		LOG_URANGE( CTN, range.first, range.second );
	}
	LOG( "- Modifier ---------------------" );
	{
		CTN ctn( v.begin() + 4, v.end() - 2 );
		CTN other( v.begin(), v.end() );

		LOG( "-- Swap" );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
		LOG_URANGE( CTN, other.begin(), other.end() );
		ctn.swap( other );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
		LOG_URANGE( CTN, other.begin(), other.end() );

		CTN::iterator it;

		LOG( "-- Insert" );
		ctn.insert( NS::make_pair( Random::GetInt(), Random::GetString() ) );

		it = ctn.begin();
		NS::advance( it, Random::GetInt( 4, 12 ) );

		ctn.insert( it, NS::make_pair( Random::GetInt(), Random::GetString() ) );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );

		vit_a = v.begin();
		NS::advance( vit_a, Random::GetInt( 0, 4 ) );
		vit_b = vit_a;
		NS::advance( vit_b, Random::GetInt( 0, 4 ) );

		ctn.insert( vit_a, vit_b );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );

		LOG( "-- Erase" );
		ctn.erase( k[ Random::GetInt( 0, k.size() / 2 ) ] );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );

		ctn.erase( ctn.find( k[ Random::GetInt( k.size() / 2 + 2, k.size() - 1 ) ] ) );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );

		CTN::iterator it_a( ctn.begin() );
		NS::advance( it_a, Random::GetInt( 0, ctn.size() / 2 - 1 ) );
		CTN::iterator it_b( it_a );
		NS::advance( it_b, Random::GetInt( 1, ctn.size() / 2 - 1 ) );

		ctn.erase( it_a, it_b );
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );

		LOG( "-- Clear" );
		ctn.clear();
		LOG_URANGE( CTN, ctn.begin(), ctn.end() );
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
		LOG_URANGE( CTN, it, ctn.end() );
	}
	{
		LOG( "--- Const" );
		CTN const ctn( v.begin(), v.end() );

		CTN::const_iterator it( ctn.begin() );
		LOG_URANGE( CTN, it, ctn.end() );
	}
	{
		LOG( "--- Non Const -> Const" );
		CTN ctn( v.begin(), v.end() );

		CTN::const_iterator first( ctn.begin() );
		CTN::const_iterator last( ctn.end() );
		LOG_URANGE( CTN, first, last );
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

		LOG_URANGE( CTN, it, ctn.end() );
	}
	LOG( "-- Access" );
	{
		LOG( "--- Non Const" );
		CTN ctn( v.begin(), v.end() );

		CTN::iterator it( ctn.begin() );

		LOG( "*it = " << *it );
		ILLEGAL( *it = NS::make_pair( Random::GetInt(), Random::GetString() ); )
		ILLEGAL( it->first = Random::GetInt(); )
		it->second = Random::GetString();
		LOG( "*it = " << *it );
	}
	{
		LOG( "--- Const" );
		CTN const ctn( v.begin(), v.end() );

		CTN::const_iterator it( ctn.begin() );

		LOG( "*it = " << *it );
		ILLEGAL( *it = NS::make_pair( Random::GetInt(), Random::GetString() ); )
		ILLEGAL( it->first = Random::GetInt(); )
		ILLEGAL( it->second = Random::GetString(); )
		LOG( "*it = " << *it );
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

		LOG_URANGE( CTN, x.begin(), x.end() );
		LOG_URANGE( CTN, y.begin(), y.end() );
	}
}
#else // PERFORMANCE_MDOE
{
	Time start = Time::Now();

	CTN ctn;

	Time insert = Time::Now();
	for ( int i = 0 ; i < 1000000 ; ++i )
	{
		ctn.insert( NS::make_pair( i >> 1, "Random::GetString()" ) );
	}
	LOG( "Time Insert (us): " << Time::Now().Sub( insert ).ToMicroSecond() );

	CTN::iterator first( ctn.begin() );
	NS::advance( first, 100000 );
	CTN::iterator last( first );
	NS::advance( last, 500000 );

	Time erase = Time::Now();
	ctn.erase( first, last );
	LOG( "Time Erase (us): " << Time::Now().Sub( erase ).ToMicroSecond() );

	ctn.clear();

	LOG( "Time Total (us): " << Time::Now().Sub( start ).ToMicroSecond() );
}
#endif // PERFORMANCE_MDOE

}
