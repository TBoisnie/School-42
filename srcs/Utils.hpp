#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
/**
 * Conditional
 */
template<
	bool B,
	typename T,
	typename F
>
struct conditional
{
	typedef T type;
};

template<
	typename T,
	typename F
>
struct conditional<false, T, F>
{
	typedef F type;
};

/**
 * Enable_if
 */
template<
	bool B,
	typename T = void
>
struct enable_if
{
};

template<
	typename T
>
struct enable_if<true, T>
{
	typedef T type;
};

/**
 * Iterators TAGS
 */
struct iterator_output_tag
{};

struct iterator_input_tag
{};
struct iterator_forward_tag
	: public iterator_input_tag
{};
struct iterator_bidirectional_tag
	: public iterator_forward_tag
{};
struct iterator_randomaccess_tag
	: public iterator_bidirectional_tag
{};

/**
 * Is_iterable
 */
template<
	typename T
>
struct is_iterable
{
};

template<>
struct is_iterable<iterator_input_tag>
{
	static const bool value = true;
};

template<>
struct is_iterable<iterator_forward_tag>
{
	static const bool value = true;
};

template<>
struct is_iterable<iterator_bidirectional_tag>
{
	static const bool value = true;
};

template<>
struct is_iterable<iterator_randomaccess_tag>
{
	static const bool value = true;
};

/**
 * Equals
 */
template<
	typename InputIteratorA,
	typename InputIteratorB
>
bool
equal(
	InputIteratorA it_lhs_begin,
	InputIteratorA it_lhs_end,
	InputIteratorB it_rhs_begin
)
{
	for ( ; it_lhs_begin != it_lhs_end; ++it_lhs_begin, ++it_rhs_begin)
	{
		if (!(*it_lhs_begin == *it_rhs_begin))
			return false;
	}
	return true;
};

/**
 * Lexicographical Compare
 */
template<
	typename InputIteratorA,
	typename InputIteratorB
>
bool
lexicographical_compare(
	InputIteratorA first1,
	InputIteratorA last1,
	InputIteratorB first2,
	InputIteratorB last2
)
{
	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
	{
		if (*first1 < *first2) return true;
		if (*first2 < *first1) return false;
	}
	return (first1 == last1) && (first2 != last2);
};

} // End - Namespace

#endif