#ifndef MAP_HPP
# define MAP_HPP

# include <memory>

# include "Utils.hpp"
# include "MapIterator.hpp"
# include "ReverseIterator.hpp"

namespace ft
{
/**
 * Map
 */
template<
	typename K, // Key
	typename M, // Mapped
	typename C = std::less<K> // Compare
>
class Map
{
public:
	/**
	 * Types
	 */
	typedef K	key_type;
	typedef M	mapped_type;
	typedef C	key_compare;

	typedef std::pair<const key_type, mapped_type> 		value_type;

private:
	typedef MapBaseNode				node_base_type;
	typedef MapNode<value_type>		node_type;
	typedef node_base_type *		node_base_pointer;
	typedef node_type *				node_pointer;

public:
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;

	typedef value_type *			pointer;
	typedef value_type &			reference;
	typedef value_type const *		const_pointer;
	typedef value_type const &		const_reference;

	typedef MapIterator<Map<K, M, C> >		iterator;
	typedef ReverseIterator<iterator>		reverse_iterator;
	typedef MapIterator<Map<K, M, C>, true>	const_iterator;
	typedef ReverseIterator<const_iterator>	const_reverse_iterator;

	// Nested class
	class value_compare
			: public std::binary_function<value_type, value_type, bool>
	{
	public:
		C	m_comp;

		value_compare(C comp)
			: m_comp(comp)
		{
		}

	public:
		bool operator()(const value_type & x, const value_type & y) const
		{
			return this->m_comp(x.first, y.first);
		}
	}; // End - Nested class

private:
	/**
	 * Attributes
	 */
	node_base_type		m_root;
	node_base_pointer	m_first;
	node_base_pointer	m_last;
	size_type			m_size;
	const key_compare	m_comp;

public:
	/**
	 * Constructors & Destructors
	 */
	explicit
	Map(
		const key_compare & comp = key_compare()
	)
		: m_size(0)
		, m_comp(comp)
	{
		this->initRoot();
	}

	template<
		typename InputIterator
	>
	Map(
		InputIterator first,
		InputIterator last,
		const key_compare & comp = key_compare()
	)
		: m_size(0)
		, m_comp(comp)
	{
		this->initRoot();
		this->insert(first, last);
	}

	Map(
		const Map & other
	)
		: m_size(0)
		, m_comp(other.m_comp)
	{
		this->initRoot();
		this->operator=(other);
	}

	~Map()
	{
		this->clear();
	}

	Map &
	operator=(const Map & other)
	{
		if (this == &other)
			return *this;

		Map tmp = Map(other.begin(), other.end(), this->key_comp());

		this->swap(tmp);

		return *this;
	}

	/**
	 * Iterators
	 */
	iterator
	begin()
	{
		return iterator(this->m_first);
	}

	const_iterator
	begin() const
	{
		return const_iterator(this->m_first);
	}

	iterator
	end()
	{
		return iterator(this->m_root.right);
	}

