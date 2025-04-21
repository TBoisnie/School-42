#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "Utils.hpp"

namespace ft
{
/**
 * MapNode
 */
struct MapBaseNode
{
	MapBaseNode * parent;
	MapBaseNode * left;
	MapBaseNode * right;
};

template<
	typename T
>
struct MapNode
	: public MapBaseNode
{
	T data;
};
// End - MapNode

/**
 * MapIterator
 */
template<
	typename M,		// Map
	bool C = false	// Const
>
class MapIterator
{
public:
	/**
	 * Types
	 */
	typedef typename M::difference_type			difference_type;

	typedef ft::iterator_bidirectional_tag		iterator_type;

	typedef MapBaseNode *						node_base_pointer;
	typedef MapNode<typename M::value_type> *	node_pointer;

	typedef typename ft::conditional<C, typename M::const_pointer, typename M::pointer>::type		pointer;
	typedef typename ft::conditional<C, typename M::const_reference, typename M::reference>::type	reference;

public:
	/**
	 * Attributes
	 */
	node_base_pointer m_root;
	node_base_pointer m_current;

public:
	/**
	 * Constructors & Destructors
	 */
	MapIterator()
		: m_root()
		, m_current()
	{
		// Empty
	}

	MapIterator(
		node_base_pointer current
	)
		: m_current(current)
	{
		this->m_root = current;

		while (this->m_root->right != this->m_root)
		{
			this->m_root = this->m_root->parent;
		}
	}

	MapIterator(
		const MapIterator & other
	)
		: m_root(other.m_root)
		, m_current(other.m_current)
	{
		// Empty
	}

	// Allow conversion from iterator to const_iterator
	template<
		typename I
	>
	MapIterator(
		const MapIterator<I, false> & other
	)
		: m_root(other.m_root)
		, m_current(other.m_current)
	{
		// Empty
	}

	~MapIterator()
	{
		// Empty
	}

	MapIterator &
	operator=(
		const MapIterator & other
	)
	{
		if (this == &other)
			return *this;

		this->m_root = other.m_root;
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

	MapIterator &
	operator++()
	{

		// end()
		if (this->m_current == this->m_root)
			return *this;

		// Have a sub right tree
		if (this->m_current->right)
		{
			this->m_current = m_current->right;

			while (this->m_current->left)
				this->m_current = this->m_current->left;
		}
		else
		{
			node_base_pointer parent = this->m_current->parent;

			while (this->m_current == parent->right)
			{
				this->m_current = parent;
				parent = parent->parent;
			}

			if (this->m_current != this->m_root && this->m_current->right != parent)
				this->m_current = parent;
		}

		return *this;
	}

	MapIterator
	operator++(int)
	{
		MapIterator tmp(*this);

		this->operator++();

		return tmp;
	}

	/**
	 * Bidirectional
	 */
	MapIterator &
	operator--()
	{
		// end()
		if (this->m_current == this->m_root)
		{
			this->m_current = this->m_root->parent;
			return *this;
		}

		// Have a sub left tree
		if (this->m_current->left)
		{
			this->m_current = m_current->left;

			while (this->m_current->right)
				this->m_current = this->m_current->right;
		}
		else
		{
			node_base_pointer parent = this->m_current->parent;

			while (this->m_current == parent->left)
			{
				this->m_current = parent;
				parent = parent->parent;
			}

			if (this->m_current != this->m_root && this->m_current->left != parent)
				this->m_current = parent;
		}

		return *this;
	}

	MapIterator
	operator--(int)
	{
		MapIterator tmp(*this);

		this->operator--();

		return tmp;
	}

}; // End - MapIterator

/**
 * Relational Operators
 */
template<
	typename M,
	bool C
>
bool
operator==(
	const MapIterator<M, C> & x,
	const MapIterator<M, C> & y
)
{
	return x.m_current == y.m_current;
}

template<
	typename M,
	bool C
>
bool
operator!=(
	const MapIterator<M, C> & x,
	const MapIterator<M, C> & y
)
{
	return !(x == y);
}

/**
 * Const / Non Const Relational Operators
 */
template<
	typename M,
	bool C
>
bool
operator==(
	const MapIterator<M, C> & x,
	const MapIterator<M, !C> & y
)
{
	return x.m_current == y.m_current;
}

template<
	typename M,
	bool C
>
bool
operator!=(
	const MapIterator<M, C> & x,
	const MapIterator<M, !C> & y
)
{
	return !(x == y);
}

}; // End - Namespace

#endif