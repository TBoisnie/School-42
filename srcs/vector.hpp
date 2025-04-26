#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef> // size_t, ptrdiff_t
#include <memory> // std::allocator

#include "algorithm.hpp"
#include "memory.hpp"
#include "stdexcept.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{

namespace
{

/**
 * VectorIterator
 */
template<
	typename T,
	bool IsConst
>
class _vector_iterator
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
	>                                       _self_base_type;
	typedef _vector_iterator< T, IsConst >  _self_type;

public:
	using typename _self_base_type::difference_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::pointer;

	// Attribute ---------------------------------------------------------------
protected:
	pointer _ptr;

	// Constructor -------------------------------------------------------------
public:
	explicit
	_vector_iterator(
		pointer ptr = nullptr
	)
		: _ptr( ptr )
	{
	}

	// Note: Allow convertion from non-const to const iterator
	template<
		typename _T
	>
	_vector_iterator(
		_vector_iterator< _T, false > const & other
	)
		: _ptr( ft::addressof( *other ))
	{
	}

	_vector_iterator(
		_self_type const & other
	)
		: _ptr( other._get_ptr() )
	{
	}

	// Operator ----------------------------------------------------------------
public:
	// - Access -----------------------
	reference
	operator*() const
	{
		return ( *( this->_ptr ) );
	}

	pointer
	operator->() const
	{
		return this->_ptr;
	}

	reference
	operator[](
		difference_type const & index
	) const
	{
		return this->_ptr[ index ];
	}

	// - Iterate ----------------------
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
		_self_type other = *this;
		other._increment( amount );
		return other;
	}

	_self_type &
	operator+=(
		difference_type const & amount
	)
	{
		this->_increment( amount );
		return *this;
	}

	_self_type
	operator-(
		difference_type const & amount
	) const
	{
		_self_type other = *this;
		other._decrement( amount );
		return other;
	}

	_self_type &
	operator-=(
		difference_type const & amount
	)
	{
		this->_decrement( amount );
		return *this;
	}

	// - Arithmetic -------------------
	difference_type
	operator-(
		_self_type const & other
	) const
	{
		return ( this->_ptr - other._ptr );
	}

	// Method ------------------------------------------------------------------
private:
	// - Access ------------------------
	pointer
	_get_ptr() const
	{
		return this->_ptr;
	}

	// - Iterate -----------------------
	void
	_increment(
		difference_type const & amount = 1
	)
	{
		this->_ptr += amount;
	}

	void
	_decrement(
		difference_type const & amount = 1
	)
	{
		this->_ptr -= amount;
	}

	// Friend ------------------------------------------------------------------
public:
	// - Relational Operator -----------
	// -- Same Constness ---------------
	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_vector_iterator< _T, _IsConst > const & x,
		_vector_iterator< _T, _IsConst > const & y
	);

	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator<(
		_vector_iterator< _T, _IsConst > const & x,
		_vector_iterator< _T, _IsConst > const & y
	);

	// -- Different Constness ----------
	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_vector_iterator< _T,   _IsConst > const & x,
		_vector_iterator< _T, ! _IsConst > const & y
	);

	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator<(
		_vector_iterator< _T,   _IsConst > const & x,
		_vector_iterator< _T, ! _IsConst > const & y
	);

}; // class _vector_iterator

// - Arithmetic Operator -------------------------------------------------------
template<
	typename T,
	bool IsConst
>
_vector_iterator< T, IsConst >
operator+(
	typename _vector_iterator< T, IsConst >::difference_type amount,
	_vector_iterator< T, IsConst > const & it
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
	_vector_iterator< T, IsConst > const & x,
	_vector_iterator< T, IsConst > const & y
)
{
	return ( x._get_ptr() == y._get_ptr() );
}

template<
	typename T,
	bool IsConst
>
bool
operator!=(
	_vector_iterator< T, IsConst > const & x,
	_vector_iterator< T, IsConst > const & y
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
	_vector_iterator< T, IsConst > const & x,
	_vector_iterator< T, IsConst > const & y
)
{
	return ( x._get_ptr() < y._get_ptr() );
}

template<
	typename T,
	bool IsConst
>
bool
operator<=(
	_vector_iterator< T, IsConst > const & x,
	_vector_iterator< T, IsConst > const & y
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
	_vector_iterator< T, IsConst > const & x,
	_vector_iterator< T, IsConst > const & y
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
	_vector_iterator< T, IsConst > const & x,
	_vector_iterator< T, IsConst > const & y
)
{
	return ( ! ( x < y ) );
}

