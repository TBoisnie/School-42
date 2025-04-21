#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include <memory>
# include <limits>

# include "Utils.hpp"
# include "VectorIterator.hpp"
# include "ReverseIterator.hpp"

namespace ft
{

/**
 * Vector
 */
template <
	typename T
>
class Vector
{
public:
	/**
	 * Types
	 */
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	typedef T			value_type;
	typedef T *			pointer;
	typedef T &			reference;
	typedef T const *	const_pointer;
	typedef T const &	const_reference;

	typedef VectorIterator<Vector<T> >			iterator;
	typedef ReverseIterator<iterator>			reverse_iterator;
	typedef VectorIterator<Vector<T>, true>		const_iterator;
	typedef ReverseIterator<const_iterator>		const_reverse_iterator;

private:
	/**
	 * Attributes
	 */
	pointer		m_data;
	size_type	m_size;
	size_type	m_capacity;

public:
	/**
	 * Constructors & Destructors
	 */
	explicit
	Vector()
		: m_data()
		, m_size(0)
		, m_capacity(0)
	{
		// Empty
	}

	explicit
	Vector(
		size_type n,
		const value_type & val = value_type()
	)
		: m_data()
		, m_size(0)
		, m_capacity(0)
	{
		this->checkSize(n);

		this->m_capacity = this->nextCapacity(n);
		this->m_data = new value_type[this->capacity()];

		while (this->size() < n)
			::new (&this->m_data[this->m_size++]) value_type(val);
	}

	template<
		typename InputIterator
	>
	Vector(
		InputIterator first,
		InputIterator last,
		typename ft::enable_if<ft::is_iterable<typename InputIterator::iterator_type>::value, void>::type* = NULL
	)
		: m_data()
		, m_size(0)
		, m_capacity(0)
	{
		size_type n = 0;

		InputIterator f = first;
		while (f++ != last)
			++n;

		this->checkSize(n);

		this->m_capacity = this->nextCapacity(n);
		this->m_size = 0;
		this->m_data = new value_type[this->m_capacity];

		while(first != last)
			::new (&this->m_data[this->m_size++]) value_type(*first++);
	}

	Vector(
		const Vector & other
	)
		: m_data()
		, m_size(0)
		, m_capacity(0)
	{
		this->operator=(other);
	}

	~Vector()
	{
		delete[] this->m_data;
	}

	/**
	 * Operators
	 */
	Vector&
	operator=(
		const Vector & other
	)
	{
		if (this == &other)
			return *this;

		delete[] this->m_data;

		this->m_capacity = other.capacity();
		this->m_size = 0;
		this->m_data = new value_type[this->capacity()];

		for (const_iterator it = other.begin(); it != other.end(); ++it)
			::new (&this->m_data[this->m_size++]) value_type(*it);

		return *this;
	}

	reference
	operator[](
		size_type n
	)
	{
		return this->m_data[n];
	}

	const_reference
	operator[](
		size_type n
	) const
	{
		return this->m_data[n];
	}

	/**
	 * Iterator
	 */
	iterator
	begin()
	{
		return iterator(this->m_data);
	}

	iterator
	end()
	{
		return iterator(this->m_data + this->size());
	}

	const_iterator
	begin() const
	{
		return const_iterator(this->m_data);
	}

	const_iterator
	end() const
	{
		return const_iterator(this->m_data + this->size());
	}

	reverse_iterator
	rbegin()
	{
		return reverse_iterator(this->end());
	}

	reverse_iterator
	rend()
	{
		return reverse_iterator(this->begin());
	}

	const_reverse_iterator
	rbegin() const
	{
		return const_reverse_iterator(this->end());
	}

	const_reverse_iterator
	rend() const
	{
		return const_reverse_iterator(this->begin());
	}

	/**
	 * Capacity
	 */
	size_type
	size() const
	{
		return this->m_size;
	}

