#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

#include <cstddef> // size_t

namespace ft
{

/**
 * UnaryFunction
 *
 * @ref https://cplusplus.com/reference/functional/unary_function/
 * @ref https://en.cppreference.com/w/cpp/utility/functional/unary_function
 */
template <
	typename Arg,
	typename Result
>
struct unary_function
{
	typedef Arg     argument_type;
	typedef Result  result_type;
}; // struct unary_function

/**
 * BinaryFunction
 *
 * @ref https://cplusplus.com/reference/functional/binary_function/
 * @ref https://en.cppreference.com/w/cpp/utility/functional/binary_function
 */
template<
	typename Arg1,
	typename Arg2,
	typename Result
>
struct binary_function
{
	typedef Arg1    first_argument_type;
	typedef Arg2    second_argument_type;
	typedef Result  result_type;
}; // struct binary_function

/**
 * Identity
 *
 * @ref https://en.cppreference.com/w/cpp/utility/functional/identity
 */
template<
	typename Arg
>
struct identity
	: public ft::unary_function< Arg, Arg >
{
private:
	typedef ft::unary_function< Arg, Arg >  _self_base_type;

public:
	using typename _self_base_type::argument_type;
	using typename _self_base_type::result_type;

public:
	result_type &
	operator()(
		argument_type & value
	) const
	{
		return value;
	}

	result_type const &
	operator()(
		argument_type const & value
	) const
	{
		return value;
	}
}; // struct identity

/**
 * Select1st
 */
template<
	typename Pair
>
struct select1st
	: public ft::unary_function< Pair, typename Pair::first_type >
{
private:
	typedef ft::unary_function< Pair, typename Pair::first_type >  _self_base_type;

public:
	using typename _self_base_type::argument_type;
	using typename _self_base_type::result_type;

public:
	result_type &
	operator()(
		argument_type & p
	) const
	{
		return p.first;
	}

	result_type const &
	operator()(
		argument_type const & p
	) const
	{
		return p.first;
	}
}; // struct select1st

/**
 * Select2nd
 */
template<
	typename Pair
>
struct select2nd
	: public ft::unary_function< Pair, typename Pair::second_type >
{
private:
	typedef ft::unary_function< Pair, typename Pair::second_type >  _self_base_type;

public:
	using typename _self_base_type::argument_type;
	using typename _self_base_type::result_type;

public:
	result_type &
	operator()(
		argument_type & p
	) const
	{
		return p.second;
	}

	result_type const &
	operator()(
		argument_type const & p
	) const
	{
		return p.second;
	}
}; // struct select2nd

/**
 * Less
 *
 * @ref https://cplusplus.com/reference/functional/less/
 * @ref https://en.cppreference.com/w/cpp/utility/functional/less
 */
template<
	typename Arg1,
	typename Arg2 = Arg1
>
struct less
	: public ft::binary_function< Arg1, Arg2, bool >
{
private:
	typedef ft::binary_function< Arg1, Arg2, bool >  _self_base_type;

public:
	using typename _self_base_type::first_argument_type;
	using typename _self_base_type::second_argument_type;
	using typename _self_base_type::result_type;

public:
	result_type
	operator()(
		first_argument_type const & x,
		second_argument_type const & y
	) const
	{
		return ( x < y );
	}
}; // struct less

/**
 * Greater
 *
 * @ref https://cplusplus.com/reference/functional/greater/
 * @ref https://en.cppreference.com/w/cpp/utility/functional/greater
 */
template<
	typename Arg1,
	typename Arg2 = Arg1
>
struct greater
	: public ft::binary_function< Arg1, Arg2, bool >
{
private:
	typedef ft::binary_function< Arg1, Arg2, bool >  _self_base_type;

public:
	using typename _self_base_type::first_argument_type;
	using typename _self_base_type::second_argument_type;
	using typename _self_base_type::result_type;

public:
	result_type
	operator()(
		first_argument_type const & x,
		second_argument_type const & y
	) const
	{
		return ( x > y );
	}
}; // struct greater

/**
 * EqualTo
 *
 * @ref https://cplusplus.com/reference/functional/equal_to/
 * @ref https://en.cppreference.com/w/cpp/utility/functional/equal_to
 */
template<
	typename Arg1,
	typename Arg2 = Arg1
>
struct equal_to
	: public ft::binary_function< Arg1, Arg2, bool >
{
private:
	typedef ft::binary_function< Arg1, Arg2, bool >  _self_base_type;

public:
	using typename _self_base_type::first_argument_type;
	using typename _self_base_type::second_argument_type;
	using typename _self_base_type::result_type;

public:
	result_type
	operator()(
		first_argument_type const & x,
		second_argument_type const & y
	) const
	{
		return ( x == y );
	}
}; // struct equal_to

/**
 * AssignTo
 */
template<
	typename T
>
struct assign_to
	: public ft::binary_function< T, T, void >
{
private:
	typedef ft::binary_function< T, T, void >  _self_base_type;

public:
	using typename _self_base_type::first_argument_type;
	using typename _self_base_type::second_argument_type;
	using typename _self_base_type::result_type;

public:
	result_type
	operator()(
		first_argument_type & x,
		second_argument_type const & y
	) const
	{
		x = y;
	}
}; // struct assign_to

/**
 * Hash
 *
 * @ref https://cplusplus.com/reference/functional/hash/
 * @ref https://en.cppreference.com/w/cpp/utility/hash
 */
template<
	typename Arg
>
struct hash
	: public ft::unary_function< Arg, size_t >
{
}; // struct hash

// - Specialization ( int )
template<>
struct hash< int >
	: public ft::unary_function< int, size_t >
{
private:
	typedef ft::unary_function< int, size_t >  _self_base_type;

public:
	using typename _self_base_type::argument_type;
	using typename _self_base_type::result_type;

public:
	result_type
	operator()(
		argument_type const & x
	) const
	{
		return static_cast< result_type >( x );
	}
}; // struct hash< int >

// Todo: Implement more specializations ( integral types, string, ... )

} // namespace ft

#endif
