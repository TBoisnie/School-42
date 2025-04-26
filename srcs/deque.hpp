#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <cstddef> // size_t, ptrdiff_t
#include <memory> // std::allocator

#include "algorithm.hpp"
#include "functional.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "stdexcept.hpp"
#include "type_traits.hpp"

namespace ft
{

// Forward Declaration
template<
	typename T,
	typename Allocator = std::allocator< T >
>
class deque;

namespace
{

template<
	typename T
>
size_t
_get_node_size()
{
	return ( ( sizeof(T) < 512 ) ? ( 512 / sizeof(T) ) : 1 );
}

/**
 * DequeIterator
 */
template<
	typename T,
	bool IsConst
>
class _deque_iterator
	: public ft::iterator<
		ft::random_access_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>
{
	// Type --------------------------------------------------------------------
private:
	typedef ft::iterator<
		ft::random_access_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>                                      _self_base_type;
	typedef _deque_iterator< T, IsConst >  _self_type;

public:
	using typename _self_base_type::difference_type;

	using typename _self_base_type::value_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::pointer;

private:
	typedef typename ft::conditional< IsConst, pointer const, pointer >::type  _node_type;

	// Attribute ---------------------------------------------------------------
private:
	_node_type * _node;

	pointer _first;
	pointer _current;
	pointer _last;

	// Constructor -------------------------------------------------------------
public:
	_deque_iterator()
		: _node( nullptr )
		, _first( nullptr )
		, _current( nullptr )
		, _last( nullptr )
	{
	}

	_deque_iterator(
		_node_type * node,
		pointer current
	)
		: _node( node )
		, _first( *node )
		, _current( current )
		, _last( *node + _get_node_size< value_type >() )
	{
	}

	// Note: Allow conversion from non-const to const iterator
	template<
		typename _T
	>
	_deque_iterator(
		_deque_iterator< _T, false > const & other
	)
		: _node( other._get_node() )
		, _first( other._get_first() )
		, _current( other._get_current() )
		, _last( other._get_last() )
	{
	}

	_deque_iterator(
		_self_type const & other
	)
		: _node( other._get_node() )
		, _first( other._get_first() )
		, _current( other._get_current() )
		, _last( other._get_last() )
	{
	}

	// Operator ----------------------------------------------------------------
public:
	// - Access ------------------------
	reference
	operator*() const
	{
		return ( *( this->_current ) );
	}

	pointer
	operator->() const
	{
		return this->_current;
	}

	reference
	operator[](
		difference_type const & index
	) const
	{
		return ( *( *this + index ) );
	}

	// - Arithmetic --------------------
	_self_type &
	operator++()
	{
		this->_increment();
		return *this;
	}

	_self_type
	operator++( int )
	{
		_self_type self = *this;
		this->_increment();
		return self;
	}

	_self_type &
	operator--()
	{
		this->_decrement();
		return *this;
	}

	_self_type
	operator--( int )
	{
		_self_type self = *this;
		this->_decrement();
		return self;
	}

	_self_type
	operator+(
		difference_type const & amount
	) const
	{
		_self_type self = *this;
		return ( self += amount );
	}

	_self_type &
	operator+=(
		difference_type const & amount
	)
	{
		this->_increment(amount);
		return *this;
	}

	_self_type
	operator-(
		difference_type const & amount
	) const
	{
		_self_type self = *this;
		return ( self -= amount );
	}

	_self_type &
	operator-=(
		difference_type const & amount
	)
	{
		this->_decrement( amount );
		return *this;
	}

	difference_type
	operator-(
		_self_type const & other
	) const
	{
		return (
			( this->_node - other._node - 1 ) * static_cast< difference_type >( _get_node_size< value_type >() )
			+ ( this->_current - this->_first )
			+ ( other._last - other._current )
		);
	}

	// Method ------------------------------------------------------------------
private:
	// - Access ------------------------
	_node_type *
	_get_node() const
	{
		return this->_node;
	}

	pointer
	_get_first() const
	{
		return this->_first;
	}

	pointer
	_get_current() const
	{
		return this->_current;
	}

	pointer
	_get_last() const
	{
		return this->_last;
	}

	// - Modifier ----------------------
	void
	_set_node(
		_node_type * node
	)
	{
		this->_node  =  node;
		this->_first = *node;
		this->_last  = *node + _get_node_size< value_type >();
	}

	void
	_set_current(
		pointer current
	)
	{
		this->_current = current;
	}

	void
	_increment(
		difference_type amount = 1
	)
	{
		if ( amount < 0 )
		{
			return this->_decrement(-amount);
		}

		difference_type const node_size = _get_node_size< value_type >();
		difference_type const offset = ( this->_current - this->_first ) + amount;
		difference_type const node_offset = offset / node_size;

		if ( offset >= node_size )
		{
			this->_set_node( this->_node + node_offset );
		}

		this->_current = this->_first + ( offset - ( node_offset * node_size ) );
	}

	void
	_decrement(
		difference_type amount = 1
	)
	{
		if ( amount < 0 )
		{
			return this->_increment(-amount);
		}

		difference_type const node_size = _get_node_size< value_type >();
		difference_type const offset = ( this->_last - this->_current ) + amount - 1;
		difference_type const node_offset = offset / node_size;

		if ( offset >= node_size )
		{
			this->_set_node( this->_node - node_offset );
		}

		this->_current = this->_last - ( offset - ( node_offset * node_size ) ) - 1;
	}

	// Friend ------------------------------------------------------------------
public:
	// - Class -------------------------
	template<
		typename _T,
		typename _Allocator
	>
	friend class ft::deque;

	template<
		typename _T,
		bool _IsConst
	>
	friend class _deque_iterator;

	// - Relational Operator -----------
	// -- Same Constness ---------------
	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_deque_iterator< _T, _IsConst > const & x,
		_deque_iterator< _T, _IsConst > const & y
	);

	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator<(
		_deque_iterator< _T, _IsConst > const & x,
		_deque_iterator< _T, _IsConst > const & y
	);

