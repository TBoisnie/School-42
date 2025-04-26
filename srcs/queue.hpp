#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "deque.hpp"
#include "priority_queue.hpp" // Note: Not used in this file, but required to be STD compliant

namespace ft
{

/**
 * Queue
 *
 * @ref https://en.cppreference.com/w/cpp/container/queue
 * @ref https://cplusplus.com/reference/queue/queue/
 */
template<
	typename T,
	typename Container = ft::deque< T >
>
class queue
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
	queue(
		container_type const & container = container_type()
	)
		: c( container )
	{
	}

	// Method ------------------------------------------------------------------
public:
	// - Access -------------------------
	value_type &       front()       { return this->c.front(); }
	value_type const & front() const { return this->c.front(); }
	value_type &       back()        { return this->c.back(); }
	value_type const & back() const  { return this->c.back(); }

	// - Capacity ---------------------
	size_type size() const  { return this->c.size(); }
	bool      empty() const { return this->c.empty(); }

	// - Modifier -----------------------
	void push( value_type const & value ) { this->c.push_back( value ); }
	void pop()                            { this->c.pop_front(); }

	// Friend ------------------------------------------------------------------
public:
	template<
		typename _T,
		typename _Container
	>
	friend bool
	operator==(
		ft::queue< _T, _Container > const & x,
		ft::queue< _T, _Container > const & y
	);

	template<
		typename _T,
		typename _Container
	>
	friend bool
	operator<(
		ft::queue< _T, _Container > const & x,
		ft::queue< _T, _Container > const & y
	);

}; // class queue

// - Relational Operator -------------------------------------------------------
template<
	typename T,
	typename Container
>
bool
operator==(
	ft::queue< T, Container > const & x,
	ft::queue< T, Container > const & y
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
	ft::queue< T, Container > const & x,
	ft::queue< T, Container > const & y
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
	ft::queue< T, Container > const & x,
	ft::queue< T, Container > const & y
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
	ft::queue< T, Container > const & x,
	ft::queue< T, Container > const & y
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
	ft::queue< T, Container > const & x,
	ft::queue< T, Container > const & y
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
	ft::queue< T, Container > const & x,
	ft::queue< T, Container > const & y
)
{
	return ( ! ( x < y ) );
}

} // namespace ft

#endif