// -- Diffeerent Constness -------------
template<
	typename T,
	bool IsConst
>
bool
operator==(
	_vector_iterator< T,   IsConst > const & x,
	_vector_iterator< T, ! IsConst > const & y
)
{
	return ( x._get_ptr() == y._get_ptr() );
}

template<
	typename T,
	bool IsConst
>
bool
operator!=(
	_vector_iterator< T,   IsConst > const & x,
	_vector_iterator< T, ! IsConst > const & y
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
	_vector_iterator< T,   IsConst > const & x,
	_vector_iterator< T, ! IsConst > const & y
)
{
	return ( x._get_ptr() < y._get_ptr() );
}

template<
	typename T,
	bool IsConst
>
bool
operator<=(
	_vector_iterator< T,   IsConst > const & x,
	_vector_iterator< T, ! IsConst > const & y
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
	_vector_iterator< T,   IsConst > const & x,
	_vector_iterator< T, ! IsConst > const & y
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
	_vector_iterator< T,   IsConst > const & x,
	_vector_iterator< T, ! IsConst > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * VectorBase
 */
template<
	typename T,
	typename Allocator
>
class _vector_base
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

private:
	typedef _vector_base< T, Allocator >  _self_type;

	// Attribute ---------------------------------------------------------------
private:
	allocator_type _allocator;

protected:
	value_type * _start;
	value_type * _current;
	value_type * _finish;

	// Constructor -------------------------------------------------------------
protected:
	_vector_base(
		allocator_type const & allocator
	)
		: _allocator( allocator )
		, _start( nullptr )
		, _current( nullptr )
		, _finish( nullptr )
	{
	}

	// Destructor --------------------------------------------------------------
public:
	~_vector_base()
	{
		if ( this->_start != nullptr )
		{
			this->_deallocate( this->_start, ( this->_finish - this->_start ));
		}
	}

	// Method ------------------------------------------------------------------
public:
	allocator_type
	get_allocator() const
	{
		return this->_allocator;
	}

protected:
	value_type *
	_allocate(
		size_type size
	)
	{
		return this->_allocator.allocate( size );
	}

	void
	_deallocate(
		value_type * ptr,
		size_type size
	)
	{
		this->_allocator.deallocate( ptr, size );
	}

	void
	_construct(
		value_type * ptr,
		value_type const & value
	)
	{
		this->_allocator.construct( ptr, value );
	}

	void
	_destroy(
		value_type * ptr
	)
	{
		this->_allocator.destroy( ptr );
	}

}; // class _vector_base

} // namespace

/**
 * Vector
 *
 * @ref https://en.cppreference.com/w/cpp/container/vector
 * @ref https://cplusplus.com/reference/vector/vector/
 */
template<
	typename T,
	typename Allocator = std::allocator< T >
