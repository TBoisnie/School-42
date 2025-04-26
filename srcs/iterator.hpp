#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef> // ptrdiff_t
#include <iterator> // std::*_iterator_tag
#include "memory.hpp"

namespace ft
{

/**
 * IteratorTag
 *
 * @note Requested by subject to use `*_iterator_tag` as `typedef` of the `std` ones
 *
 * @ref https://en.cppreference.com/w/cpp/iterator/iterator_tags
 * @ref https://cplusplus.com/reference/iterator/
 */
typedef std::input_iterator_tag          input_iterator_tag;
typedef std::output_iterator_tag         output_iterator_tag;
typedef std::forward_iterator_tag        forward_iterator_tag;
typedef std::bidirectional_iterator_tag  bidirectional_iterator_tag;
typedef std::random_access_iterator_tag  random_access_iterator_tag;

/**
 * IteratorTraits
 *
 * @ref https://en.cppreference.com/w/cpp/iterator/iterator_traits
 * @ref https://cplusplus.com/reference/iterator/iterator_traits/
 */
template<
	typename Iterator
>
struct iterator_traits
{
	typedef typename Iterator::iterator_category  iterator_category;
	typedef typename Iterator::difference_type    difference_type;
	typedef typename Iterator::value_type         value_type;
	typedef typename Iterator::reference          reference;
	typedef typename Iterator::pointer            pointer;
};

// - Specialization ( pointer )
template<
	typename T
>
struct iterator_traits< T * >
{
	typedef ft::random_access_iterator_tag  iterator_category;
	typedef ptrdiff_t                       difference_type;
	typedef T                               value_type;
	typedef T &                             reference;
	typedef T *                             pointer;
};

// - Specialization ( pointer const )
template<
	typename T
>
struct iterator_traits< T const * >
{
	typedef ft::random_access_iterator_tag  iterator_category;
	typedef ptrdiff_t                       difference_type;
	typedef T                               value_type;
	typedef T const &                       reference;
	typedef T const *                       pointer;
};

/**
 * Iterator
 *
 * @ref https://en.cppreference.com/w/cpp/iterator/iterator
 * @ref https://cplusplus.com/reference/iterator/iterator/
 */
template<
	typename Category,
	typename T,
	typename Distance = ptrdiff_t,
	typename Pointer = T *,
	typename Reference = T &
>
struct iterator
{
	// Type --------------------------------------------------------------------
	typedef Category   iterator_category;
	typedef Distance   difference_type;