	size_type
	max_size() const
	{
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	size_type
	capacity() const
	{
		return this->m_capacity;
	}

	bool
	empty() const
	{
		return this->size() == 0;
	}

	void
	resize(
		size_type n,
		value_type val = value_type()
	)
	{
		while (this->size() < n)
			this->push_back(val);

		while (this->size() > n)
			this->pop_back();
	}

	void
	reserve(
		size_type n
	)
	{
		this->checkLength(n);

		if (this->capacity() < n)
			this->reallocate(n);
	}

	/**
	 * Elements Access
	 */
	reference
	at(
		size_type n
	)
	{
		this->checkRange(n);
		return this->m_data[n];
	}

	reference
	front()
	{
		return this->m_data[0];
	}

	reference
	back()
	{
		return this->m_data[this->size() - 1];
	}

	const_reference
	at(
		size_type n
	) const
	{
		this->checkRange(n);
		return this->m_data[n];
	}

	const_reference
	front() const
	{
		return this->m_data[0];
	}

	const_reference
	back() const
	{
		return this->m_data[this->size() - 1];
	}

	/**
	 * Modifiers
	 */
	void
	assign(
		size_type n,
		const value_type & val
	)
	{
		this->clear();

		while (n--)
			this->push_back(val);
	}

	template<
		typename InputIterator
	>
	typename ft::enable_if<ft::is_iterable<typename InputIterator::iterator_type>::value, void>::type
	assign(
		InputIterator first,
		InputIterator last
	)
	{
		this->clear();

		while (first != last)
			this->push_back(*first++);
	}

	void
	push_back(
		const value_type & val
	)
	{
		this->checkSize(1);
		this->reserve(this->size() + 1);
		::new (&this->m_data[this->m_size++]) value_type(val);
	}

	void
	pop_back()
	{
		this->m_data[--this->m_size].~value_type();
	}

	iterator
	insert(
		iterator position,
		const value_type & val
	)
	{
		difference_type dist = position - this->begin();

		this->insert(position, 1, val);

		return iterator(this->m_data + dist);
	}

	void
	insert(
		iterator position,
		size_type n,
		const value_type & val
	)
	{
		this->checkSize(n);

		size_type dist_end = static_cast<size_type>(this->end() - position);

		this->reserve(this->size() + n);
		this->m_size += n;

		for (size_type i = 1; i <= dist_end; ++i)
		{
			if (i >= n)
				this->m_data[this->size() - i].~value_type();

			::new (&this->m_data[this->size() - i]) value_type(this->m_data[this->size() - i - n]);
		}

		for (size_type i = 1; i <= n; ++i)
		{
			this->m_data[this->size() - dist_end - i].~value_type();

			::new (&this->m_data[this->size() - dist_end - i]) value_type(val);
		}
	}

	template<
		typename InputIterator
	>
	typename ft::enable_if<ft::is_iterable<typename InputIterator::iterator_type>::value, void>::type
	insert(
		iterator position,
		InputIterator first,
		InputIterator last
	)
	{
		difference_type dist = position - this->begin();

		while (first != last)
			this->insert(iterator(this->m_data + dist++), 1, *first++);
	}

	iterator
	erase(
		iterator position
	)
	{
		return this->erase(position, position + 1);
	}

	iterator
	erase(
		iterator first,
		iterator last
	)
	{
		difference_type n = 0;

		while (first != last)
		{
			first->~value_type();
			++first;
			++n;
		}

		difference_type dist_begin = (last - this->begin()) - n;

		while (last != this->end())
		{
			::new (&this->m_data[dist_begin]) value_type(*last);

			last->~value_type();

			++last;
			++dist_begin;
		}

		this->m_size -= static_cast<size_type>(n);

		return first - n;
	}

	void
	swap(
		Vector & x
	)
	{
		pointer tmp_data = this->m_data;
		size_type tmp_size = this->m_size;
		size_type tmp_capacity = this->m_capacity;

		this->m_data = x.m_data;
		this->m_size = x.m_size;
		this->m_capacity = x.m_capacity;

		x.m_data = tmp_data;
		x.m_size = tmp_size;
		x.m_capacity = tmp_capacity;
	}

	void
	clear()
	{
		while (this->size() > 0)
			this->pop_back();
	}

private:
	/**
	 * Private Methods
	 */
	void
	checkSize(
		size_type n
	)
	{
		if (n > this->max_size() || this->size() > this->max_size() - n)
			throw std::runtime_error("Vector : Maximum size exceeded.");
	}

	void
	checkLength(
		size_type n
	)
	{
		if (n > this->max_size())
			throw std::length_error("Vector : Maximum size exceeded.");
	}

	void
	checkRange(
		size_type n
	)
	{
		if (n < 0 || this->size() <= n)
			throw std::out_of_range("Vector: Index out of range.");
	}

	size_type
	nextCapacity(
		size_type n
	)
	{
		size_type p = 1;

		if (n && !(n & (n - 1)))
			return n;

		while (p < n)
			p <<= 1;

		return p;
	}

	void
	reallocate(
		size_type n
	)
	{
		size_type	new_capacity = this->nextCapacity(n);
		size_type	new_size = 0;
		pointer		new_data = new value_type[new_capacity];

		for (iterator it = this->begin(); it != this->end(); ++it)
			::new (&new_data[new_size++]) value_type(*it);

		delete[] this->m_data;

		this->m_data = new_data;
		this->m_size = new_size;
		this->m_capacity = new_capacity;
	}

}; // End - Vector

/**
 * Relatinal Operators
 */
template<
	typename T
>
bool
operator==(
	const Vector<T> & x,
	const Vector<T> & y
)
{
	if (x.size() != y.size())
		return false;

	return ft::equal(x.begin(), x.end(), y.begin());
}

template<
	typename T
>
bool
operator!=(
	const Vector<T> & x,
	const Vector<T> & y
)
{
	return !(x == y);
}

template<
	typename T
>
bool
operator<(
	const Vector<T> & x,
	const Vector<T> & y
)
{
	return ft::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end()
	);
}

template<
	typename T
>
bool
operator<=(
	const Vector<T> & x,
	const Vector<T> & y
)
{
	return !(y < x);
}

template<
	typename T
>
bool
operator>(
	const Vector<T> & x,
	const Vector<T> & y
)
{
	return y < x;
}

template<
	typename T
>
bool
operator>=(
	const Vector<T> & x,
	const Vector<T> & y
)
{
	return !(x < y);
}

/**
 * Swap
 */
template<
	typename T
>
void
swap(
	Vector<T> & x,
	Vector<T> & y
)
{
	x.swap(y);
}

}; // End - Namespace

#endif