#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{
/**
 * ReverseIterator
 */
template<
	typename I	// Iterator
>
class ReverseIterator
{
public:
	/**
	 * Types
	 */
	typedef I								iterator_type;

	typedef typename I::difference_type		difference_type;
	typedef typename I::pointer				pointer;
	typedef typename I::reference			reference;

private:
	/**
	 * Attributes
	 */
	iterator_type m_current;

public:
	/**
	 * Constructors & Destructors
	 */
	ReverseIterator()
		: m_current()
	{
		// Empty
	}

	explicit
	ReverseIterator(
		iterator_type it
	)
		: m_current(it)
	{
		// Empty
	}

	ReverseIterator(
		const ReverseIterator & other
	)
		: m_current(other.base())
	{
		// Empty
	}

	// Allow conversion from reverse_iterator to const_reverse_iterator
	template<
		typename IT
	>
	ReverseIterator(
		const ReverseIterator<IT> & other
	)
		: m_current(other.base())
	{
		// Empty
	}

	~ReverseIterator()
	{
		// Empty
	}

	ReverseIterator &
	operator=(
		const ReverseIterator & other
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
	iterator_type
	base() const
	{
		return this->m_current;
	}

	/**
	 * Operators
	 */
	reference
	operator*() const
	{
		iterator_type tmp = this->m_current;

		return *--tmp;
	}

	pointer
	operator->() const
	{
		return &(this->operator*()); // TODO: Test
	}

	ReverseIterator &
	operator++()
	{
		--this->m_current;

		return *this;
	}

	ReverseIterator
	operator++(int)
	{
		ReverseIterator tmp = *this;

		--this->m_current;

		return tmp;
	}

	ReverseIterator &
	operator--()
	{
		++this->m_current;

		return *this;
	}

	ReverseIterator
	operator--(int)
	{
		ReverseIterator tmp = *this;

		++this->m_current;

		return tmp;
	}

	ReverseIterator
	operator+(
		difference_type n
	) const
	{
		return ReverseIterator(this->m_current - n);
	}

	ReverseIterator &
	operator+=(
		difference_type n
	)
	{
		this->m_current += n;

		return *this;
	}

	ReverseIterator
	operator-(
		difference_type n
	) const
	{
		return ReverseIterator(this->m_current + n);
	}

	ReverseIterator &
	operator-=(
		difference_type n
	)
	{
		this->m_current += n;

		return *this;
	}

	reference
	operator[](
		difference_type n
	) const
	{
		return *(*this + n);
	}

}; // End - ReverseIterator

/**
 * Relational Operators
 */
template<
	typename I
>
bool
operator==(
	const ReverseIterator<I> & x,
	const ReverseIterator<I> & y
)
{
	return x.base() == y.base();
}

template<
	typename I
>
bool
operator!=(
	const ReverseIterator<I> & x,
	const ReverseIterator<I> & y
)
{
	return !(x == y);
}

template<
	typename I
>
bool
operator<(
	const ReverseIterator<I> & x,
	const ReverseIterator<I> & y
)
{
	return y.base() < x.base();
}

template<
	typename I
>
bool
operator>(
	const ReverseIterator<I> & x,
	const ReverseIterator<I> & y
)
{
	return y < x;
}

template<
	typename I
>
bool
operator<=(
	const ReverseIterator<I> & x,
	const ReverseIterator<I> & y
)
{
	return !(y < x);
}

template<
	typename I
>
bool
operator>=(
	const ReverseIterator<I> & x,
	const ReverseIterator<I> & y
)
{
	return !(x < y);
}

/**
 * Const / Non Const Relational Operators
 */
template<
	typename IA,
	typename IB
>
bool
operator==(
	const ReverseIterator<IA> & x,
	const ReverseIterator<IB> & y
)
{
	return x.base() == y.base();
}

template<
	typename IA,
	typename IB
>
bool
operator!=(
	const ReverseIterator<IA> & x,
	const ReverseIterator<IB> & y
)
{
	return !(x == y);
}

template<
	typename IA,
	typename IB
>
bool
operator<(
	const ReverseIterator<IA> & x,
	const ReverseIterator<IB> & y
)
{
	return y.base() < x.base();
}

template<
	typename IA,
	typename IB
>
bool
operator>(
	const ReverseIterator<IA> & x,
	const ReverseIterator<IB> & y
)
{
	return y < x;
}

template<
	typename IA,
	typename IB
>
bool
operator<=(
	const ReverseIterator<IA> & x,
	const ReverseIterator<IB> & y
)
{
	return !(y < x);
}

template<
	typename IA,
	typename IB
>
bool
operator>=(
	const ReverseIterator<IA> & x,
	const ReverseIterator<IB> & y
)
{
	return !(x < y);
}

/**
 * Arithmetic Operators
 */
template<
	typename I
>
typename ReverseIterator<I>::difference_type
operator-(
	const ReverseIterator<I> & x,
	const ReverseIterator<I> & y
)
{
	return y.base() - x.base();
}

template<
	typename I
>
ReverseIterator<I>
operator+(
	typename ReverseIterator<I>::difference_type n,
	const ReverseIterator<I> & rit
)
{
	return ReverseIterator<I>(rit.base() - n);
}

} // End - Namespace

#endif