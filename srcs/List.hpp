#ifndef LIST_HPP
# define LIST_HPP

# include <cstddef>
# include <memory>
# include <limits>

# include "Utils.hpp"
# include "ListIterator.hpp"
# include "ReverseIterator.hpp"

namespace ft
{
/**
 * List
 */
template<
	typename T
>
class List
{
private:
	/**
	 * Types
	 */
	typedef ListBaseNode		node_base_type;
	typedef ListNode<T>			node_type;
	typedef node_base_type *	node_base_pointer;
	typedef node_type *			node_pointer;

public:
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	typedef T						value_type;
	typedef value_type *			pointer;
	typedef value_type &			reference;
	typedef value_type const *		const_pointer;
	typedef value_type const &		const_reference;

	typedef ListIterator<List<T> >				iterator;
	typedef ReverseIterator<iterator>			reverse_iterator;
	typedef ListIterator<List<T>, true>			const_iterator;
	typedef ReverseIterator<const_iterator>		const_reverse_iterator;

private:
	/**
	 * Attributes
	 */
	node_base_type m_root;
	size_type m_size;

public:
	/**
	 * Constructors & Destructors
	 */
	explicit
	List()
		: m_size(0)
	{
		this->initRoot();
	}

	explicit
	List(
		size_type n,
		const value_type & val = value_type()
	)
		: m_size(0)
	{
		this->initRoot();

		while (this->size() < n)
			this->push_back(val);
	}

	template<
		typename InputIterator
	>
	List(
		InputIterator first,
		InputIterator last,
		typename ft::enable_if<ft::is_iterable<typename InputIterator::iterator_type>::value, void>::type* = NULL
	)
		: m_size(0)
	{
		this->initRoot();

		while (first != last)
			this->push_back(*first++);
	}

	List(
		const List & other
	)
		: m_size(0)
	{
		this->initRoot();
		this->operator=(other);
	}

	~List()
	{
		this->clear();
	}

	List &
	operator=(
		const List & other
	)
	{
		if (this == &other)
			return *this;

		List tmp = List(other.begin(), other.end());

		this->swap(tmp);

		return *this;
	}

	/**
	 * Iterators
	 */
	iterator
	begin()
	{
		return iterator(this->m_root.next);
	}

	const_iterator
	begin() const
	{
		return const_iterator(this->m_root.next);
	}

	iterator
	end()
	{
		return iterator(this->m_root.prev->next);
	}

	const_iterator
	end() const
	{
		return const_iterator(this->m_root.prev->next);
	}

	reverse_iterator
	rbegin()
	{
		return reverse_iterator(this->end());
	}

	const_reverse_iterator
	rbegin() const
	{
		return const_reverse_iterator(this->end());
	}

	reverse_iterator
	rend()
	{
		return reverse_iterator(this->begin());
	}

	const_reverse_iterator
	rend() const
	{
		return const_reverse_iterator(this->begin());
	}

	/**
	 * Capacity
	 */
	bool
	empty() const
	{
		return this->size() == 0;
	}

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

	/**
	 * Element Access
	 */
	reference
	front()
	{
		return *this->begin();
	}

	const_reference
	front() const
	{
		return *this->begin();
	}

	reference
	back()
	{
		iterator tmp = this->end();
		--tmp;
		return *tmp;
	}

	const_reference
	back() const
	{
		const_iterator tmp = this->end();
		--tmp;
		return *tmp;
	}

	/**
	 * Modifiers
	 */
	template<
		typename InputIterator
	>
	typename ft::enable_if<ft::is_iterable<typename InputIterator::iterator_type>::value, void>::type
	assign(
		InputIterator first,
		InputIterator last
	)
	{
		List tmp = List(first, last);

		this->swap(tmp);
	}

	void
	assign(
		size_type n,
		const value_type & val
	)
	{
		List tmp = List(n, val);

		this->swap(tmp);
	}

	void
	push_front(
		const value_type & val
	)
	{
		this->insert(this->begin(), val);
	}

	void
	pop_front()
	{
		this->erase(this->begin());
	}

	void
	push_back (
		const value_type & val
	)
	{
		this->insert(this->end(), val);
	}

	void
	pop_back()
	{
		this->erase(--this->end());
	}

	iterator
	insert(
		iterator position,
		const value_type & val
	)
	{
		this->checkSize(1);

		this->linkNode(position, this->createNode(val));

		this->m_size += 1;

		return position;
	}

	void
	insert(
		iterator position,
		size_type n,
		const value_type & val
	)
	{
		List tmp = List(n, val);

		this->splice(position, tmp);
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
		List tmp = List(first, last);

		this->splice(position, tmp);
	}

	iterator
	erase(
		iterator position
	)
	{
		iterator it = position;
		++position;

		this->deleteNode(static_cast<node_pointer>(this->unlinkNode(it.m_current)));

		this->m_size -= 1;

		return position;
	}

	iterator
	erase(
		iterator first,
		iterator last
	)
	{
		while (first != last)
			first = this->erase(first);

		return last;
	}