	// -- Different Constness ----------
	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_deque_iterator< _T,   _IsConst > const & x,
		_deque_iterator< _T, ! _IsConst > const & y
	);

	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator<(
		_deque_iterator< _T,   _IsConst > const & x,
		_deque_iterator< _T, ! _IsConst > const & y
	);

}; // class _deque_iterator

// - Arithmetic Operator -------------------------------------------------------
template<
	typename T,
	bool IsConst
>
_deque_iterator< T, IsConst >
operator+(
	typename _deque_iterator< T, IsConst >::difference_type amount,
	_deque_iterator< T, IsConst > const & it
)
{
	return ( it + amount );
}

// - Relational Operator -------------------------------------------------------
// -- Same Constness -------------------
template<
	typename T,
	bool IsConst
>
bool
operator==(
	_deque_iterator< T, IsConst > const & x,
	_deque_iterator< T, IsConst > const & y
)
{
	return ( x._get_current() == y._get_current() );
}

template<
	typename T,
	bool IsConst
>
bool
operator!=(
	_deque_iterator< T, IsConst > const & x,
	_deque_iterator< T, IsConst > const & y
)
{
	return ( ! ( x == y ) );
}

template<
	typename T,
	bool IsConst
>
bool
operator<(
	_deque_iterator< T, IsConst > const & x,
	_deque_iterator< T, IsConst > const & y
)
{
	return ( ( x._get_node() == y._get_node() ) ? ( x._get_current() < y._get_current() ) : ( x._get_node() < y._get_node() ) );
}

template<
	typename T,
	bool IsConst
>
bool
operator<=(
	_deque_iterator< T, IsConst > const & x,
	_deque_iterator< T, IsConst > const & y
)
{
	return ( ! ( y < x ) );
}

template<
	typename T,
	bool IsConst
>
bool
operator>(
	_deque_iterator< T, IsConst > const & x,
	_deque_iterator< T, IsConst > const & y
)
{
	return ( y < x );
}

template<
	typename T,
	bool IsConst
