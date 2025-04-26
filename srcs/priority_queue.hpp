#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "algorithm.hpp"
#include "functional.hpp"
#include "vector.hpp"

namespace ft
{

/**
 * PriorityQueue
 *
 * @ref https://en.cppreference.com/w/cpp/container/priority_queue
 * @ref https://cplusplus.com/reference/queue/priority_queue/
 */
template<
	typename T,
	typename Container = ft::vector< T >,
	typename Compare = ft::less< typename Container::value_type >
>
class priority_queue
{
	// Type --------------------------------------------------------------------
public:
	typedef Container  container_type;
	typedef Compare    value_compare; // Note: Not standard, but 42-tester fail otherwise...

	typedef typename container_type::size_type   size_type;
	typedef typename container_type::value_type  value_type;


private:
	typedef Compare  compare_type;

	// Attribute ---------------------------------------------------------------
protected:
	container_type c;
	compare_type comp;

	// Constructor -------------------------------------------------------------
public:
	explicit
	priority_queue(
		compare_type const & compare = compare_type(),
		container_type const & container = container_type()
	)
		: c( container )
		, comp( compare )
    {
		ft::make_heap( this->c.begin(), this->c.end(), this->comp );
	}

	template<
		typename _InputIterator
	>
	priority_queue(
		_InputIterator first,
		_InputIterator last,
		compare_type const & compare = compare_type(),
		container_type const & container = container_type()
	)
		: c( container )
		, comp( compare )
	{
		this->c.insert( this->c.end(), first, last );
		ft::make_heap( this->c.begin(), this->c.end(), this->comp );
	}

	// Method ------------------------------------------------------------------
public:
	// - Access -----------------------
	value_type const & top() const { return this->c.front(); }

	// - Capacity ---------------------
	size_type size() const  { return this->c.size(); }
	bool      empty() const { return this->c.empty(); }

	// - Modifier ---------------------
	void
	push(
		value_type const & value
	)
	{
		try
		{
			this->c.push_back( value );
			ft::push_heap( this->c.begin(), this->c.end(), this->comp );
		}
		catch ( ... )
		{
			this->c.clear();
			throw ;
		}
	}

	void
	pop()
	{
		try
		{
			ft::pop_heap( this->c.begin(), this->c.end(), this->comp );
			this->c.pop_back();
		}
		catch ( ... )
		{
			this->c.clear();
			throw ;
		}
	}

}; // class priority_queue

} // namespace ft

#endif
