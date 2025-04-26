#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include "iterator.hpp"

namespace ft
{

/**
 * BooleanType
 */
struct true_type
{
	static bool const value = true;
};

struct false_type
{
	static bool const value = false;
};

/**
 * Conditional
 *
 * @ref https://cplusplus.com/reference/type_traits/conditional/
 */
template<
	bool Condition,
	typename Truthy,
	typename Falsy
>
struct conditional
{
	typedef Truthy  type;
};

template<
	typename Truthy,
	typename Falsy
>
struct conditional< false, Truthy, Falsy >
{
	typedef Falsy  type;
};

/**
 * EnableIf
 *
 * @ref https://cplusplus.com/reference/type_traits/enable_if/
 */
template<
	bool Condition,
	typename T = void
>
struct enable_if
{
};

template<
	typename T
>
struct enable_if< true, T >
{
	typedef T  type;
};

/**
 * IsConst
 */
template<
	typename T
>
struct is_const
	: ft::false_type
{
};

template<
	typename T
>
struct is_const< T const >
	: ft::true_type
{
};

/**
 * IsInteger
 */
template<
	typename T
>
struct is_integer
{
	typedef false_type  type;
	static bool const value = false;
};

template<>
struct is_integer< bool >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< char >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< signed char >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< unsigned char >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< short >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< unsigned short >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< int >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< unsigned int >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< long >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< unsigned long >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< long long >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_integer< unsigned long long >
{
	typedef true_type  type;
	static bool const value = true;
};

/**
 * IsIterable
 */
template<
	typename T
>
struct is_iterable
{
	typedef false_type  type;
	static bool const value = false;
};

template<>
struct is_iterable< ft::input_iterator_tag >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_iterable< ft::output_iterator_tag >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_iterable< ft::forward_iterator_tag >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_iterable< ft::bidirectional_iterator_tag >
{
	typedef true_type  type;
	static bool const value = true;
};

template<>
struct is_iterable< ft::random_access_iterator_tag >
{
	typedef true_type  type;
	static bool const value = true;
};

} // namespace ft

#endif
