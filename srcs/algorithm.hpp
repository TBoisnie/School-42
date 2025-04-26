#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "iterator.hpp"
#include "functional.hpp"
#include "utility.hpp"

namespace ft
{

/**
 * Equal
 *
 * @ref https://cplusplus.com/reference/algorithm/equal/
 */
template<
	typename InputIterator1,
	typename InputIterator2,
	typename Compare
>
bool
equal(
	InputIterator1 first_1,
	InputIterator1 last_1,
	InputIterator2 first_2,
	InputIterator2 last_2,
	Compare compare
)
{
	for ( ; ( first_1 != last_1 && first_2 != last_2 ) ; ++first_1, ++first_2 )
	{
		if ( ! compare( *first_1, *first_2 ) )
		{
			return false;
		}
	}

	return ( first_1 == last_1 && first_2 == last_2 );
}

template<
	typename InputIterator1,
	typename InputIterator2
>
bool
equal(
	InputIterator1 first_1,
	InputIterator1 last_1,
	InputIterator2 first_2,
	InputIterator2 last_2
)
{
	return ft::equal(
		first_1, last_1, first_2, last_2,
		ft::equal_to<
			typename ft::iterator_traits< InputIterator1 >::value_type,
			typename ft::iterator_traits< InputIterator2 >::value_type
		>()
	);
}

/**
 * Mismatch
 *
 * @ref https://cplusplus.com/reference/algorithm/mismatch
 */
template<
	typename InputIterator1,
	typename InputIterator2,
	typename Compare
>
ft::pair< InputIterator1, InputIterator2 >
mismatch(
	InputIterator1 first_1,
	InputIterator1 last_1,
	InputIterator2 first_2,
	InputIterator2 last_2,
	Compare compare
)
{
	for ( ; ( first_1 != last_1 && first_2 != last_2 ) ; ++first_1, ++first_2 )
	{
		if ( ! compare( *first_1, *first_2 ) )
		{
			break ;
		}
	}

	return ft::make_pair( first_1, first_2 );
}

template<
	typename InputIterator1,
	typename InputIterator2
>
ft::pair< InputIterator1, InputIterator2 >
mismatch(
	InputIterator1 first_1,
	InputIterator1 last_1,
	InputIterator2 first_2,
	InputIterator2 last_2
)
{
	return ft::mismatch(
		first_1, last_1, first_2, last_2,
		ft::equal_to<
			typename ft::iterator_traits< InputIterator1 >::value_type,
			typename ft::iterator_traits< InputIterator2 >::value_type
		>()
	);
}

/**
 * LexicographicalCompare
 *
 * @ref https://cplusplus.com/reference/algorithm/lexicographical_compare/
 * @ref https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
 */
template<
	typename InputIterator1,
	typename InputIterator2,
	typename Compare
>
bool
lexicographical_compare(
	InputIterator1 first_1,
	InputIterator1 last_1,
	InputIterator2 first_2,
	InputIterator2 last_2,
	Compare compare
)
{
	for ( ; ( first_1 != last_1 && first_2 != last_2 ) ; ++first_1, ++first_2 )
	{
		if ( compare( *first_1, *first_2 ) ) return true;
		if ( compare( *first_2, *first_1 ) ) return false;
	}

	return ( first_1 == last_1 && first_2 != last_2 );
}

template<
	typename InputIterator1,
	typename InputIterator2
>
bool
lexicographical_compare(
	InputIterator1 first_1,
	InputIterator1 last_1,
	InputIterator2 first_2,
	InputIterator2 last_2
)
{
	return ft::lexicographical_compare(
		first_1, last_1, first_2, last_2,
		ft::less<
			typename ft::iterator_traits< InputIterator1 >::value_type,
			typename ft::iterator_traits< InputIterator2 >::value_type
		>()
	);
}

/**
 * Find
 *
 * @ref https://cplusplus.com/reference/algorithm/find/
 */
template<
	typename InputIterator,
	typename T,
	typename Compare
>
InputIterator
find(
	InputIterator first,
	InputIterator last,
	T const & value,
	Compare compare
)
{
	while ( first != last )
	{
		if ( compare( *first, value ) )
		{
			return first;
		}

		++first;
	}

	return last;
}

template<
	typename InputIterator,
	typename T
>
InputIterator
find(
	InputIterator first,
	InputIterator last,
	T const & value
)
{
	return ft::find(
		first, last, value,
		ft::equal_to< typename ft::iterator_traits< InputIterator >::value_type, T >()
	);
}

/**
 * Count
 *
 * @ref https://cplusplus.com/reference/algorithm/count/
 */
template<
	typename InputIterator,
	typename T,
	typename Compare
>
typename ft::iterator_traits< InputIterator >::difference_type
count(
	InputIterator first,
	InputIterator last,
	T const & value,
	Compare compare
)
{
	typename ft::iterator_traits< InputIterator >::difference_type count = 0;

	while ( first != last )
	{
		if ( compare( *first, value ) )
		{
			count += 1;
		}

		++first;
	}

	return count;
}

template<
	typename InputIterator,
	typename T
>
typename ft::iterator_traits< InputIterator >::difference_type
count(
	InputIterator first,
	InputIterator last,
	T const & value
)
{
	return ft::count(
		first, last, value,
		ft::equal_to< typename ft::iterator_traits< InputIterator >::value_type, T >()
	);
}

/**
 * IsPermutation
 */
template<
	typename InputIterator1,
	typename InputIterator2,
	typename Compare
>
bool
is_permutation(
	InputIterator1 first_1,
	InputIterator1 last_1,
	InputIterator2 first_2,
	InputIterator2 last_2,
	Compare compare
)
{
	ft::pair< InputIterator1, InputIterator2 > miss = ft::mismatch( first_1, last_1, first_2, last_2, compare );

	first_1 = miss.first;
	first_2 = miss.second;

	if ( first_1 == last_1 )
	{
		return true;
	}

	for ( InputIterator1 it = first_1 ; it != last_1 ; ++it )
	{
		if ( ft::find( first_1, it, *it, compare ) == it )
		{
			typename ft::iterator_traits< InputIterator2 >::difference_type count = ft::count( first_2, last_2, *it, compare );

			if ( count == 0 || ft::count( it, last_1, *it, compare ) != count )
			{
				return false;
			}
		}
	}

	return true;
}

template<
	typename InputIterator1,
	typename InputIterator2
>
bool
is_permutation(
	InputIterator1 first_1,
	InputIterator1 last_1,
	InputIterator2 first_2,
	InputIterator2 last_2
)
{
	return ft::is_permutation(
		first_1, last_1, first_2, last_2,
		ft::equal_to<
			typename ft::iterator_traits< InputIterator1 >::value_type,
			typename ft::iterator_traits< InputIterator2 >::value_type
		>()
	);
}

/**
 * Copy
 *
 * @ref https://cplusplus.com/reference/algorithm/copy/
 * @ref https://en.cppreference.com/w/cpp/algorithm/copy
 */
template<
	typename InputIterator,
	typename OutputIterator
>
OutputIterator
copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result
)
{
	while ( first != last )
	{
		*result++ = *first++;
	}

	return result;
}

