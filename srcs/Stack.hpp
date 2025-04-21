#ifndef STACK_HPP
# define STACK_HPP

# include "List.hpp"

namespace ft
{
/**
 * Stack
 */
template<
	typename T,
	typename C = ft::List<T>
>
class Stack
{
private:
	/**
	 * Friends
	 */
	template<
		typename _T,
		typename _C
	>
	friend bool
	operator==(
		const Stack<_T, _C> &,
		const Stack<_T, _C> &
	);

	template<
		typename _T,
		typename _C
	>
	friend bool
	operator<(
		const Stack<_T, _C> &,
		const Stack<_T, _C> &
	);

public:
	/**
	 * Types
	 */
	typedef C		container_type;
	typedef T		value_type;

	typedef typename C::size_type		size_type;

private:
	/**
	 * Attributes
	 */
	container_type m_ctnr;

public:
	/**
	 * Constructors & Destructors
	 */
	explicit
	Stack(
		const container_type & ctnr = container_type()
	)
		: m_ctnr(ctnr)
	{
		// Empty
	}

	Stack(
		const Stack & other
	)
	{
		this->operator=(other);
	}

	~Stack()
	{
		// Empty
	}

	Stack &
	operator=(
		const Stack & other
	)
	{
		if (this == &other)
			return *this;

		this->m_ctnr = other.m_ctnr;

		return *this;
	}

	/**
	 * Capacity
	 */
	bool
	empty() const
	{
		return this->m_ctnr.empty();
	}

	size_type
	size() const
	{
		return this->m_ctnr.size();
	}

	/**
	 * Element Access
	 */
	value_type &
	top()
	{
		return this->m_ctnr.back();
	}

	const value_type &
	top() const
	{
		return this->m_ctnr.back();
	}

	/**
	 * Modifier
	 */
	void
	push(
		const value_type & val
	)
	{
		this->m_ctnr.push_back(val);
	}

	void
	pop()
	{
		this->m_ctnr.pop_back();
	}

}; // End - Stack

/**
 * Relational Operators
 */
template<
	typename T,
	typename C
>
bool
operator==(
	const Stack<T, C> & x,
	const Stack<T, C> & y
)
{
	return x.m_ctnr == y.m_ctnr;
}

template<
	typename T,
	typename C
>
bool
operator!=(
	const Stack<T, C> & x,
	const Stack<T, C> & y
)
{
	return !(x == y);
}

template<
	typename T,
	typename C
>
bool
operator< (
	const Stack<T, C> & x,
	const Stack<T, C> & y
)
{
	return x.m_ctnr < y.m_ctnr;
}

template<
	typename T,
	typename C
>
bool
operator<=(
	const Stack<T, C> & x,
	const Stack<T, C> & y
)
{
	return !(y < x);
}

template<
	typename T,
	typename C
>
bool
operator> (
	const Stack<T, C> & x,
	const Stack<T, C> & y
)
{
	return y < x;
}

template<
	typename T,
	typename C
>
bool
operator>=(
	const Stack<T, C> & x,
	const Stack<T, C> & y
)
{
	return !(x < y);
}

}; // End - Namespace

#endif