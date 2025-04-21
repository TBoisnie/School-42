#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "Utils.hpp"

namespace ft
{
/**
 * VectorIterator
 */
template<
	typename V,		// Vector
	bool C = false	// Const
>
class VectorIterator
{
public:
	/**
	 * Types
	 */
	typedef typename V::difference_type		difference_type;

	typedef ft::iterator_randomaccess_tag	iterator_type;

	typedef typename ft::conditional<C, typename V::const_pointer, typename V::pointer>::type		pointer;
	typedef typename ft::conditional<C, typename V::const_reference, typename V::reference>::type	reference;

private:
	/**
	 * Attributes
	 */
	pointer m_current;

public:
	/**
	 * Constructors & Destructors
	 */
	VectorIterator()
		: m_current()
	{
		// Empty
	}

	VectorIterator(
		pointer current
	)
		: m_current(current)
	{
		// Empty
	}

	VectorIterator(
		const VectorIterator & other
	)
		: m_current(other.m_current)
	{
		// Empty
	}

	// Allow conversion from iterator to const_iterator
	template<
		typename I
	>
	VectorIterator(
		const VectorIterator<I, false> & other
	)
		: m_current(other.base())
	{
		// Empty
	}

	~VectorIterator()
	{
		// Empty
	}

	VectorIterator &
	operator=(
		const VectorIterator & other
	)
	{
		if (this == &other)
			return *this;

		this->m_current = other.m_current;

		return *this;
	}

	/**
	 * Methods
	 */
	const pointer
	base() const
	{
		return this->m_current;
	}

	/**
	 * Forward
	 */
	reference
	operator*()
	{
		return *(this->m_current);
	}

	pointer
	operator->()
	{
		return this->m_current;
	}

	VectorIterator &
	operator++()
	{
		++this->m_current;

		return *this;
	}

	VectorIterator
	operator++(int)
	{
		return VectorIterator(this->m_current++);
	}

	/**
	 * Bidirectional
	 */
	VectorIterator &
	operator--()
	{
		--this->m_current;

		return *this;
	}

	VectorIterator
	operator--(int)
	{
		return VectorIterator(this->m_current--);
	}

	/**
	 * Random access
	 */
	reference
	operator[](
		difference_type n
	) const
	{
		return *(this->m_current + n);
	}

	VectorIterator &
	operator+=(
		difference_type n
	)
	{
		this->m_current += n;

		return *this;
	}

	VectorIterator
	operator+(
		difference_type n
	) const
	{
		return VectorIterator(this->m_current + n);
	}

	VectorIterator &
	operator-=(
		difference_type n
	)
	{
		this->m_current -= n;

		return *this;
	}

	VectorIterator
	operator-(
		difference_type n
	) const
	{
		return VectorIterator(this->m_current - n);
	}

}; // End - VectorIterator

/**
 * Relational Operators
 */
template<
	typename V,
	bool C
>
bool
operator==(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, C> & y
)
{
	return x.base() == y.base();
}

template<
	typename V,
	bool C
>
bool
operator!=(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, C> & y
)
{
	return !(x == y);
}

template<
	typename V,
	bool C
>
bool
operator<(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, C> & y
)
{
	return x.base() < y.base();
}

template<
	typename V,
	bool C
>
bool
operator>(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, C> & y
)
{
	return y < x;
}

template<
	typename V,
	bool C
>
bool
operator<=(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, C> & y
)
{
	return !(y < x);
}

template<
	typename V,
	bool C
>
bool
operator>=(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, C> & y
)
{
	return !(x < y);
}

/**
 * Const / Non Const Relational Operators
 */
template<
	typename V,
	bool C
>
bool
operator==(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, !C> & y
)
{
	return x.base() == y.base();
}

template<
	typename V,
	bool C
>
bool
operator!=(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, !C> & y
)
{
	return !(x == y);
}

template<
	typename V,
	bool C
>
bool
operator<(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, !C> & y
)
{
	return x.base() < y.base();
}

template<
	typename V,
	bool C
>
bool
operator>(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, !C> & y
)
{
	return y < x;
}

template<
	typename V,
	bool C
>
bool
operator<=(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, !C> & y
)
{
	return !(y < x);
}

template<
	typename V,
	bool C
>
bool
operator>=(
	const VectorIterator<V, C> & x,
	const VectorIterator<V, !C> & y
)
{
	return !(x < y);
}

/**
 * Arithmetic Operators
 */
template<
	typename V
>
typename VectorIterator<V>::difference_type
operator-(
	const VectorIterator<V> & x,
	const VectorIterator<V> & y
)
{
	return x.base() - y.base();
}

}; // End - Namespace

#endif