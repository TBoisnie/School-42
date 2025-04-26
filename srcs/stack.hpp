#ifndef STACK_HPP
#define STACK_HPP

#include "deque.hpp"

namespace ft
{

/**
 * Stack
 *
 * @ref https://en.cppreference.com/w/cpp/container/stack
 * @ref https://cplusplus.com/reference/stack/stack/
 */
template<
	typename T,
	typename Container = ft::deque< T >
>
class stack
{
	// Type --------------------------------------------------------------------
public:
	typedef Container  container_type;

	typedef typename container_type::size_type   size_type;
	typedef typename container_type::value_type  value_type;

	// Attribute ---------------------------------------------------------------
protected:
	container_type c;

	// Constructor -------------------------------------------------------------
public:
	explicit
	stack(
		container_type const & container = container_type()
	)
		: c( container )
	{
	}

	// Method ------------------------------------------------------------------
public:
	// - Access -----------------------
	value_type &       top()       { return this->c.back(); }
	value_type const & top() const { return this->c.back(); }

	// - Capacity ---------------------
	size_type size() const  { return this->c.size(); }
	bool      empty() const { return this->c.empty(); }

	// - Modifier ---------------------
	void push( value_type const & value ) { this->c.push_back( value ); }
	void pop()                            { this->c.pop_back(); }

	// Friend ------------------------------------------------------------------
public:
	template<
		typename _T,
		typename _Container
	>
	friend bool
	operator==(
		ft::stack< _T, _Container > const & x,
		ft::stack< _T, _Container > const & y
	);

	template<
		typename _T,
		typename _Container
	>
	friend bool
	operator<(
		ft::stack< _T, _Container > const & x,
		ft::stack< _T, _Container > const & y
	);

}; // class stack

// - Relation Operator ---------------------------------------------------------
template<
	typename T,
	typename Container
>
bool
operator==(
	ft::stack< T, Container > const & x,
	ft::stack< T, Container > const & y
)
{
	return ( x.c == y.c );
}

template<
	typename T,
	typename Container
>
bool
operator!=(
	ft::stack< T, Container > const & x,
	ft::stack< T, Container > const & y
)
{
	return ( ! ( x == y ) );
}

template<
	typename T,
	typename Container
>
bool
operator<(
	ft::stack< T, Container > const & x,
	ft::stack< T, Container > const & y
)
{
	return ( x.c < y.c );
}

template<
	typename T,
	typename Container
>
bool
operator<=(
	ft::stack< T, Container > const & x,
	ft::stack< T, Container > const & y
)
{
	return ( ! ( y < x ) );
}

template<
	typename T,
	typename Container
>
bool
operator>(
	ft::stack< T, Container > const & x,
	ft::stack< T, Container > const & y
)
{
	return ( y < x );
}

template<
	typename T,
	typename Container
>
bool
operator>=(
	ft::stack< T, Container > const & x,
	ft::stack< T, Container > const & y
)
{
	return ( ! ( x < y ) );
}

} // namespace ft

#endif