/**
 * CopyBackward
 *
 * @ref https://cplusplus.com/reference/algorithm/copy_backward/
 * @ref https://en.cppreference.com/w/cpp/algorithm/copy_backward
 */
template<
	typename BidirectionalIterator1,
	typename BidirectionalIterator2
>
BidirectionalIterator2
copy_backward(
	BidirectionalIterator1 first,
	BidirectionalIterator1 last,
	BidirectionalIterator2 result
)
{
	while ( last != first )
	{
		*--result = *--last;
	}

	return result;
}

/**
 * Swap
 *
 * @ref https://cplusplus.com/reference/algorithm/swap/
 * @ref https://en.cppreference.com/w/cpp/algorithm/swap
 */
template<
	typename T
>
void
swap(
	T & x,
	T & y
)
{
	T tmp(x);

	x = y;
	y = tmp;
}

/**
 * Min
 *
 * @ref https://cplusplus.com/reference/algorithm/min/
 * @ref https://en.cppreference.com/w/cpp/algorithm/min
 */
template<
	typename T,
	typename Compare
>
T const &
min(
	T const & x,
	T const & y,
	Compare compare
)
{
	return ( ( compare( x, y ) ) ? y : x );
}

template<
	typename T
>
T const &
min(
	T const & x,
	T const & y
)
{
	return ft::min( x, y, ft::greater< T >() );
}

/**
 * Max
 *
 * @ref https://cplusplus.com/reference/algorithm/max/
 * @ref https://en.cppreference.com/w/cpp/algorithm/max
 */
template<
	typename T,
	typename Compare
>
T const &
max(
	T const & x,
	T const & y,
	Compare compare
)
{
	return ( ( compare( x, y ) ) ? y : x );
}

template<
	typename T
>
T const &
max(
	T const & x,
	T const & y
)
{
	return ft::max( x, y, ft::less< T >() );
}

/**
 * PushHeap
 *
 * @ref https://cplusplus.com/reference/algorithm/push_heap/
 * @ref https://en.cppreference.com/w/cpp/algorithm/push_heap
 */