>
bool
operator>=(
	_deque_iterator< T, IsConst > const & x,
	_deque_iterator< T, IsConst > const & y
)
{
	return ( ! ( x < y ) );
}

// -- Different constness --------------
template<
	typename T,
	bool IsConst
>
bool
operator==(
	_deque_iterator< T, IsConst > const & x,
	_deque_iterator< T, ! IsConst > const & y
)
{
	return ( x._get_current() == y._get_current() );
}

template<
	typename T,
	bool IsConst
>
bool
operator!=(
	_deque_iterator< T,   IsConst > const & x,
	_deque_iterator< T, ! IsConst > const & y
)
{
	return ( ! ( x == y ) );
}

template<
	typename T,
	bool IsConst
>
bool
operator<(
	_deque_iterator< T,   IsConst > const & x,
	_deque_iterator< T, ! IsConst > const & y
)
{
	return ( ( x._get_node() == y._get_node() ) ? ( x._get_current() < y._get_current() ) : ( x._get_node() < y._get_node() ) );
}

template<
	typename T,
	bool IsConst
>
bool
operator<=(
	_deque_iterator< T,   IsConst > const & x,
	_deque_iterator< T, ! IsConst > const & y
)
{
	return ( ! ( y < x ) );
}

template<
	typename T,
	bool IsConst
>
bool
operator>(
	_deque_iterator< T,   IsConst > const & x,
	_deque_iterator< T, ! IsConst > const & y
)
{
	return ( y < x );
}

template<
	typename T,
	bool IsConst
>
bool
operator>=(
	_deque_iterator< T,   IsConst > const & x,
	_deque_iterator< T, ! IsConst > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * DequeBase
 */
template<
	typename T,
	typename Allocator
>
class _deque_base
{
	// Type --------------------------------------------------------------------
public:
	typedef Allocator  allocator_type;

	typedef size_t     size_type;
	typedef ptrdiff_t  difference_type;

	typedef T                   value_type;
	typedef value_type &        reference;
	typedef value_type const &  const_reference;
	typedef value_type *        pointer;
	typedef value_type const *  const_pointer;

protected:
	typedef value_type **  _map_type;
	typedef value_type *   _node_type;

private:
	typedef typename Allocator::template rebind< _node_type >::other  _map_allocator_type;
	typedef typename Allocator::template rebind< value_type >::other  _node_allocator_type;

	typedef _deque_base< T, Allocator >  _self_type;

	// Attribute ---------------------------------------------------------------
private:
	_map_allocator_type _map_allocator;
	_node_allocator_type _node_allocator;

protected:
	_map_type _map;
	size_type _map_size;

	// Constructor -------------------------------------------------------------
protected:
	explicit
	_deque_base(
		allocator_type const & allocator
	)
		: _map_allocator( allocator )
		, _node_allocator( allocator )
		, _map( nullptr )
		, _map_size( 0 )
	{
	}

	// Destructor --------------------------------------------------------------
public:
	~_deque_base()
	{
		if ( this->_map != nullptr )
		{
			this->_deallocate_map( this->_map, this->_map_size );
		}
	}

	// Method ------------------------------------------------------------------
public:
	allocator_type
	get_allocator() const
	{
		return this->_node_allocator;
	}

protected:
	// - Allocation -------------------
	_map_type
	_allocate_map(
		size_type size
	)
	{
		return this->_map_allocator.allocate( size );
	}

	void
	_deallocate_map(
		_map_type map,
		size_type size
	)
	{
		this->_map_allocator.deallocate( map, size );
	}

	_node_type
	_allocate_node()
	{
		return this->_node_allocator.allocate( _get_node_size< value_type >() );
	}

	void
	_deallocate_node(
		_node_type * node
	)
	{
		this->_node_allocator.deallocate( *node, _get_node_size< value_type >() );
	}

	void
	_construct(
		value_type * ptr,
		value_type const & value
	)
	{
		return this->_node_allocator.construct( ptr, value );
	}

	void
	_destroy(
		value_type * ptr
	)
	{
		this->_node_allocator.destroy( ptr );
	}

}; // class _deque_base

} // namespace

