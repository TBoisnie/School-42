#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "Utils.hpp"

namespace ft
{

/**
 * ListNode
 */
struct ListBaseNode
{
	ListBaseNode * prev;
	ListBaseNode * next;
};

template<
	typename T
>
struct ListNode
	: public ListBaseNode
{
	T data;
};
// End - ListNode

/**
 * ListIterator
 */
template<
	typename L,		// List
	bool C = false	// Const
>
class ListIterator
{
private:
	/**
	 * Types
	 */
	typedef ListBaseNode *							node_base_pointer;
	typedef ListNode<typename L::value_type> *		node_pointer;

public:
	typedef ft::iterator_bidirectional_tag			iterator_type;

	typedef typename L::difference_type		difference_type;

	typedef typename ft::conditional<C, typename L::const_pointer, typename L::pointer>::type		pointer;
	typedef typename ft::conditional<C, typename L::const_reference, typename L::reference>::type	reference;

public:
	/**
	 * Attributes
	 */
	node_base_pointer m_current;

public:
	/**
	 * Constructors & Destructors
	 */
	ListIterator()
		: m_current()
	{
		// Empty
	}

	ListIterator(
		node_base_pointer current
	)
		: m_current(current)
	{
		// Empty
	}

	ListIterator(
		const ListIterator & other
	)
		: m_current(other.m_current)
	{
		// Empty
	}

	// Allow conversion from iterator to const_iterator
	template<
		typename I
	>
	ListIterator(
		const ListIterator<I, false> & other
	)
		: m_current(other.m_current)
	{
		// Empty
	}

	~ListIterator()
	{
		// Empty
	}

	ListIterator &
	operator=(
		const ListIterator & other
	)
	{
		if (this == &other)
			return *this;

		this->m_current = other.m_current;

		return *this;
	}

	/**
	 * Forward
	 */
	reference
	operator*()
	{
		return static_cast<node_pointer>(this->m_current)->data;
	}

	pointer
	operator->()
	{
		return &static_cast<node_pointer>(this->m_current)->data;
	}

	ListIterator &
	operator++()
	{
		this->m_current = this->m_current->next;
		return *this;
	}

	ListIterator
	operator++(int)
	{
		ListIterator tmp(*this);

		this->m_current = this->m_current->next;

		return tmp;
	}

	/**
	 * Bidirectional
	 */
	ListIterator &
	operator--()
	{
		this->m_current = this->m_current->prev;

		return *this;
	}

	ListIterator
	operator--(int)
	{
		ListIterator tmp(*this);

		this->m_current = this->m_current->prev;

		return tmp;
	}

}; // End - ListIterator

/**
 * Relational Operators
 */
template<
	typename L,
	bool C
>
bool
operator==(
	const ListIterator<L, C> & x,
	const ListIterator<L, C> & y
)
{
	return x.m_current == y.m_current;
}

template<
	typename L,
	bool C
>
bool
operator!=(
	const ListIterator<L, C> & x,
	const ListIterator<L, C> & y
)
{
	return !(x == y);
}

/**
 * Const / Non Const Relational Operators
 */
template<
	typename L,
	bool C
>
bool
operator==(
	const ListIterator<L, C> & x,
	const ListIterator<L, !C> & y
)
{
	return x.m_current == y.m_current;
}

template<
	typename L,
	bool C
>
bool
operator!=(
	const ListIterator<L, C> & x,
	const ListIterator<L, !C> & y
)
{
	return !(x == y);
}

}; // End - Namespace

#endif