	void
	swap(
		List & other
	)
	{
		List tmp = List();

		tmp.splice(tmp.begin(), *this);
		this->splice(this->begin(), other);
		other.splice(other.begin(), tmp);
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
	clear()
	{
		this->erase(this->begin(), this->end());
	}

	/**
	 * Operations
	 */
	void
	splice(
		iterator position,
		List & other
	)
	{
		this->splice(position, other, other.begin(), other.end());
	}

	void
	splice(
		iterator position,
		List & other,
		iterator i
	)
	{
		iterator next = i;
		++next;
		this->splice(position, other, i, next);
	}

	void
	splice(
		iterator position,
		List & other,
		iterator first,
		iterator last
	)
	{
		if (first == last)
			return ;

		size_type n = 0;

		if (first == other.begin() && last == other.end())
		{
			n = other.size();
		}
		else
		{
			for (iterator it = first; it != last; ++it)
				++n;
		}

		this->checkSize(n);

		node_base_pointer tmp = position.m_current->prev;

		position.m_current->prev->next = first.m_current;
		position.m_current->prev = last.m_current->prev;

		last.m_current->prev->next = position.m_current;
		last.m_current->prev = first.m_current->prev;

		first.m_current->prev->next = last.m_current;
		first.m_current->prev = tmp;

		other.m_size -= n;
		this->m_size += n;
	}

	void
	remove(
		const value_type & val
	)
	{
		iterator it = this->begin();
		iterator current;

		while (it != this->end())
		{
			current = it++;
			if (*current == val)
				this->erase(current);
		}
	}

	template<
		typename Predicate
	>
	void
	remove_if(
		Predicate pred
	)
	{
		iterator it = this->begin();
		iterator current;

		while (it != this->end())
		{
			current = it++;
			if (pred(*current))
				this->erase(current);
		}
	}

	void
	unique()
	{
		if (this->size() < 2)
			return ;

		iterator it = this->begin();
		iterator next = it;

		while (++next != this->end())
		{
			if (*it == *next)
				this->erase(next);
			else
				it = next;
			next = it;
		}
	}

	template<
		typename BinaryPredicate
	>
	void
	unique(
		BinaryPredicate pred
	)
	{
		if (this->size() < 2)
			return ;

		iterator it = this->begin();
		iterator next = it;

		while (++next != this->end())
		{
			if (pred(*it, *next))
				this->erase(next);
			else
				it = next;
			next = it;
		}
	}

	void
	merge(
		List & other
	)
	{
		this->merge(other, std::less<value_type>());
	}

	template<
		typename Compare
	>
	void
	merge(
		List & other,
		Compare comp
	)
	{
		if (&other == this)
			return ;

		this->checkSize(other.size());

		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (!other.empty() && comp(other.front(), *it))
				this->splice(it, other, other.begin());
		}

		this->splice(this->end(), other);
	}

	void
	sort()
	{
		this->sort(std::less<value_type>());
	}

	template<
		typename Compare
	>
	void
	sort(
		Compare comp
	)
	{
		if(this->size() < 2)
			return ;

		node_base_pointer node;

		for (iterator it_a = this->begin(); it_a != --this->end(); ++it_a)
		{
			for (iterator it_b = it_a; it_b != this->end(); ++it_b)
			{
				if (comp(*it_b, *it_a))
				{
					node = this->unlinkNode(it_b.m_current);
					this->linkNode(it_a, node);

					it_a = this->begin();
					break;
				}
			}
		}
	}

	void
	reverse()
	{
		node_base_pointer tmp;
		node_base_pointer current = this->m_root.next;

		this->m_root.next = this->m_root.prev;
		this->m_root.prev = current;

		while (current != &this->m_root)
		{
			tmp = current->prev;

			current->prev = current->next;
			current->next = tmp;

			current = current->prev;
		}
	}

private:
	/**
	 * Private methods
	 */
	void
	checkSize(
		size_type n
	)
	{
		if (n > this->max_size() || this->size() > this->max_size() - n)
			throw std::runtime_error("List : Maximum size exceeded.");
	}

	void
	initRoot()
	{
		this->m_root.prev = &this->m_root;
		this->m_root.next = &this->m_root;
	}

	node_pointer
	createNode(
		const value_type & val
	)
	{
		node_pointer node = new node_type();

		::new (&node->data) value_type(val);

		node->next = NULL;
		node->prev = NULL;

		return node;
	}

	node_base_pointer
	linkNode(
		iterator position,
		node_base_pointer node
	)
	{
		node->prev = position.m_current->prev;
		node->next = position.m_current;
		position.m_current->prev->next = node;
		position.m_current->prev = node;

		return node;
	}

	node_base_pointer
	unlinkNode(
		node_base_pointer node
	)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;

		return node;
	}

	void
	deleteNode(
		node_pointer node
	)
	{
		// node->data.~value_type();

		delete node;
	}

}; // End - List

/**
 * Relational Operators
 */
template<
	typename T
>
bool
operator==(
	const List<T> & x,
	const List<T> & y
)
{
	typedef typename List<T>::const_iterator c_i;

	if (x.size() != y.size())
		return false;

	c_i it_x = x.begin();
	c_i it_y = y.begin();
	c_i end_x = x.end();
	c_i end_y = y.end();

	while (
		it_x != end_x &&
		it_y != end_y &&
		*it_x == *it_y
	)
	{
		++it_x;
		++it_y;
	}

	return it_x == end_x && it_y == end_y;
}

template<
	typename T
>
bool
operator!=(
	const List<T> & x,
	const List<T> & y
)
{
	return !(x == y);
}

template<
	typename T
>
bool
operator<(
	const List<T> & x,
	const List<T> & y
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
	const List<T> & x,
	const List<T> & y
)
{
	return !(y < x);
}

template<
	typename T
>
bool
operator>(
	const List<T> & x,
	const List<T> & y
)
{
	return y < x;
}

template<
	typename T
>
bool
operator>=(
	const List<T> & x,
	const List<T> & y
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
	List<T> & x,
	List<T> & y
)
{
	x.swap(y);
}

}; // End - Namespace

#endif