/**
 * Deque
 *
 * @ref https://en.cppreference.com/w/cpp/container/deque
 * @ref https://cplusplus.com/reference/deque/deque/
 */
template<
	typename T,
	typename Allocator
>
class deque
	: public _deque_base< T, Allocator >
{
	// Type --------------------------------------------------------------------
private:
	typedef _deque_base< T, Allocator >  _self_base_type;
	typedef ft::deque< T, Allocator >    _self_type;

	using typename _self_base_type::_map_type;
	using typename _self_base_type::_node_type;

public:
	using typename _self_base_type::allocator_type;

	using typename _self_base_type::size_type;
	using typename _self_base_type::difference_type;

	using typename _self_base_type::value_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::const_reference;
	using typename _self_base_type::pointer;
	using typename _self_base_type::const_pointer;

	typedef _deque_iterator< value_type, false >    iterator;
	typedef _deque_iterator< value_type, true >     const_iterator;
	typedef ft::reverse_iterator< iterator >        reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >  const_reverse_iterator;

	// Property ----------------------------------------------------------------
private:
	iterator _start;
	iterator _finish;

	// Constructor -------------------------------------------------------------
public:
	explicit
	deque(
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
		, _start()
		, _finish()
	{
		this->_create_map();
	}

	explicit
	deque(
		size_type count,
		value_type const & value = value_type(),
		allocator_type const & allocator = Allocator()
	)
		: _self_base_type( allocator )
		, _start()
		, _finish()
	{
		this->_create_map( count );
		this->assign( count, value );
	}

	template<
		typename _InputIterator
	>
	deque(
		_InputIterator first,
		_InputIterator last,
		allocator_type const & allocator = Allocator()
	)
		: _self_base_type( allocator )
		, _start()
		, _finish()
	{
		this->_create_map();
		this->assign( first, last );
	}

	deque(
		_self_type const & other
	)
		: _self_base_type( other.get_allocator() )
		, _start()
		, _finish()
	{
		this->_create_map();
		this->assign( other.begin(), other.end() );
	}

	// Destructor --------------------------------------------------------------
public:
	~deque()
	{
		this->clear();
		_self_base_type::_deallocate_node( this->_start._get_node() );
	}

	// Operator ----------------------------------------------------------------
public:
	// - Assignation ------------------
	_self_type &
	operator=(
		_self_type const & other
	)
	{
		if ( this != &other )
		{
			this->assign( other.begin(), other.end() );
		}

		return *this;
	}

	// - Access -----------------------
	reference       operator[]( size_type index )       { return this->_start[ static_cast< difference_type >( index ) ]; }
	const_reference operator[]( size_type index ) const { return this->_start[ static_cast< difference_type >( index ) ]; }

	// Method ------------------------------------------------------------------
public:
	allocator_type get_allocator() const { return _self_base_type::get_allocator(); }

	// - Iteration --------------------
	iterator               begin()        { return iterator( this->_start ); }
	const_iterator         begin() const  { return const_iterator( this->_start ); }
	iterator               end()          { return iterator( this->_finish ); }
	const_iterator         end() const    { return const_iterator( this->_finish ); }
	reverse_iterator       rbegin()       { return reverse_iterator( this->end() ); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator( this->end() ); }
	reverse_iterator       rend()         { return reverse_iterator( this->begin() ); }
	const_reverse_iterator rend() const   { return const_reverse_iterator( this->begin() ); }

	// - Capacity ---------------------
	size_type     size() const { return ( ( this->empty() ) ? 0 : ( this->end() - this->begin() ) ); }
	size_type max_size() const { return size_type(-1) / sizeof(value_type) / 2; }

	bool empty() const { return ( this->begin() == this->end() ); }

	// - Access -----------------------
	reference       at( size_type index )       { this->_check_range( index ); return ( *this )[ index ]; }
	const_reference at( size_type index ) const { this->_check_range( index ); return ( *this )[ index ]; }

	reference       front()       { return *( this->begin() ); }
	const_reference front() const { return *( this->begin() ); }

	reference       back()       { return *( --this->end() ); }
	const_reference back() const { return *( --this->end() ); }

	// - Modifier ---------------------
	void
	push_front(
		value_type const & value
	)
	{
		if ( this->_start._get_current() != this->_start._get_first() )
		{
			_self_base_type::_construct( this->_start._get_current() - 1, value );

			this->_start._set_current( this->_start._get_current() - 1 );

			return ;
		}

		this->_reserve_at_front( 1 );

		_node_type * node = this->_start._get_node() - 1;
		*node = _self_base_type::_allocate_node();

		try
		{
			this->_start._set_node( node );
			this->_start._set_current( this->_start._get_last() - 1 );

			_self_base_type::_construct( this->_start._get_current(), value );
		}
		catch ( ... )
		{
			++this->_start;

			_self_base_type::_deallocate_node( node );

			throw ;
		}
	}

	void
	push_back(
		value_type const & value
	)
	{
		if ( this->_finish._get_current() != this->_finish._get_last() - 1 )
		{
			_self_base_type::_construct( this->_finish._get_current(), value );

			this->_finish._set_current( this->_finish._get_current() + 1 );

			return ;
		}

		this->_reserve_at_back(1);

		_node_type * node = this->_finish._get_node() + 1;
		*node = _self_base_type::_allocate_node();

		try
		{
			_self_base_type::_construct( this->_finish._get_current(), value );

			this->_finish._set_node( node );
			this->_finish._set_current( this->_finish._get_first() );
		}
		catch ( ... )
		{
			_self_base_type::_deallocate_node( node );

			throw ;
		}
	}

	void
	pop_front()
	{
		_self_base_type::_destroy( this->_start._get_current() );

		if ( this->_start._get_current() != this->_start._get_last() - 1 )
		{
			this->_start._set_current( this->_start._get_current() + 1 );
		}
		else
		{
			_self_base_type::_deallocate_node( this->_start._get_node() );
			this->_start._set_node( this->_start._get_node() + 1 );
			this->_start._set_current( this->_start._get_first() );
		}
	}

	void
	pop_back()
	{
		if ( this->_finish._get_current() != this->_finish._get_first() )
		{
			this->_finish._set_current( this->_finish._get_current() - 1 );
		}
		else
		{
			_self_base_type::_deallocate_node( this->_finish._get_node() );
			this->_finish._set_node( this->_finish._get_node() - 1 );
			this->_finish._set_current( this->_finish._get_last() - 1 );
		}

		_self_base_type::_destroy( this->_finish._get_current() );

	}

	void
	resize(
		size_type size,
		value_type const & value = value_type()
	)
	{
		size_type const current_size = this->size();

		if ( size < current_size )
		{
			this->erase( this->begin() + size, this->end() );
		}
		else
		{
			this->insert( this->end(), size - current_size, value );
		}
	}

	void
	shrink_to_fit()
	{
		// Todo: Implement ? Not supported by some implementation
	}

	void
	clear()
	{
		this->erase( this->begin(), this->end() );
	}

	void
	swap(
		_self_type & other
	)
	{
		ft::swap( this->_map, other._map );
		ft::swap( this->_map_size, other._map_size );
		ft::swap( this->_start, other._start );
		ft::swap( this->_finish, other._finish );
	}

	iterator
	insert(
		iterator position,
		value_type const & value
	)
	{
		if ( position == this->begin() )
		{
			this->push_front( value );
			return this->begin();
		}

		if ( position == this->end() )
		{
			this->push_back( value );
			return ( this->end() - 1 );
		}

		size_type index = position - this->begin();

		if ( index < ( this->size() / 2 ) )
		{
			this->push_front( this->front() );
			position = this->begin() + index;
			ft::copy( this->begin() + 2, position + 1, this->begin() + 1 );
		}
		else
		{
			this->push_back( this->back() );
			position = this->begin() + index;
			ft::copy_backward( position, this->end() - 2, this->end() - 1 );
		}

		*position = value;

		return position;
	}

	void
	insert(
		iterator position,
		size_type count,
		value_type const & value
	)
	{
		// Todo: Optimise
		while ( count-- > 0 )
		{
			position = this->insert( position, value );
			++position;
		}
	}

	template<
		typename _InputIterator
	>
	typename ft::enable_if< ! ft::is_integer< _InputIterator >::value, void >::type
	insert(
		iterator position,
		_InputIterator first,
		_InputIterator last
	)
	{
		// Todo: Optimse for ForwardIterator
		while ( first != last )
		{
			position = this->insert( position, *first );
			++first;
			++position;
		}
	}

	iterator
	erase(
		iterator position
	)
	{
		size_type index = position - this->_start;

		if ( index < ( this->size() / 2 ) )
		{
			ft::copy_backward( this->_start, position, position + 1 );
			this->pop_front();
		}
		else
		{
			ft::copy( position + 1, this->_finish, position );
			this->pop_back();
		}

		return ( this->_start + index );
	}

	iterator
	erase(
		iterator first,
		iterator last
	)
	{
		size_type count = last - first;
		size_type index = first - this->_start;

		if ( index < ( ( this->size() - count ) / 2 ) )
		{
			ft::copy_backward( this->_start, first, last );

			iterator start = this->_start + count;

			for ( iterator it = this->_start ; it != start ; ++it )
			{
				_self_base_type::_destroy( ft::addressof( *it ) );
			}

			this->_destroy_nodes( this->_start._get_node(), start._get_node() );
			this->_start = start;
		}
		else
		{
			ft::copy( last, this->_finish, first );

			iterator finish = this->_finish - count;

			for ( iterator it = finish ; it != this->_finish ; ++it )
			{
				_self_base_type::_destroy( ft::addressof( *it ) );
			}

			this->_destroy_nodes( finish._get_node() + 1, this->_finish._get_node() + 1 );
			this->_finish = finish;
		}

		return ( this->_start + index );
	}

	void
	assign(
		size_type count,
		value_type const & value
	)
	{
		if ( count > this->size() )
		{
			for ( iterator it = this->begin() ; it != this->end() ; ++it )
			{
				*it = value;
			}

			this->insert( this->end(), count - this->size(), value );
		}
		else
		{
			this->erase( this->begin() + count, this->end() );

			for ( iterator it = this->begin() ; it != this->end() ; ++it )
			{
				*it = value;
			}
		}
	}

	template<
		typename _InputIterator
	>
	typename ft::enable_if< ! ft::is_integer< _InputIterator >::value, void >::type
	assign(
		_InputIterator first,
		_InputIterator last
	)
	{
		// Todo: Optimise for ForwardIterator
		iterator current;

		for ( current = this->begin() ; ( current != this->end() && first != last ) ; ++current, ++first )
		{
			*current = *first;
		}

		if ( first == last )
		{
			this->erase( current, this->end() );
		}
		else
		{
			this->insert( current, first, last );
		}
	}

private:
	// - Access -----------------------
	void
	_check_range(
		size_type n
	) const
	{
		if ( n >= this->size() )
		{
			throw ft::out_of_range("deque::_check_range");
		}
	}

	// - Allocation -------------------
	void
	_create_map(
		size_type elements_count = 0
	)
	{
		size_type const required_node_count = ( elements_count / _get_node_size< value_type >() ) + 1;

		this->_map_size = required_node_count + 2;
		this->_map = _self_base_type::_allocate_map( this->_map_size );

		// Get the positions to create nodes in the middle of the map
		// So we have empty space before/after for future front/back push
		_node_type * start = this->_map + ( this->_map_size - required_node_count ) / 2;

		try
		{
			*start = _self_base_type::_allocate_node();
		}
		catch ( ... )
		{
			_self_base_type::_deallocate_node( start );
			_self_base_type::_deallocate_map( this->_map, this->_map_size );

			this->_map = nullptr;
			this->_map_size = 0;

			throw ;
		}

		this->_start._set_node( start );
		this->_start._set_current( this->_start._get_first() );
		this->_finish = this->_start;
	}

	void
	_destroy_nodes(
		_node_type * fst,
		_node_type * lst
	)
	{
		for ( _node_type * node = fst ; node < lst ; ++node )
		{
			_self_base_type::_deallocate_node( node );
		}
	}

	void
	_destroy_values(
		value_type * fst,
		value_type * lst
	)
	{
		for ( value_type * current = fst ; fst < lst ; ++current )
		{
			_self_base_type::_destroy( current );
		}
	}

	void
	_extend_map(
		size_type node_to_add,
		bool at_front
	)
	{
		size_type old_node_count = this->_finish._get_node() - this->_start._get_node() + 1;
		size_type new_node_count = old_node_count + node_to_add;

		_node_type * new_node_start;

		if ( this->_map_size > 2 * new_node_count )
		{
			new_node_start = this->_map + ( this->_map_size - new_node_count ) / 2 + ( ( at_front ) ? node_to_add : 0 );

			if ( new_node_start < this->_start._get_node() )
			{
				ft::copy( this->_start._get_node(), this->_finish._get_node() + 1, new_node_start );
			}
			else
			{
				ft::copy_backward( this->_start._get_node(), this->_finish._get_node() + 1, new_node_start + old_node_count );
			}
		}
		else
		{
			size_type new_map_size = this->_map_size + ft::max( this->_map_size, node_to_add ) + 2;
			_map_type new_map = _self_base_type::_allocate_map( new_map_size );

			new_node_start = new_map + ( new_map_size - new_node_count ) / 2 + ( ( at_front ) ? node_to_add : 0 );
			ft::copy( this->_start._get_node(), this->_finish._get_node() + 1, new_node_start );

			_self_base_type::_deallocate_map( this->_map, this->_map_size );

			this->_map = new_map;
			this->_map_size = new_map_size;
		}

		this->_start._set_node( new_node_start );
		this->_finish._set_node( new_node_start + old_node_count - 1 );
	}

	// - Capacity ---------------------
	void
	_reserve_at_front(
		size_type node_to_add
	)
	{
		if ( node_to_add > static_cast< size_type >( this->_start._get_node() - this->_map ) )
		{
			this->_extend_map( node_to_add, true );
		}
	}

	void
	_reserve_at_back(
		size_type node_to_add
	)
	{
		if ( ( node_to_add + 1 ) > ( this->_map_size - static_cast< size_type >( this->_finish._get_node() - this->_map ) ) )
		{
			this->_extend_map( node_to_add, false );
		}
	}

}; // class deque

// - Relational Operator -------------------------------------------------------
template<
	typename T,
	typename Allocator
>
bool
operator==(
	ft::deque< T, Allocator > const & x,
	ft::deque< T, Allocator > const & y
)
{
	return ( ( x.size() == y.size() ) && ft::equal( x.begin(), x.end(), y.begin(), y.end() ) );
}

template<
	typename T,
	typename Allocator
>
bool
operator!=(
	ft::deque< T, Allocator > const & x,
	ft::deque< T, Allocator > const & y
)
{
	return ( ! ( x == y ) );
}

template<
	typename T,
	typename Allocator
>
bool
operator<(
	ft::deque< T, Allocator > const & x,
	ft::deque< T, Allocator > const & y
)
{
	return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
}

template<
	typename T,
	typename Allocator
>
bool
operator<=(
	ft::deque< T, Allocator > const & x,
	ft::deque< T, Allocator > const & y
)
{
	return ( ! ( y < x ) );
}

template<
	typename T,
	typename Allocator
>
bool
operator>(
	ft::deque< T, Allocator > const & x,
	ft::deque< T, Allocator > const & y
)
{
	return ( y < x );
}

template<
	typename T,
	typename Allocator
>
bool
operator>=(
	ft::deque< T, Allocator > const & x,
	ft::deque< T, Allocator > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * Swap
 *
 * @ref https://cplusplus.com/reference/deque/deque/swap-free/
 * @ref https://en.cppreference.com/w/cpp/container/deque/swap2
 */
template<
	typename T,
	typename Allocator
>
void
swap(
	ft::deque< T, Allocator > & x,
	ft::deque< T, Allocator > & y
)
{
	x.swap(y);
}

} // namespace ft

#endif
