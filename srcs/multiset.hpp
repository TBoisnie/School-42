#ifndef MULTISET_HPP
#define MULTISET_HPP

#include <memory> // std::allocator

#include "algorithm.hpp"
#include "functional.hpp"
#include "rb_tree.hpp"

namespace ft
{

/**
 * MultiSet
 *
 * @ref https://en.cppreference.com/w/cpp/container/multiset
 * @ref https://cplusplus.com/reference/set/multiset/
 */
template<
	typename T,
	typename Compare = ft::less< T >,
	typename Allocator = std::allocator< T >
>
class multiset
{
	// Type --------------------------------------------------------------------
public:
	typedef T          key_type;
	typedef T          value_type;

	typedef Compare    key_compare;
	typedef Compare    value_compare;

private:
	typedef ft::rb_tree< key_type, value_type, ft::identity< value_type >, key_compare, Allocator >  container_type;

public:
	typedef typename container_type::allocator_type          allocator_type;

	typedef typename container_type::size_type               size_type;
	typedef typename container_type::difference_type         difference_type;

	typedef typename container_type::reference               reference;
	typedef typename container_type::const_reference         const_reference;
	typedef typename container_type::pointer                 pointer;
	typedef typename container_type::const_pointer           const_pointer;

	typedef typename container_type::iterator                iterator;
	typedef typename container_type::const_iterator          const_iterator;
	typedef typename container_type::reverse_iterator        reverse_iterator;
	typedef typename container_type::const_reverse_iterator  const_reverse_iterator;

private:
	typedef ft::multiset< T, Compare, Allocator >  _self_type;

	// Attribute ---------------------------------------------------------------
private:
	container_type _container;

	// Constructor -------------------------------------------------------------
public:
	explicit
	multiset(
		value_compare const & compare = value_compare(),
		allocator_type const & allocator = allocator_type()
	)
		: _container( compare, allocator )
	{
	}

	template<
		typename _InputIterator
	>
	multiset(
		_InputIterator first,
		_InputIterator last,
		value_compare const & compare = value_compare(),
		allocator_type const & allocator = allocator_type()
	)
		: _container( compare, allocator )
	{
		this->_container.insert_equal( first, last );
	}

	multiset(
		_self_type const & other
	)
		: _container( other._container )
	{
	}

	// Operator ----------------------------------------------------------------
public:
	_self_type &
	operator=(
		_self_type const & other
	)
	{
		this->_container = other._container;
		return *this;
	}

	// Method ------------------------------------------------------------------
public:
	// - Observer ---------------------
	allocator_type get_allocator() const { return this->_container.get_allocator(); }

	key_compare    key_comp() const      { return this->_container.key_comp(); }
	value_compare  value_comp() const    { return this->_container.key_comp(); }

	// - Iterator ---------------------
	iterator               begin()        { return this->_container.begin(); }
	const_iterator         begin() const  { return this->_container.begin(); }
	iterator               end()          { return this->_container.end(); }
	const_iterator         end() const    { return this->_container.end(); }
	reverse_iterator       rbegin()       { return this->_container.rbegin(); }
	const_reverse_iterator rbegin() const { return this->_container.rbegin(); }
	reverse_iterator       rend()         { return this->_container.rend(); }
	const_reverse_iterator rend() const   { return this->_container.rend(); }

	// - Lookup ------------------------
	size_type count( value_type const & value ) const { return this->_container.count( value ); }

	iterator       find( value_type const & value )              { return this->_container.find( value ); }
	const_iterator find( value_type const & value ) const        { return this->_container.find( value ); }
	iterator       lower_bound( value_type const & value )       { return this->_container.lower_bound( value ); }
	const_iterator lower_bound( value_type const & value ) const { return this->_container.lower_bound( value ); }
	iterator       upper_bound( value_type const & value )       { return this->_container.upper_bound( value ); }
	const_iterator upper_bound( value_type const & value ) const { return this->_container.upper_bound( value ); }

	ft::pair< iterator, iterator >             equal_range( value_type const & value )       { return this->_container.equal_range( value ); }
	ft::pair< const_iterator, const_iterator > equal_range( value_type const & value ) const { return this->_container.equal_range( value ); }

	// - Capacity ---------------------
	size_type size() const     { return this->_container.size(); }
	size_type max_size() const { return this->_container.max_size(); }
	bool      empty() const    { return this->_container.empty(); }

	// - Modifier ---------------------
	iterator
	insert(
		value_type const & value
	)
	{
		return this->_container.insert_equal( value );
	}

	iterator
	insert(
		iterator position,
		value_type const & value
	)
	{
		return this->_container.insert_equal( position, value );
	}

	template<
		typename _InputIterator
	>
	void
	insert(
		_InputIterator first,
		_InputIterator last
	)
	{
		this->_container.insert_equal( first, last );
	}

	size_type
	erase(
		value_type const & value
	)
	{
		return this->_container.erase( value );
	}

	void
	erase(
		iterator position
	)
	{
		this->_container.erase( position );
	}

	void
	erase(
		iterator first,
		iterator last
	)
	{
		this->_container.erase( first, last );
	}

	void
	clear()
	{
		this->_container.clear();
	}

	void
	swap(
		_self_type & other
	)
	{
		this->_container.swap( other._container );
	}

	// Friend ------------------------------------------------------------------
public:
	template <
		class _T,
		class _Compare,
		class _Allocator
	>
	friend bool
	operator==(
		ft::multiset< _T, _Compare, _Allocator > const & x,
		ft::multiset< _T, _Compare, _Allocator > const & y
	);

	template <
		class _T,
		class _Compare,
		class _Allocator
	>
	friend bool
	operator<(
		ft::multiset< _T, _Compare, _Allocator > const & x,
		ft::multiset< _T, _Compare, _Allocator > const & y
	);

}; // class multiset

// - Relational Operator -------------------------------------------------------
template<
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator==(
	ft::multiset< T, Compare, Allocator > const & x,
	ft::multiset< T, Compare, Allocator > const & y
)
{
	return ( x._container == y._container );
}

template<
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator!=(
	ft::multiset< T, Compare, Allocator > const & x,
	ft::multiset< T, Compare, Allocator > const & y
)
{
	return ( ! ( x == y ) );
}

template<
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator<(
	ft::multiset< T, Compare, Allocator > const & x,
	ft::multiset< T, Compare, Allocator > const & y
)
{
	return ( x._container < y._container );
}

template<
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator<=(
	ft::multiset< T, Compare, Allocator > const & x,
	ft::multiset< T, Compare, Allocator > const & y
)
{
	return ( ! ( y < x ) );
}

template<
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator>(
	ft::multiset< T, Compare, Allocator > const & x,
	ft::multiset< T, Compare, Allocator > const & y
)
{
	return ( y < x );
}

template<
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator>=(
	ft::multiset< T, Compare, Allocator > const & x,
	ft::multiset< T, Compare, Allocator > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * Swap
 *
 * @ref https://cplusplus.com/reference/set/multiset/swap-free/
 * @ref https://en.cppreference.com/w/cpp/container/multiset/swap2
 */
template<
	typename T,
	typename Compare,
	typename Allocator
>
void
swap(
	ft::multiset< T, Compare, Allocator > & x,
	ft::multiset< T, Compare, Allocator > & y
)
{
	x.swap( y );
}

} // namespace ft

#endif
