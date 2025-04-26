#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{

/**
 * Pair
 *
 * @ref https://en.cppreference.com/w/cpp/utility/pair
 * @ref https://cplusplus.com/reference/utility/pair/
 */
template<
	typename T1,
	typename T2
>
class pair
{
	// Type --------------------------------------------------------------------
public:
	typedef T1  first_type;
	typedef T2  second_type;

private:
	typedef ft::pair< T1, T2 >  _self_type;

	// Attribute ---------------------------------------------------------------
public:
	first_type first;
	second_type second;

	// Constructor -------------------------------------------------------------
public:
	explicit
	pair()
		: first()
		, second()
	{
	}

	pair(
		first_type const & first,
		second_type const & second
	)
		: first( first )
		, second( second )
	{
	}

	template<
		typename _T1,
		typename _T2
	>
	pair(
		ft::pair< _T1, _T2 > const & other
	)
		: first( other.first )
		, second( other.second )
	{
	}

	// Operator ----------------------------------------------------------------
public:
	template<
		typename _T1,
		typename _T2
	>
	_self_type &
	operator=(
		ft::pair< _T1, _T2 > const & other
	)
	{
		if ( this != &other )
		{
			this->first = other.first;
			this->second = other.second;
		}

		return *this;
	}

}; // class pair

// - Relational Operator -------------------------------------------------------
template<
	typename T1,
	typename T2
>
bool
operator==(
	ft::pair< T1, T2 > const & x,
	ft::pair< T1, T2 > const & y
)
{
	return ( x.first == y.first && x.second == y.second );
}

template<
	typename T1,
	typename T2
>
bool
operator!=(
	ft::pair< T1, T2 > const & x,
	ft::pair< T1, T2 > const & y
)
{
	return ( ! ( x == y ) );
}

template<
	typename T1,
	typename T2
>
bool
operator<(
	ft::pair< T1, T2 > const & x,
	ft::pair< T1, T2 > const & y
)
{
	return ( ( x.first < y.first ) || ( ( ! ( y.first < x.first ) ) && ( x.second < y.second ) ) );
}

template<
	typename T1,
	typename T2
>
bool
operator<=(
	ft::pair< T1, T2 > const & x,
	ft::pair< T1, T2 > const & y
)
{
	return ( ! ( y < x ) );
}

template<
	typename T1,
	typename T2
>
bool
operator>(
	ft::pair< T1, T2 > const & x,
	ft::pair< T1, T2 > const & y
)
{
	return ( y < x );
}

template<
	typename T1,
	typename T2
>
bool
operator>=(
	ft::pair< T1, T2 > const & x,
	ft::pair< T1, T2 > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * MakePair
 *
 * @ref https://cplusplus.com/reference/utility/make_pair/
 * @ref https://en.cppreference.com/w/cpp/utility/pair/make_pair
 */
template<
	typename T1,
	typename T2
>
ft::pair< T1, T2 >
make_pair(
	T1 first,
	T2 second
)
{
	return ft::pair< T1, T2 >(first, second);
}

} // namespace ft

#endif
