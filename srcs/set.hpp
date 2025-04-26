#ifndef SET_HPP
#define SET_HPP

#include <memory> // std::allocator

#include "functional.hpp"
#include "rb_tree.hpp"
#include "multiset.hpp" // Note: Not used in this file, but required to be defined in the same header file

namespace ft
{

/**
 * Set
 *
 * @ref https://en.cppreference.com/w/cpp/container/set
 * @ref https://cplusplus.com/reference/set/set/
 */
template<
	typename T,
	typename Compare = ft::less< T >,
	typename Allocator = std::allocator< T >
>
class set
{
	// Type --------------------------------------------------------------------
public:
	typedef T        key_type;
	typedef T        value_type;

	typedef Compare  key_compare;
	typedef Compare  value_compare;

private:
	typedef ft::rb_tree< key_type, value_type, ft::identity< value_type >, key_compare, Allocator >  _container_type;

public:
	typedef typename _container_type::allocator_type          allocator_type;

	typedef typename _container_type::size_type               size_type;
	typedef typename _container_type::difference_type         difference_type;

	typedef typename _container_type::reference               reference;
	typedef typename _container_type::const_reference         const_reference;
	typedef typename _container_type::pointer                 pointer;
	typedef typename _container_type::const_pointer           const_pointer;

	typedef typename _container_type::iterator                iterator;
	typedef typename _container_type::const_iterator          const_iterator;
	typedef typename _container_type::reverse_iterator        reverse_iterator;
	typedef typename _container_type::const_reverse_iterator  const_reverse_iterator;

private:
	typedef ft::set< T, Compare, Allocator >  _self_type;

	// Attribute ---------------------------------------------------------------
private:
	_container_type _container;

	// Constructor -------------------------------------------------------------
public:
	explicit
	set(
		key_compare const & compare = key_compare(),
		allocator_type const & allocator = allocator_type()
	)
		: _container( compare, allocator )
	{
	}

	template<
		typename _InputIterator
	>
	set(
		_InputIterator first,
		_InputIterator last,
		key_compare const & compare = key_compare(),
		allocator_type const & allocator = allocator_type()
	)
		: _container( compare, allocator )
	{
		this->_container.insert_unique( first, last );
	}

	set(
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
	size_type count( value_type const & value ) const { return ( this->_container.find( value ) != this->_container.end() ); }

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
	ft::pair< iterator, bool >
	insert(
		value_type const & value
	)
	{
		return this->_container.insert_unique( value );
	}

	iterator
	insert(
		iterator position,
		value_type const & value
	)
	{
		return this->_container.insert_unique( position, value );
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
		this->_container.insert_unique( first, last );
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
		ft::set< _T, _Compare, _Allocator > const & x,
		ft::set< _T, _Compare, _Allocator > const & y
	);

	template <
		class _T,
		class _Compare,
		class _Allocator
	>
	friend bool
	operator<(
		ft::set< _T, _Compare, _Allocator > const & x,
		ft::set< _T, _Compare, _Allocator > const & y
	);

}; // class set

// - Relational Operator -------------------------------------------------------
template<
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator==(
	ft::set< T, Compare, Allocator > const & x,
	ft::set< T, Compare, Allocator > const & y
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
	ft::set< T, Compare, Allocator > const & x,
	ft::set< T, Compare, Allocator > const & y
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
	ft::set< T, Compare, Allocator > const & x,
	ft::set< T, Compare, Allocator > const & y
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
	ft::set< T, Compare, Allocator > const & x,
	ft::set< T, Compare, Allocator > const & y
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
	ft::set< T, Compare, Allocator > const & x,
	ft::set< T, Compare, Allocator > const & y
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
	ft::set< T, Compare, Allocator > const & x,
	ft::set< T, Compare, Allocator > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * Swap
 *
 * @ref https://cplusplus.com/reference/set/set/swap-free/
 * @ref https://en.cppreference.com/w/cpp/container/set/swap2
 */
template<
	typename T,
	typename Compare,
	typename Allocator
>
void
swap(
	ft::set< T, Compare, Allocator > & x,
	ft::set< T, Compare, Allocator > & y
)
{
	x.swap( y );
}

} // namespace ft

#endif