	const_iterator
	end() const
	{
		return const_iterator(this->m_root.right);
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
	mapped_type &
	operator[](
		const key_type & k
	)
	{
		iterator it = this->lower_bound(k);

		if (it == this->end() || this->key_comp()(k, (*it).first))
			it = this->insert(it, value_type(k, mapped_type()));
		return (*it).second;
	}

	/**
	 * Modifiers
	 */
	std::pair<
		iterator,
		bool
	>
	insert(
		const value_type & val
	)
	{
		size_type exist = this->count(val.first);

		return std::make_pair(this->insert(this->begin(), val), !exist);
	}

	iterator
	insert(
		iterator position,
		const value_type & val
	)
	{
		this->checkSize(1);

		(void) position;

		iterator found = this->find(val.first);

		if (found != this->end())
			return found;

		// Create node
		node_pointer node = new node_type();
		::new (&node->data) value_type(val.first, val.second);
		node->parent = NULL;
		node->left = NULL;
		node->right = NULL;

		// Set node parent
		node_base_pointer prev = &this->m_root;
		node_base_pointer current = prev->left;

		while (current && current != &this->m_root)
		{
			prev = current;
			if (this->key_comp()(val.first, static_cast<node_pointer>(current)->data.first))
				current = current->left;
			else
				current = current->right;
		}

		node->parent = prev;

		// Set parent child
		if (prev == &this->m_root || this->key_comp()(val.first, static_cast<node_pointer>(prev)->data.first))
			prev->left = node;
		else
			prev->right = node;

		// Set first / last
		if (node->parent == this->m_first && this->m_first->left == node)
		{
			this->m_first = node;
		}
		if (node->parent == this->m_last && (this->m_last->right == node || this->m_last == &this->m_root))
		{
			this->m_last = node;
			this->m_root.parent = this->m_last;
		}

		this->m_size += 1;

		return iterator(node);
	}

	template<
		typename InputIterator
	>
	typename ft::enable_if<ft::is_iterable<typename InputIterator::iterator_type>::value, void>::type
	insert(
		InputIterator first,
		InputIterator last
	)
	{
		while (first != last)
		{
			this->insert(this->begin(), *first);
			++first;
		}
	}

	void
	erase(
		iterator position
	)
	{
		node_pointer node = static_cast<node_pointer>(position.m_current);

		// No child
		if (!node->left && !node->right)
		{
			if (node->parent->left == node)
				node->parent->left = NULL;
			else
				node->parent->right = NULL;
		}
		// Two children
		else if (node->left && node->right)
		{
			node_base_pointer min_right = (++position).m_current;

			// Set min_right parent child
			if (min_right->parent == node)
				min_right->parent->right = min_right->right;
			else
			{
				min_right->parent->left = min_right->right;

				if (min_right->right)
					min_right->right->parent = min_right->parent;
			}

			// Set min_right children & parent
			min_right->parent = node->parent;
			min_right->left = node->left;
			min_right->right = node->right;

			// Set node children parent
			node->left->parent = min_right;

			if (node->right)
				node->right->parent = min_right;

			// Set node parent child
			if (node->parent->left == node)
				node->parent->left = min_right;
			else
				node->parent->right = min_right;
		}
		// One child
		else
		{
			node_base_pointer child = node->left;

			if (!child)
				child = node->right;

			if (node->parent->left == node)
				node->parent->left = child;
			else
				node->parent->right = child;

			child->parent = node->parent;
		}

		// Set first / last
		if (node == this->m_first)
		{
			this->m_first = node->parent;
		}
		if (node == this->m_last)
		{
			this->m_last = node->parent;
			this->m_root.parent = node->parent;
		}

		this->m_size -= 1;

		// delete node->data;
		delete node;
	}

	size_type
	erase(
		const key_type & k
	)
	{
		iterator found = this->find(k);

		if (found != this->end())
		{
			this->erase(found);
			return (1);
		}

		return (0);
	}

	void
	erase(
		iterator first,
		iterator last
	)
	{
		while (first != last)
			this->erase(first++);
	}

	void
	swap(
		Map & other
	)
	{
		// Size
		size_type tmp_size = other.m_size;

		other.m_size = this->m_size;
		this->m_size = tmp_size;

		// Parents
		node_base_pointer tmp_parent = this->m_root.parent;

		if (other.m_root.parent != &other.m_root)
			this->m_root.parent = other.m_root.parent;
		if (tmp_parent != &this->m_root)
			other.m_root.parent = tmp_parent;

		// Children and Children Parents
		node_base_pointer tmp_child = other.m_root.left;

		if (other.m_root.left != &other.m_root)
			other.m_root.left->parent = &this->m_root;

		if (this->m_root.left != &this->m_root)
			other.m_root.left = this->m_root.left;
		else
			other.m_root.left = &other.m_root;

		if (this->m_root.left != &this->m_root)
			this->m_root.left->parent = &other.m_root;

		if (tmp_child != &other.m_root)
			this->m_root.left = tmp_child;
		else
			this->m_root.left = &this->m_root;

		// First / Last
		node_base_pointer tmp_first = this->m_first;
		node_base_pointer tmp_last = this->m_last;

		if (other.m_first != &other.m_root)
		{
			this->m_first = other.m_first;
			this->m_last = other.m_last;
		}
		else
		{
			this->m_first = &this->m_root;
			this->m_last = &this->m_root;
		}

		if (tmp_first != &this->m_root)
		{
			other.m_first = tmp_first;
			other.m_last = tmp_last;
		}
		else
		{
			other.m_first = &other.m_root;
			other.m_last = &other.m_root;
		}

	}

	void
	clear()
	{
		this->erase(this->begin(), this->end());
	}

	/**
	 * Observers
	 */
	key_compare
	key_comp() const
	{
		return this->m_comp;
	}

	value_compare
	value_comp() const
	{
		return value_compare(this->key_comp());
	}

	/**
	 * Operations
	 */
	iterator
	find(
		const key_type & k
	)
	{
		iterator it = this->begin();
		while (it != this->end() && (this->key_comp()(it->first, k) || this->key_comp()(k, it->first)))
			++it;

		return it;
	}

	const_iterator
	find(
		const key_type & k
	) const
	{
		const_iterator it = this->begin();

		while (it != this->end() && (this->key_comp()(it->first, k) || this->key_comp()(k, it->first)))
			++it;

		return it;
	}

	size_type
	count(
		const key_type & k
	) const
	{
		return this->find(k) == this->end() ? 0 : 1;
	}

	iterator
	lower_bound(
		const key_type & k
	)
	{
		iterator it = this->begin();

		while (it != this->end() && this->key_comp()(it->first, k))
			++it;

		return it;
	}

	const_iterator
	lower_bound(
		const key_type & k
	) const
	{
		const_iterator it = this->begin();

		while (it != this->end() && this->key_comp()(it->first, k))
			++it;

		return it;
	}

	iterator
	upper_bound(
		const key_type & k
	)
	{
		iterator it = this->begin();

		while (it != this->end() && !this->key_comp()(k, it->first))
			++it;

		return it;
	}

	const_iterator
	upper_bound(
		const key_type & k
	) const
	{

		const_iterator it = this->begin();

		while (it != this->end() && !this->key_comp()(k, it->first))
			++it;

		return it;
	}

	std::pair<
		const_iterator,
		const_iterator
	>
	equal_range(
		const key_type & k
	) const
	{
		return std::make_pair(this->lower_bound(k), this->upper_bound(k));
	}

	std::pair<
		iterator,
		iterator
	>
	equal_range(
		const key_type & k
	)
	{
		return std::make_pair(this->lower_bound(k), this->upper_bound(k));
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
			throw std::runtime_error("Map : Maximum size exceeded.");
	}

	void
	initRoot()
	{
		this->m_root.parent = &m_root;
		this->m_root.left = &m_root;
		this->m_root.right = &m_root;

		this->m_first = &m_root;
		this->m_last = &m_root;
	}

}; // End - Map

}; // End - Namespace

#endif