>
class vector
	: public _vector_base< T, Allocator >
{
	// Type --------------------------------------------------------------------
private:
	typedef _vector_base< T, Allocator >  _self_base_type;
	typedef ft::vector< T, Allocator >    _self_type;

public:
	using typename _self_base_type::allocator_type;

	using typename _self_base_type::size_type;
	using typename _self_base_type::difference_type;

	using typename _self_base_type::value_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::const_reference;
	using typename _self_base_type::pointer;
	using typename _self_base_type::const_pointer;

	typedef _vector_iterator< value_type, false >   iterator;
	typedef _vector_iterator< value_type, true >    const_iterator;
	typedef ft::reverse_iterator< iterator >        reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >  const_reverse_iterator;

	// Constructor -------------------------------------------------------------
public:
	explicit
	vector(
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
	{
	}

	explicit
	vector(
		size_type count,
		value_type const & value = value_type(),
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
	{
		this->assign( count, value );
	}

	template <
		typename _InputIterator
	>
	vector(
		_InputIterator first,
		_InputIterator last,
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
	{
		this->assign( first, last );
	}

	vector(
		_self_type const & other
	)
		: _self_base_type( other.get_allocator() )
	{
		this->assign( other.begin(), other.end() );
	}

	// Destructor --------------------------------------------------------------
public:
	~vector()
	{
		this->clear();
	}

	// Operator ----------------------------------------------------------------
public:
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

	reference       operator[]( size_type n )       { return ( *( this->_start + n ) ); }
	const_reference operator[]( size_type n ) const { return ( *( this->_start + n ) ); }

	// Method ------------------------------------------------------------------
public:
	// - Iterator -----------------------
	iterator               begin()        { return iterator( this->_start ); }
	const_iterator         begin() const  { return const_iterator( this->_start ); }
	iterator               end()          { return iterator( this->_current ); }
	const_iterator         end() const    { return const_iterator( this->_current ); }
	reverse_iterator       rbegin()       { return reverse_iterator( this->end() ); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator( this->end() ); }
	reverse_iterator       rend()         { return reverse_iterator( this->begin() ); }
	const_reverse_iterator rend() const   { return const_reverse_iterator( this->begin() ); }

	// - Access ------------------------
	reference       at( size_type n )       { this->_check_range( n ); return ( *this )[n]; }
	const_reference at( size_type n ) const { this->_check_range( n ); return ( *this )[n]; }

	reference       front()       { return ( *( this->begin() ) ); }
	const_reference front() const { return ( *( this->begin() ) ); }
	reference       back()        { return ( *( --this->end() ) ); }
	const_reference back() const  { return ( *( --this->end() ) ); }
	pointer         data()        { return this->_start; }
	const_pointer   data() const  { return this->_start; }

	// - Capacity ----------------------
	size_type capacity() const { return ( this->_finish - this->_start ); }
	size_type size() const     { return ( this->_current - this->_start ); }
	size_type max_size() const { return ( size_type( -1 ) / sizeof( value_type ) / 2 ); }
	bool      empty() const    { return ( this->_start == this->_current ); }

	// Modifier -------------------------
	void
	reserve(
		size_type capacity
	)
	{
		if ( this->capacity() >= capacity )
		{
			return ;
		}

		this->_reallocate( this->_next_capacity( capacity ));
	}

	void
	resize(
		size_type size,
		value_type const & value = value_type()
	)
	{
		if ( this->size() < size )
		{
			this->insert( this->end(), size - this->size(), value );
			return ;
		}

		if ( this->size() > size )
		{
			this->erase( this->begin() + size, this->end() );
			return ;
		}
	}

	void
	shrink_to_fit()
	{
		this->_reallocate( this->size() );
	}

	void
	swap(
		_self_type & other
	)
	{
		ft::swap( this->_start, other._start );
		ft::swap( this->_current, other._current );
		ft::swap( this->_finish, other._finish );
	}

	void
	push_back(
		const_reference value
	)
	{
		this->insert( this->end(), 1, value );
	}

	void
	pop_back()
	{
		this->erase( --this->end() );
	}

	void
	clear()
	{
		this->erase( this->begin(), this->end() );
	}

	iterator
	insert(
		iterator position,
		const_reference value
	)
	{
		difference_type offset = ft::distance( this->begin(), position );

		this->insert( position, 1, value );

		return ( this->begin() + offset );
	}

	void
	insert(
		iterator position,
		size_type count,
		const_reference value
	)
	{
		if ( count == 0 )
		{
			return ;
		}

		size_type const free = ft::distance( this->end(), iterator( this->_finish ));

		// Enough space ( no reallocation )
		if ( count <= free )
		{
			size_type tailing = ft::distance( position, this->end() );
			const_iterator last = this->end();
			value_type * current = this->_current + count;

			try
			{
				if ( tailing > count )
				{
					const_iterator first = last - count;

					while ( last != first )
					{
						_self_base_type::_construct( --current, *--last );
					}
				}
				else
				{
					const_iterator first = last - tailing;

					while ( last != first )
					{
						_self_base_type::_construct( --current, *--last );
					}

					while ( current != this->_current )
					{
						_self_base_type::_construct( --current, value );
					}
				}
			}
			catch ( ... )
			{
				while ( current != this->_current + count )
				{
					_self_base_type::_destroy( current++ );
				}

				throw ;
			}

			this->_current += count;

			while ( last != position )
			{
				*--current = *--last;
			}

			while ( current != this->_current - tailing - count )
			{
				*--current = value;
			}

			return ;
		}

		// Not enough space ( reallation )
		size_type const capacity = this->_next_capacity( this->size() + count );
		value_type * const start = _self_base_type::_allocate( capacity );
		value_type * current = start;

		try
		{
			const_iterator it = this->begin();

			while ( it != position )
			{
				_self_base_type::_construct( current++, *it++ );
			}

			while ( count-- > 0 )
			{
				_self_base_type::_construct( current++, value );
			}

			while ( it != this->end() )
			{
				_self_base_type::_construct( current++, *it++ );
			}
		}
		catch ( ... )
		{
			while ( current != start )
			{
				_self_base_type::_destroy( --current );
			}

			_self_base_type::_deallocate( start, capacity );

			throw ;
		}

		while ( this->_current != this->_start )
		{
			_self_base_type::_destroy( --this->_current );
		}

		_self_base_type::_deallocate( this->_start, this->capacity() );

		this->_start = start;
		this->_current = current;
		this->_finish = start + capacity;
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
		// Todo: Optimise for ForwardIterator ( reserve ft::distance( first, last ) and insert directly )
		for ( ; first != last ; ++first, ++position )
		{
			position = this->insert( position, *first );
  		}
	}

	iterator
	erase(
		iterator pos
	)
	{
		if ( pos == this->end() )
		{
			return pos;
		}

		return this->erase( pos, pos + 1 );
	}

	iterator
	erase(
		iterator first,
		iterator last
	)
	{
		iterator current = first;

		while ( last != this->end() )
		{
			*current++ = *last++;
		}

		this->_current = ft::addressof( *current );

		while ( current != this->end() )
		{
			_self_base_type::_destroy( ft::addressof( *current++ ));
		}

		return first;
	}

	void
	assign(
		size_type count,
		const_reference value
	)
	{
		if ( count > this->capacity() )
		{
			size_type capacity = this->_next_capacity( count );
			pointer start = _self_base_type::_allocate( capacity );
			pointer current = start;

			try
			{
				while ( count-- > 0 )
				{
					_self_base_type::_construct( current++, value );
				}
			}
			catch ( ... )
			{
				while ( current != start )
				{
					_self_base_type::_destroy( --current );
				}

				_self_base_type::_deallocate( start, capacity );

				throw ;
			}

			this->clear();
			_self_base_type::_deallocate( this->_start, this->capacity() );

			this->_start = start;
			this->_current = current;
			this->_finish = start + capacity;

			return ;
		}

		iterator current = this->begin();

		while ( current != this->end() && count > 0 )
		{
			*current++ = value;
			--count;
		}

		if ( count == 0 )
		{
			this->erase( current, this->end() );
		}
		else
		{
			this->insert( current, count, value );
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
		iterator current = this->begin();

		while ( first != last && current != this->end() )
		{
			*current++ = *first;
			++first;
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
	size_type
	_next_capacity(
		size_type capacity
	) const
	{
		return ft::max( this->capacity() * 2, capacity );
	}

	void
	_check_range(
		size_type index
	) const
	{
		if ( index >= this->size() )
		{
			throw ft::out_of_range( "vector::_check_range" );
		}
	}

	void
	_reallocate(
		size_type capacity
	)
	{
		pointer start = _self_base_type::_allocate( capacity );
		pointer current = start;

		try
		{
			for ( const_iterator it = this->begin() ; it != this->end() ; ++it )
			{
				_self_base_type::_construct( current++, *it );
			}
		}
		catch ( ... )
		{
			while ( current != start )
			{
				_self_base_type::_destroy( --current );
			}

			_self_base_type::_deallocate( start, capacity );

			throw ;
		}

		this->clear();
		_self_base_type::_deallocate( this->_start, this->capacity() );

		this->_start = start;
		this->_current = current;
		this->_finish = start + capacity;
	}

}; // class vector

// - Relational Operator -------------------------------------------------------
template<
	typename T,
	typename Allocator
>
bool
operator==(
	ft::vector< T, Allocator > const & x,
	ft::vector< T, Allocator > const & y
)
{
	return ( x.size() == y.size() && ft::equal( x.begin(), x.end(), y.begin(), y.end() ) );
}

template<
	typename T,
	typename Allocator >
bool
operator!=(
	ft::vector< T, Allocator > const & x,
	ft::vector< T, Allocator > const & y
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
	ft::vector< T, Allocator > const & x,
	ft::vector< T, Allocator > const & y
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
	ft::vector< T, Allocator > const & x,
	ft::vector< T, Allocator > const & y
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
	ft::vector< T, Allocator > const & x,
	ft::vector< T, Allocator > const & y
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
	ft::vector< T, Allocator > const & x,
	ft::vector< T, Allocator > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * Swap
 *
 * @ref https://cplusplus.com/reference/vector/vector/swap-free/
 * @ref https://en.cppreference.com/w/cpp/container/vector/swap2
 */
template<
	typename T,
	typename Allocator
>
void
swap(
	ft::vector< T, Allocator > & x,
	ft::vector< T, Allocator > & y
)
{
	x.swap( y );
}

} // namespace ft

#endif
