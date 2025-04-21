#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "List.hpp"

namespace ft
{
/**
 * Queue
 */
template<
	typename T,
	typename C = ft::List<T>
>
class Queue
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
		const Queue<_T, _C> &,
		const Queue<_T, _C> &
	);

	template<
		typename _T,
		typename _C
	>
	friend bool
	operator<(
		const Queue<_T, _C> &,
		const Queue<_T, _C> &
	);

public:
	/**
	 * Types
	 */
	typedef C		container_type;
	typedef T		value_type;

	typedef typename C::size_type	size_type;

protected:
	/**
	 * Attributes
	 */
	container_type m_ctnr;

public:
	/**
	 * Constructors & Destructors
	 */
	explicit
	Queue(
		const container_type & ctnr = container_type()
	)
		: m_ctnr(ctnr)
	{
		// Empty
	}

	Queue(
		const Queue & other
	)
	{
		this->operator=(other);
	}

	~Queue()
	{
		// Empty
	}

	Queue &
	operator=(
		const Queue & other
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
	front()
	{
		return this->m_ctnr.front();
	}

	const value_type &
	front() const
	{
		return this->m_ctnr.front();
	}

	value_type &
	back()
	{
		return this->m_ctnr.back();
	}

	const value_type &
	back() const
	{
		return this->m_ctnr.back();
	}

	/**
	 * Modifiers
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
		this->m_ctnr.pop_front();
	}

}; // End - Queue

/**
 * Relational Operators
 */
template<
	typename T,
	typename C
>
bool
operator==(
	const Queue<T, C> & x,
	const Queue<T, C> & y
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
	const Queue<T, C> & x,
	const Queue<T, C> & y
)
{
	return !(x == y);
}

template<
	typename T,
	typename C
>
bool
operator<(
	const Queue<T, C> & x,
	const Queue<T, C> & y
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
	const Queue<T, C> & x,
	const Queue<T, C> & y
)
{
	return !(y < x);
}

template<
	typename T,
	typename C
>
bool
operator>(
	const Queue<T, C> & x,
	const Queue<T, C> & y
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
	const Queue<T, C> & x,
	const Queue<T, C> & y
)
{
	return !(x < y);
}

}; // End - Namespace

#endif