namespace
{

template<
	typename RandomAccessIterator,
	typename Distance,
	typename T,
	typename Compare
>
void
_push_heap(
	RandomAccessIterator first,
	Distance hole,
	Distance top,
	T value,
	Compare & compare
)
{
	Distance parent = ( hole - 1 ) / 2;

	while ( hole > top && compare( *( first + parent ), value ) )
	{
		*( first + hole ) = *( first + parent );
		hole = parent;
		parent = ( hole - 1 ) / 2;
	}

	*( first + hole ) = value;
}

} // namespace

template<
	typename RandomAccessIterator,
	typename Compare
>
void
push_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare compare
)
{
	typedef typename ft::iterator_traits< RandomAccessIterator >::difference_type  distance_type;

	_push_heap( first, last - first - 1, static_cast< distance_type >( 0 ), *( last - 1 ), compare );
}

template<
	typename RandomAccessIterator
>
void
push_heap(
	RandomAccessIterator first,
	RandomAccessIterator last
)
{
	ft::push_heap( first, last, ft::less< typename ft::iterator_traits< RandomAccessIterator >::value_type >() );
}

/**
 * AdjustHeap
 */
namespace
{

template<
	typename RandomAccessIterator,
	typename Distance,
	typename T,
	typename Compare
>
void
_adjust_heap(
	RandomAccessIterator first,
	Distance hole,
	Distance length,
	T value,
	Compare compare
)
{
	Distance top = hole;
	Distance next = 2 * hole + 2;

	while ( next < length )
	{
		if ( compare( *( first + next ), *( first + ( next - 1 ) ) ) )
		{
			next--;
		}

		*( first + hole ) = *( first + next );
		hole = next;
		next = 2 * ( next + 1 );
	}

	if ( next == length )
	{
		*( first + hole ) = *( first + ( next - 1 ) );
		hole = next - 1;
	}

	_push_heap( first, hole, top, value, compare );
}

} // namespace

/**
 * PopHeap
 *
 * @ref https://cplusplus.com/reference/algorithm/pop_heap/
 * @ref https://en.cppreference.com/w/cpp/algorithm/pop_heap
 */
namespace
{

template<
	typename RandomAccessIterator,
	typename T,
	typename Compare
>
void
_pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	RandomAccessIterator result,
	T value,
	Compare & compare
)
{
	typedef typename ft::iterator_traits< RandomAccessIterator >::difference_type  distance_type;

	*result = *first;

	_adjust_heap( first, static_cast< distance_type >( 0 ), last - first, value, compare );
}

} // namespace

template<
	typename RandomAccessIterator,
	typename Compare
>
void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare & compare
)
{
	_pop_heap( first, last - 1, last - 1, *( last - 1 ), compare );
}

template<
	typename RandomAccessIterator
>
void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last
)
{
	ft::pop_heap( first, last, ft::less< typename ft::iterator_traits< RandomAccessIterator >::value_type >() );
}

/**
 * SortHeap
 *
 * @ref https://cplusplus.com/reference/algorithm/sort_heap/
 * @ref https://en.cppreference.com/w/cpp/algorithm/sort_heap
 */
template<
	typename RandomAccessIterator,
	typename Compare
>
void
sort_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare & compare
)
{
	while ( last - first > 1 )
	{
		ft::pop_heap( first, last--, compare );
	}
}

template<
	typename RandomAccessIterator,
	typename Compare
>
void
sort_heap(
	RandomAccessIterator first,
	RandomAccessIterator last
)
{
	ft::sort_heap( first, last, ft::less< typename ft::iterator_traits< RandomAccessIterator >::value_type >() );
}

/**
 * MakeHeap
 *
 * @ref https://cplusplus.com/reference/algorithm/make_heap/
 * @ref https://en.cppreference.com/w/cpp/algorithm/make_heap
 */
template<
	typename RandomAccessIterator,
	typename Compare
>
void
make_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare & compare
)
{
	typedef typename ft::iterator_traits< RandomAccessIterator >::difference_type  distance_type;

	if ( last - first < 2 )
	{
		return ;
	}

	distance_type length = last - first;
	distance_type parent = ( length - 2 ) / 2;

	while ( true )
	{
		_adjust_heap( first, parent, length, *( first + parent ), compare );

		if ( parent == 0 )
		{
			return;
		}

		--parent;
	}
}

template<
	typename RandomAccessIterator
>
void
make_heap(
	RandomAccessIterator first,
	RandomAccessIterator last
)
{
	ft::make_heap( first, last, ft::less< typename ft::iterator_traits< RandomAccessIterator >::value_type >() );
}

} // namespace ft

#endif