	typedef T          value_type;
	typedef Reference  reference;
	typedef Pointer    pointer;
};

/**
 * ReverseIterator
 *
 * @ref https://en.cppreference.com/w/cpp/iterator/reverse_iterator
 * @ref https://cplusplus.com/reference/iterator/reverse_iterator/
 */
template<
	typename Iterator
>
class reverse_iterator
	: public ft::iterator<
		typename ft::iterator_traits< Iterator >::iterator_category,
		typename ft::iterator_traits< Iterator >::value_type,
		typename ft::iterator_traits< Iterator >::difference_type,
		typename ft::iterator_traits< Iterator >::pointer,
		typename ft::iterator_traits< Iterator >::reference
	>
{
	// Type --------------------------------------------------------------------
private:
	typedef ft::iterator<
		typename ft::iterator_traits< Iterator >::iterator_category,
		typename ft::iterator_traits< Iterator >::value_type,
		typename ft::iterator_traits< Iterator >::difference_type,
		typename ft::iterator_traits< Iterator >::pointer,
		typename ft::iterator_traits< Iterator >::reference
	>  _self_base_type;

	typedef ft::reverse_iterator< Iterator >  _self_type;

public:
	typedef Iterator  iterator_type;

	using typename _self_base_type::difference_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::pointer;

	// Attribute ---------------------------------------------------------------
private:
	iterator_type _iterator;

	// Constructor -------------------------------------------------------------
public:
	reverse_iterator()
	{
	}

	explicit
	reverse_iterator(
		iterator_type it
	)
		: _iterator( it )
	{
	}

	template<
		typename _Iterator
	>
	reverse_iterator(
		ft::reverse_iterator< _Iterator > const & other
	)
		: _iterator( other.base() )
	{
	}

	// Operator ----------------------------------------------------------------
public:
	// - Access -----------------------
	reference
	operator*() const
	{
		iterator_type tmp = this->_iterator;
		return ( *( --tmp ) );
	}

	pointer
	operator->() const
	{
		return ft::addressof( this->operator*() );
	}

	reference
	operator[](
		difference_type index
	) const
	{
		return ( *( *this + index ) );
	}

	// - Iterate ----------------------
	_self_type &
	operator++()
	{
		--this->_iterator;
		return *this;
	}

	_self_type
	operator++( int )
	{
		return _self_type( this->_iterator-- );
	}

	_self_type &
	operator--()
	{
		++this->_iterator;
		return *this;
	}

	_self_type
	operator--( int )
	{
		return _self_type( this->_iterator++ );
	}

	_self_type
	operator+(
		difference_type amount
	) const
	{
		return _self_type( this->_iterator - amount );
	}

	_self_type &
	operator+=(
		difference_type amount
	)
	{
		this->_iterator -= amount;
		return *this;
	}

	_self_type
	operator-(
		difference_type amount
	) const
	{
		return _self_type( this->_iterator + amount );
	}

	_self_type &
	operator-=(
		difference_type amount
	)
	{
		this->_iterator += amount;
		return *this;
	}

	// - Arithmetic -------------------
	difference_type
	operator-(
		_self_type const & other
	) const
	{
		return ( this->_iterator - other._iterator );
	}

	// Method ------------------------------------------------------------------
public:
	iterator_type const &
	base() const
	{
		return this->_iterator;
	}

}; // class reverse_iterator

// - Arithmetic Operator -------------------------------------------------------
template<
	typename Iterator
>
ft::reverse_iterator< Iterator >
operator+(
	typename ft::reverse_iterator< Iterator >::difference_type amount,
	ft::reverse_iterator< Iterator > const & rit
)
{
	return ft::reverse_iterator< Iterator >( rit.base() - amount );
}

// - Relational Operator -------------------------------------------------------
template<
	typename Iterator
>
bool
operator==(
	ft::reverse_iterator< Iterator > const & lhs,
	ft::reverse_iterator< Iterator > const & rhs
)
{
	return ( lhs.base() == rhs.base() );
}

template<
	typename Iterator
>
bool
operator!=(
	ft::reverse_iterator< Iterator > const & lhs,
	ft::reverse_iterator< Iterator > const & rhs
)
{
	return ( ! ( lhs == rhs ) );
}

template<
	typename Iterator
>
bool
operator<(
	ft::reverse_iterator< Iterator > const & lhs,
	ft::reverse_iterator< Iterator > const & rhs
)
{
	return ( lhs.base() < rhs.base() );
}

template<
	typename Iterator
>
bool
operator<=(
	ft::reverse_iterator< Iterator > const & lhs,
	ft::reverse_iterator< Iterator > const & rhs
)
{
	return ( ! ( rhs < lhs ) );
}

template<
	typename Iterator
>
bool
operator>(
	ft::reverse_iterator< Iterator > const & lhs,
	ft::reverse_iterator< Iterator > const & rhs
)
{
	return ( rhs < lhs );
}

template<
	typename Iterator
>
bool
operator>=(
	ft::reverse_iterator< Iterator > const & lhs,
	ft::reverse_iterator< Iterator > const & rhs
)
{
	return ( ! ( lhs < rhs ) );
}

/**
 * Advance
 *
 * @ref https://en.cppreference.com/w/cpp/iterator/advance
 * @ref https://cplusplus.com/reference/iterator/advance/
 */
namespace
{

template<
	typename InputIterator,
	typename Distance
>
void
_advance(
	InputIterator & it,
	Distance n,
	ft::input_iterator_tag
)
{
	while ( n-- > 0 )
	{
		++it;
	}
}

template<
	typename BidirectionalIterator,
	typename Distance
>
void
_advance(
	BidirectionalIterator & it,
	Distance n,
	ft::bidirectional_iterator_tag
)
{
	if ( n > 0 )
	{
		while ( n-- > 0 )
		{
			++it;
		}
	}
	else
	{
		while ( n++ < 0 )
		{
			--it;
		}
	}
}

template<
	typename RandomAccessIterator,
	typename Distance
>
void
_advance(
	RandomAccessIterator & it,
	Distance n,
	ft::random_access_iterator_tag
)
{
	it += n;
}

} // namespace

template<
	typename InputIterator,
	typename Distance
>
void
advance(
	InputIterator & it,
	Distance n
)
{
	typename ft::iterator_traits< InputIterator >::iterator_category category;

	_advance( it, n, category );
}

/**
 * Distance
 *
 * @ref https://en.cppreference.com/w/cpp/iterator/distance
 * @ref https://cplusplus.com/reference/iterator/distance/
 */
namespace
{

template<
	typename InputIterator
>
typename ft::iterator_traits< InputIterator >::difference_type
_distance(
	InputIterator first,
	InputIterator last,
	ft::input_iterator_tag
)
{
	typename ft::iterator_traits< InputIterator >::difference_type n = 0;

	while ( first++ != last )
	{
		++n;
	}

	return n;
}

template<
	typename RandomAccessIterator
>
typename ft::iterator_traits< RandomAccessIterator >::difference_type
_distance(
	RandomAccessIterator first,
	RandomAccessIterator last,
	ft::random_access_iterator_tag
)
{
	return ( last - first );
}

} // namespace

template<
	typename InputIterator
>
typename ft::iterator_traits< InputIterator >::difference_type
distance(
	InputIterator first,
	InputIterator last
)
{
	typename ft::iterator_traits< InputIterator >::iterator_category category;

	return _distance( first, last, category );
}

} // namespace ft

#endif
