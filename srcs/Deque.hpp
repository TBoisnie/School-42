#ifndef _DEQUE_HPP_
# define _DEQUE_HPP_ 1

# include <memory>

# include "Utils.hpp"
# include "ReverseIterator.hpp"

namespace ft
{

/**
 * Deque
 */
template <
	typename T
>
class Deque
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

	typedef DequeIterator<Deque<T>>			iterator;
	typedef ReverseIterator<iterator>		reverse_iterator;

	typedef DequeIterator<Deque<T>, true>	const_iterator;
	typedef ReverseIterator<const_iterator>	const_reverse_iterator;

private:
	/**
	 * Attributes
	 */

public:
	/**
	 * Constructors & Destructors
	 */
	explicit
	Deque();

	explicit
	Deque(
		size_type n,
		const value_type & val = value_type()
	);

	template <
		class InputIterator
	>
	Deque(
		InputIterator first,
		InputIterator last
	);

	Deque(
		const Deque & x
	);

	~Deque();

	Deque&
	operator=(
		const Deque & x
	);

	/**
	 * Iterators
	 */
	iterator
	begin();

	const_iterator
	begin() const;

	iterator
	end();

	const_iterator
	end() const;

	reverse_iterator
	rbegin();

	const_reverse_iterator
	rbegin() const;

	reverse_iterator
	rend();

	const_reverse_iterator
	rend() const;

	/**
	 * Capacity
	 */
	size_type
	size() const;

	size_type
	max_size() const;

	void
	resize(
		size_type n,
		value_type val = value_type()
	);

	bool
	empty() const;

	/**
	 * Element Access
	 */
	reference
	operator[](
		size_type n
	);

	const_reference
	operator[](
		size_type n
	) const;

	reference
	at(
		size_type n
	);

	const_reference
	at(
		size_type n
	) const;

	reference
	front();

	const_reference
	front() const;

	reference
	back();

	const_reference
	back() const;

	/**
	 * Modifiers
	 */
	template<
		typename InputIterator
	>
	void
	assign(
		InputIterator first,
		InputIterator last
	);

	void
	assign(
		size_type n,
		const value_type& val
	);

	void
	push_back(
		const value_type& val
	);

	void
	push_front(
		const value_type& val
	);

	void
	pop_back();

	void
	pop_front();

	iterator
	insert(
		iterator position,
		const value_type& val
	);

	void
	insert(
		iterator position,
		size_type n,
		const value_type & val
	);

	template<
		typename InputIterator
	>
	void
	insert(
		iterator position,
		InputIterator first,
		InputIterator last
	);

	iterator
	erase(
		iterator position
	);

	iterator
	erase(
		iterator first,
		iterator last
	);

	void
	swap(
		Deque & other
	);

	void
	clear();

}; // End - Deque

/**
 * Relational operators
 */
template<
	typename T
>
bool
operator==(
	const Deque<T> & lhs,
	const Deque<T> & rhs
);

template<
	typename T
>
bool
operator!=(
	const Deque<T> & lhs,
	const Deque<T> & rhs
);

template<
	typename T
>
bool
operator< (
	const Deque<T> & lhs,
	const Deque<T> & rhs
);

template<
	typename T
>
bool
operator<=(
	const Deque<T> & lhs,
	const Deque<T> & rhs
);

template<
	typename T
>
bool
operator> (
	const Deque<T> & lhs,
	const Deque<T> & rhs
);

template<
	typename T
>
bool
operator>=(
	const Deque<T> & lhs,
	const Deque<T> & rhs
);

/**
 * Swap
 */
template<
	typename T
>
void
swap(
	Deque<T> & x,
	Deque<T> & y
);

}; // End - Namespace

#endif