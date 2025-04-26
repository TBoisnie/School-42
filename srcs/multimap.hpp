#ifndef MULTIMAP_HPP
#define MULTIMAP_HPP

#include <memory> // std::allocator

#include "algorithm.hpp"
#include "functional.hpp"
#include "utility.hpp"
#include "rb_tree.hpp"

namespace ft
{

/**
 * Map
 *
 * @ref https://en.cppreference.com/w/cpp/container/multimap
 * @ref https://cplusplus.com/reference/map/multimap/
 */
template<
	typename Key,
	typename T,
	typename Compare = ft::less< Key >,
	typename Allocator = std::allocator< ft::pair< Key const, T > >
>
class multimap
{
	// Type --------------------------------------------------------------------
public:
	typedef Key                       key_type;
	typedef T                         mapped_type;
	typedef ft::pair< Key const, T >  value_type;

	typedef Compare  key_compare;

private:
	typedef ft::rb_tree< key_type, value_type, ft::select1st< value_type >, key_compare, Allocator >  _container_type;

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
	typedef ft::multimap< Key, T, Compare, Allocator >  _self_type;

	// Nested class ------------------------------------------------------------
public:
	struct value_compare
		: public ft::binary_function< value_type, value_type, bool >
	{
		// - Type ---------------------
	private:
		typedef ft::binary_function< value_type, value_type, bool >  _self_base_type;

		using typename _self_base_type::first_argument_type;
		using typename _self_base_type::second_argument_type;
		using typename _self_base_type::result_type;

		// - Attribute ----------------
	protected:
		key_compare _compare;

		// - Constructor --------------
	protected:
		value_compare(
			key_compare compare
		)
			: _compare( compare )
		{
		}

		// - Operator -----------------
	public:
		result_type
		operator()(
			first_argument_type const & x,
			second_argument_type const & y
		) const
		{
			return this->_compare( x.first, y.first );
		}

		// - Friend -------------------
	public:
		friend class multimap< Key, T, Compare, Allocator >;

	};

	// Attribute ---------------------------------------------------------------
private:
	_container_type _container;

	// Constructor -------------------------------------------------------------
public:
	explicit
	multimap(
		key_compare const & compare = key_compare(),
		allocator_type const & allocator = allocator_type()
	)
		: _container( compare, allocator )
	{
	}

	template<
		typename _InputIterator
	>
	multimap(
		_InputIterator first,
		_InputIterator last,
		key_compare const & compare = key_compare(),
		allocator_type const & allocator = allocator_type()
	)
		: _container( compare, allocator )
	{
		this->_container.insert_equal( first, last );
	}

	multimap(
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
	value_compare  value_comp() const    { return value_compare( this->_container.key_comp() ); }

	// - Iterator ---------------------
	iterator               begin()        { return this->_container.begin(); }
	const_iterator         begin() const  { return this->_container.begin(); }
	iterator               end()          { return this->_container.end(); }
	const_iterator         end() const    { return this->_container.end(); }
	reverse_iterator       rbegin()       { return this->_container.rbegin(); }
	const_reverse_iterator rbegin() const { return this->_container.rbegin(); }
	reverse_iterator       rend()         { return this->_container.rend(); }
	const_reverse_iterator rend() const   { return this->_container.rend(); }

	// - Capacity ---------------------
	size_type size() const     { return this->_container.size(); }
	size_type max_size() const { return this->_container.max_size(); }
	bool      empty() const    { return this->_container.empty(); }

	// - Lookup ------------------------
	size_type count( key_type const & key ) const { return this->_container.count( key ); }

	iterator       find( key_type const & key )              { return this->_container.find( key ); }
	const_iterator find( key_type const & key ) const        { return this->_container.find( key ); }
	iterator       lower_bound( key_type const & key )       { return this->_container.lower_bound( key ); }
	const_iterator lower_bound( key_type const & key ) const { return this->_container.lower_bound( key ); }
	iterator       upper_bound( key_type const & key )       { return this->_container.upper_bound( key ); }
	const_iterator upper_bound( key_type const & key ) const { return this->_container.upper_bound( key ); }

	ft::pair< iterator, iterator >             equal_range( key_type const & key )       { return this->_container.equal_range( key ); }
	ft::pair< const_iterator, const_iterator > equal_range( key_type const & key ) const { return this->_container.equal_range( key ); }

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
		key_type const & key
	)
	{
		return this->_container.erase( key );
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
		typename _Key,
		typename _T,
		typename _Compare,
		typename _Allocator
	>
	friend bool
	operator==(
		ft::multimap< _Key, _T, _Compare, _Allocator > const & x,
		ft::multimap< _Key, _T, _Compare, _Allocator > const & y
	);

	template <
		typename _Key,
		typename _T,
		typename _Compare,
		typename _Allocator
	>
	friend bool
	operator<(
		ft::multimap< _Key, _T, _Compare, _Allocator > const & x,
		ft::multimap< _Key, _T, _Compare, _Allocator > const & y
	);

}; // class multimap

// - Relational Operator -------------------------------------------------------
template<
	typename Key,
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator==(
	ft::multimap< Key, T, Compare, Allocator > const & x,
	ft::multimap< Key, T, Compare, Allocator > const & y
)
{
	return ( x._container == y._container );
}

template<
	typename Key,
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator!=(
	ft::multimap< Key, T, Compare, Allocator > const & x,
	ft::multimap< Key, T, Compare, Allocator > const & y
)
{
	return ( ! ( x == y ) );
}

template<
	typename Key,
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator<(
	ft::multimap< Key, T, Compare, Allocator > const & x,
	ft::multimap< Key, T, Compare, Allocator > const & y
)
{
	return ( x._container < y._container );
}

template<
	typename Key,
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator<=(
	ft::multimap< Key, T, Compare, Allocator > const & x,
	ft::multimap< Key, T, Compare, Allocator > const & y
)
{
	return ( ! ( y < x ) );
}

template<
	typename Key,
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator>(
	ft::multimap< Key, T, Compare, Allocator > const & x,
	ft::multimap< Key, T, Compare, Allocator > const & y
)
{
	return ( y < x );
}

template<
	typename Key,
	typename T,
	typename Compare,
	typename Allocator
>
bool
operator>=(
	ft::multimap< Key, T, Compare, Allocator > const & x,
	ft::multimap< Key, T, Compare, Allocator > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * Swap
 *
 * @ref https://cplusplus.com/reference/map/multimap/swap-free/
 * @ref https://en.cppreference.com/w/cpp/container/multimap/swap2
 */
template<
	typename Key,
	typename T,
	typename Compare,
	typename Allocator
>
void
swap(
	ft::multimap< Key, T, Compare, Allocator > & x,
	ft::multimap< Key, T, Compare, Allocator > & y
)
{
	x.swap( y );
}

} // namespace ft

#endif
