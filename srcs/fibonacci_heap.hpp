#ifndef FIBONACCI_HEAP_HPP
#define FIBONACCI_HEAP_HPP

#include <cstddef> // size_t, ptrdiff_t
#include <memory> // std::allocator

#include "functional.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "stdexcept.hpp"
#include "type_traits.hpp"

#include "queue.hpp"
#include "vector.hpp"

namespace ft
{

// Forward declaration
template<
	typename K,
	typename T = K,
	typename KeyOfValue = ft::identity< T >,
	typename Compare = ft::less< K >,
	typename Allocator = std::allocator< T >
>
class fibonacci_heap;

namespace
{

/**
 * FibonacciHeapNodeBase
 */
struct _fibonacci_heap_node_base
{
	// Attribute ---------------------------------------------------------------
public:
	_fibonacci_heap_node_base * prev;
	_fibonacci_heap_node_base * next;

	_fibonacci_heap_node_base * parent;
	_fibonacci_heap_node_base * children;

	unsigned int degree;
	bool is_marked;

	// Method ------------------------------------------------------------------
public:
	void mark()   { this->is_marked = true; }
	void unmark() { this->is_marked = false; }

	bool is_first() const { return ( this->parent->children == this ); }

	bool has_parent()   const { return ( this->parent   != nullptr ); }
	bool has_children() const { return ( this->children != nullptr ); }

	_fibonacci_heap_node_base *
	link(
		_fibonacci_heap_node_base * first,
		_fibonacci_heap_node_base * last
	)
	{
		first->prev = this->prev;
		last->next  = this;

		this->prev->next = first;
		this->prev       = last;

		return this;
	}

	_fibonacci_heap_node_base *
	unlink()
	{
		_fibonacci_heap_node_base * next = this->next;

		this->next->prev = this->prev;
		this->prev->next = this->next;

		this->next = this;
		this->prev = this;

		return ( ( next != this ) ? next : nullptr );
	}

	void
	push_child(
		_fibonacci_heap_node_base * child
	)
	{
		if ( this->children == nullptr )
		{
			this->children = child;
		}
		else
		{
			this->children->link(child, child);
		}

		child->parent = this;
		this->degree += 1;
	}
};

template<
	typename T
>
struct _fibonacci_heap_node
	: public _fibonacci_heap_node_base
{
	T data;
};

/**
 * FibonacciHeapIterator
 */
template<
	typename T,
	bool IsConst
>
class _fibonacci_heap_iterator
	: public ft::iterator<
		ft::bidirectional_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>
{
	// Type --------------------------------------------------------------------
private:
	typedef _fibonacci_heap_node_base  _node_base_type;
	typedef _fibonacci_heap_node< T >  _node_type;

	typedef ft::iterator<
		ft::bidirectional_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>                                               _self_base_type;
	typedef _fibonacci_heap_iterator< T, IsConst >  _self_type;

public:
	using typename _self_base_type::value_type;

	// Note: Force const to disable key modification, which would make the heap
	//   in an invalid state. Could also allow it, but then it would be the
	//   dev responsability to keep the keys safe.
	typedef T const *  pointer;
	typedef T const &  reference;

	// Attribute ---------------------------------------------------------------
private:
	_node_base_type * _top;
	_node_base_type * _node;

	// Constructor -------------------------------------------------------------
public:
	explicit
	_fibonacci_heap_iterator(
		_node_base_type * top = nullptr,
		_node_base_type * node = nullptr
	)
		: _top ( top )
		, _node( node )
	{
	}

	// Note: Convert non-const to const iterator
	template<
		typename _T
	>
	_fibonacci_heap_iterator(
		_fibonacci_heap_iterator< _T, false > const & other
	)
		: _top ( other._top )
		, _node( other._node )
	{
	}

	_fibonacci_heap_iterator(
		_self_type const & other
	)
		: _top ( other._top )
		, _node( other._node )
	{
	}

	// Operator ----------------------------------------------------------------
public:
	// - Access ------------------------
	reference
	operator*() const
	{
		return static_cast< _node_type * >( this->_node )->data;
	}

	pointer
	operator->() const
	{
		return ft::addressof( static_cast< _node_type * >( this->_node )->data );
	}

	// - Iterate -----------------------
	_self_type &
	operator++()
	{
		this->_increment();
		return *this;
	}

	_self_type
	operator++( int )
	{
		_self_type self = *this;
		this->_increment();
		return self;
	}

	_self_type &
	operator--()
	{
		this->_decrement();
		return *this;
	}

	_self_type
	operator--( int )
	{
		_self_type self = *this;
		this->_decrement();
		return self;
	}

private:
	// - Access ------------------------
	_node_base_type *
	_get_node() const
	{
		return this->_node;
	}

	// - Iterate -----------------------
	void
	_increment()
	{
		if ( this->_node->has_children() )
		{
			this->_node = this->_node->children;
			return ;
		}

		this->_node = this->_node->next;

		if ( this->_node == this->_top )
		{
			this->_node = nullptr;
			return ;
		}

		while ( this->_node->has_parent() && this->_node == this->_node->parent->children )
		{
			this->_node = this->_node->parent->next;
		}
	}

	void
	_decrement()
	{
		if ( this->_node == nullptr )
		{
			this->_node = this->_top->prev;

			while ( this->_node->has_children() )
			{
				this->_node = this->_node->children->prev;
			}

			return ;
		}

		if ( this->_node == this->_top )
		{
			this->_node = nullptr;
			return ;
		}

		if ( this->_node->has_parent() && this->_node == this->_node->parent->children )
		{
			this->_node = this->_node->parent;
			return ;
		}

		this->_node = this->_node->prev;

		if ( this->_node->has_children() )
		{
			this->_node = this->_node->children->prev;

			while ( this->_node->has_children() )
			{
				this->_node = this->_node->children->prev;
			}
		}
	}

	// Friend ------------------------------------------------------------------
public:
	// - Class -------------------------
	friend class _fibonacci_heap_iterator< T, ! IsConst >;

	template<
		typename _Key,
		typename _Value,
		typename _KeyOfValue,
		typename _Compare,
		typename _Allocator
	>
	friend class ft::fibonacci_heap;

	// - Relational Operator -----------
	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_fibonacci_heap_iterator< _T, _IsConst > const & x,
		_fibonacci_heap_iterator< _T, _IsConst > const & y
	);

	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_fibonacci_heap_iterator< _T,   _IsConst > const & x,
		_fibonacci_heap_iterator< _T, ! _IsConst > const & y
	);

}; // class _fibonacci_heap_iterator

// - Relational Operator -------------------------------------------------------
// -- Same Constness -------------------
template<
	typename T,
	bool IsConst
>
bool
operator==(
	_fibonacci_heap_iterator< T, IsConst > const & x,
	_fibonacci_heap_iterator< T, IsConst > const & y
)
{
	return ( x._get_node() == y._get_node() );
}

template<
	typename T,
	bool IsConst
>
bool
operator!=(
	_fibonacci_heap_iterator< T, IsConst > const & x,
	_fibonacci_heap_iterator< T, IsConst > const & y
)
{
	return ( ! ( x == y ) );
}

// -- Different Constness --------------
template<
	typename T,
	bool IsConst
>
bool
operator==(
	_fibonacci_heap_iterator< T,   IsConst > const & x,
	_fibonacci_heap_iterator< T, ! IsConst > const & y
)
{
	return ( x._get_node() == y._get_node() );
}

template<
	typename T,
	bool IsConst
>
bool
operator!=(
	_fibonacci_heap_iterator< T,   IsConst > const & x,
	_fibonacci_heap_iterator< T, ! IsConst > const & y
)
{
	return ( ! ( x == y ) );
}

/**
 * FibonacciHeapBase
 */
template<
	typename T,
	typename Allocator
>
class _fibonacci_heap_base
{
	// Type --------------------------------------------------------------------
private:
	typedef _fibonacci_heap_base< T, Allocator >  _self_type;

public:
	typedef Allocator  allocator_type;

	typedef size_t     size_type;
	typedef ptrdiff_t  difference_type;

	typedef T                   value_type;
	typedef value_type &        reference;
	typedef value_type const &  const_reference;
	typedef value_type *        pointer;
	typedef value_type const *  const_pointer;

protected:
	typedef _fibonacci_heap_node_base  _node_base_type;
	typedef _fibonacci_heap_node< T >  _node_type;

private:
	typedef typename Allocator::template rebind< _node_type >::other  _node_allocator_type;

	// Attribute ---------------------------------------------------------------
private:
	allocator_type _allocator;
	_node_allocator_type _node_allocator;

	// Constructor -------------------------------------------------------------
protected:
	_fibonacci_heap_base(
		allocator_type const & allocator = allocator_type()
	)
		: _allocator(allocator)
		, _node_allocator(allocator)
	{
	}

	// Destructor --------------------------------------------------------------
protected:
	~_fibonacci_heap_base()
	{
	}

	// Method ------------------------------------------------------------------
protected:
	// - Observer ----------------------
	allocator_type
	get_allocator() const
	{
		return this->_allocator;
	}

	// - Allocation --------------------
	_node_type *
	_allocate_node()
	{
		return this->_node_allocator.allocate(1);
	}

	void
	_deallocate_node(
		_node_type * node
	)
	{
		this->_node_allocator.deallocate(node, 1);
	}

	void
	_construct(
		_node_type * node,
		value_type const & value
	)
	{
		this->_allocator.construct(ft::addressof(node->data), value);
	}

	void
	_destroy(
		_node_type * node
	)
	{
		this->_allocator.destroy(ft::addressof(node->data));
	}

}; // class _fibonacci_heap_base

} // namespace

/**
 * FibonacciHeap
 *
 * @ref https://en.wikipedia.org/wiki/Fibonacci_heap
 * @ref https://www.cs.princeton.edu/~wayne/cs423/fibonacci/FibonacciHeapAlgorithm.html
 * @ref https://www.cs.princeton.edu/~wayne/teaching/fibonacci-heap.pdf
 */
template<
	typename K,
	typename T,
	typename KeyOfValue,
	typename Compare,
	typename Allocator
>
class fibonacci_heap
	: public _fibonacci_heap_base< T, Allocator >
{
	// Type --------------------------------------------------------------------
private:
	typedef _fibonacci_heap_base< T, Allocator >                    _self_base_type;
	typedef fibonacci_heap< K, T, KeyOfValue, Compare, Allocator >  _self_type;

public:
	using typename _self_base_type::allocator_type;

	using typename _self_base_type::size_type;
	using typename _self_base_type::difference_type;

	typedef K  key_type;

	using typename _self_base_type::value_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::const_reference;
	using typename _self_base_type::pointer;
	using typename _self_base_type::const_pointer;

	typedef KeyOfValue  key_of_value_type;
	typedef Compare     key_compare;

	typedef _fibonacci_heap_iterator< value_type, false >  iterator;
	typedef _fibonacci_heap_iterator< value_type, true >   const_iterator;
	typedef ft::reverse_iterator< iterator >               reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >         const_reverse_iterator;

private:
	using typename _self_base_type::_node_base_type;
	using typename _self_base_type::_node_type;

	// Attribute ---------------------------------------------------------------
private:
	key_compare _compare;

	_node_base_type * _top;
	size_type _size;

	// Constructor -------------------------------------------------------------
public:
	// - Default -----------------------
	/**
	 * Default constructor, initializing an empty heap.
	 *
	 * @param compare The function object used to compare keys
	 * @param allocator The allocator used for memory allocation
	 *
	 * @complexity Constant - O(1)
	 */
	explicit
	fibonacci_heap(
		key_compare const & compare = key_compare(),
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type(allocator)
		, _compare(compare)
		, _top(nullptr)
		, _size(0)
	{
	}

	// - Range -------------------------
	/**
	 * Range constructor, initializing the heap with the copied values from [`first` to `last`).
	 *
	 * @param first An iterator pointing to the first element to be copied
	 * @param last An iterator pointing past the last element to be copied
	 * @param compare The function object used to compare keys
	 * @param allocator The allocator used for memory allocation
	 *
	 * @complexity Linear - O(n) with n = distance(first, last)
	 */
	template<
		typename _InputIterator
	>
	fibonacci_heap(
		_InputIterator first,
		_InputIterator last,
		key_compare const & compare = key_compare(),
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type(allocator)
		, _compare(compare)
		, _top(nullptr)
		, _size(0)
	{
		while ( first != last )
		{
			this->push(*first);
			++first;
		}
	}

	// - Copy --------------------------
	/**
	 * Copy constructor, initializing the heap with values from `other`.
	 *
	 * @param other The fibonacci_heap to copy
	 *
	 * @complexity Linear - O(n) with n = other.size()
	 */
	fibonacci_heap(
		_self_type const & other
	)
		: _self_base_type(other.get_allocator())
		, _compare(other.key_comp())
		, _top(nullptr)
		, _size(0)
	{
		*this = other;
	}

	// Destructor --------------------------------------------------------------
public:
	/**
	 * Call each element destructor before destructing heap itself.
	 *
	 * @complexity Linear - O(n) with n = heap.size()
	 */
	~fibonacci_heap()
	{
		this->clear();
	}

	// Operator ----------------------------------------------------------------
public:
	/**
	 * Clear heap content, then copy `other` ones.
	 *
	 * @return The heap
	 *
	 * @complexity Linear - O(n) with n = heap.size()
	 */
	_self_type &
	operator=(
		_self_type const & other
	)
	{
		if ( this != &other )
		{
			this->_delete_tree( static_cast< _node_type * >( this->_top ) );

			this->_compare = other._compare;
			this->_top = this->_copy_tree( static_cast< _node_type const * >( other._top ) );
			this->_size = other._size;
		}

		return *this;
	}

	// Method ------------------------------------------------------------------
public:
	// - Observer ----------------------
	/**
	 * Get the allocator.
	 *
	 * @return The heap allocator
	 *
	 * @complexity Constant - O(1)
	 */
	allocator_type
	get_allocator() const
	{
		return _self_base_type::get_allocator();
	}

	/**
	 * Get the key compare function object.
	 *
	 * @return The key compare function object
	 *
	 * @complexity Constant - O(1)
	 */
	key_compare
	key_comp() const
	{
		return this->_compare;
	}

	// - Iterator ----------------------
	iterator               begin()        { return iterator( this->_top, this->_top ); }
	const_iterator         begin()  const { return const_iterator( this->_top, this->_top ); }
	iterator               end()          { return iterator( this->_top ); }
	const_iterator         end()    const { return const_iterator( this->_top ); }
	reverse_iterator       rbegin()       { return reverse_iterator( this->end() ); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator( this->end() ); }
	reverse_iterator       rend()         { return reverse_iterator( this->begin() ); }
	const_reverse_iterator rend()   const { return const_reverse_iterator( this->begin() ); }

	// - Capacity ----------------------
	/**
	 * Get the number of elements in the heap.
	 *
	 * @return Number of elements
	 *
	 * @complexity Constant - O(1)
	 */
	size_type
	size() const
	{
		return this->_size;
	}

	/**
	 * Get the maximum number of elements the heap should / can contains.
	 *
	 * @return Maximum number of elements
	 *
	 * @complexity Constant - O(1)
	 */
	size_type
	max_size() const
	{
		return ( size_type(-1) / sizeof(_node_type) / 2 );
	}

	/**
	 * Check whether the heap is empty.
	 *
	 * @return `true` if the heap is empty, `false` otherwise
	 *
	 * @complexity Constant - O(1)
	 */
	bool
	empty() const
	{
		return ( this->size() == 0 );
	}

	// - Access ------------------------
	/**
	 * Get the min-element.
	 *
	 * @return Min-element of the heap
	 *
	 * @complexity Constant - O(1)
	 */
	const_reference
	top() const
	{
		return static_cast< _node_type * >( this->_top )->data;
	}

	// - Modifier ----------------------
	/**
	 * Add a value to the heap.
	 *
	 * @complexity Constant - O(1)
	 * @iterator Nothing is invalidated
	 */
	void
	push(
		value_type const & value
	)
	{
		_node_base_type * top = this->_top;
		_node_base_type * node = this->_create_node( value );

		if ( top != nullptr )
		{
			top->link( node, node );

			if ( this->_compare(
				this->_get_key_of_value( static_cast< _node_type * >( top )->data ),
				this->_get_key_of_value( static_cast< _node_type * >( node )->data )
			) )
			{
				node = top;
			}
		}

		this->_top = node;
		this->_size += 1;
	}

	/**
	 * Remove the min-element.
	 *
	 * @complexity Logarithmic -  O(log(n)) with n = heap.size()
	 * @iterator Invalidate heap.begin()
	 */
	void
	pop()
	{
		_node_base_type * top = this->_top;

		if ( top->children != nullptr )
		{
			_node_base_type * first = top->children;
			_node_base_type * last = first->prev;
			_node_base_type * current = first;

			do
			{
				current->parent = nullptr;
				current = current->next;
			}
			while ( current != first );

			top->link( first, last );
		}

		this->_top = top->unlink();
		this->_delete_node( static_cast< _node_type * >( top ) );

		if ( this->_top != nullptr )
		{
			this->_consolidate();
		}

		this->_size -= 1;
	}

	/**
	 * Remove all the elements.
	 *
	 * @complexity Linear - O(n) with n = heap.size()
	 * @iterator Invalidate all iterator
	 */
	void
	clear()
	{
		this->_delete_tree( static_cast< _node_type * >( this->_top ) );

		this->_top = nullptr;
		this->_size = 0;
	}

	/**
	 * Swap the elements.
	 *
	 * @param other Other heap to swap with
	 *
	 * @complexity Constant - O(1)
	 * @iterator Invalidate all iterator
	 */
	void
	swap(
		_self_type & other
	)
	{
		ft::swap(this->_top, other._top);
		ft::swap(this->_size, other._size);
		ft::swap(this->_compare, other._compare);
	}

	// - Operation ---------------------
	/**
	 * Search for a specific value.
	 *
	 * @param value Value for search for
	 *
	 * @return Iterator pointing to the first equivalent value found
	 *
	 * @complexity Logarithmic - O(log(n)) with n = heap.size()
	 */
	iterator
	find(
		key_type const & key
	)
	{
		_node_base_type * node = this->_top;

		if ( this->empty() || this->_compare( key, this->_get_key_of_value( static_cast< _node_type * >( node )->data ) ) )
		{
			return this->end();
		}

		ft::queue< _node_base_type * > queue;
		queue.push( node );

		_node_base_type * next = node->next;

		while ( next != node )
		{
			if ( ! this->_compare( key, this->_get_key_of_value( static_cast< _node_type * >( next )->data ) ) )
			{
				queue.push( next );
			}

			next = next->next;
		}

		while ( ! queue.empty() )
		{
			node = queue.front();

			if ( ! this->_compare( this->_get_key_of_value( static_cast< _node_type * >( node )->data ), key ) )
			{
				return iterator( this->_top, node );
			}

			if ( node->has_children() )
			{
				_node_base_type * next = node->children;

				do
				{
					if ( ! this->_compare( key, this->_get_key_of_value( static_cast< _node_type * >( next )->data ) ) )
					{
						queue.push( next );
					}

					next = next->next;
				}
				while ( next != node->children );
			}

			queue.pop();
		}

		return this->end();
	}

	const_iterator
	find(
		key_type const & key
	) const
	{
		_node_base_type * node = this->_top;

		if ( this->empty() || this->_compare( key, this->_get_key_of_value( static_cast< _node_type * >( node )->data ) ) )
		{
			return this->end();
		}

		ft::queue< _node_base_type * > queue;
		queue.push( node );

		_node_base_type * next = node->next;

		while ( next != node )
		{
			if ( ! this->_compare( key, this->_get_key_of_value( static_cast< _node_type * >( next )->data ) ) )
			{
				queue.push( next );
			}

			next = next->next;
		}

		while ( ! queue.empty() )
		{
			node = queue.front();

			if ( ! this->_compare( this->_get_key_of_value( static_cast< _node_type * >( node )->data ), key ) )
			{
				return const_iterator( this->_top, node );
			}

			if ( node->has_children() )
			{
				_node_base_type * next = node->children;

				do
				{
					if ( ! this->_compare( key, this->_get_key_of_value( static_cast< _node_type * >( next )->data ) ) )
					{
						queue.push( next );
					}

					next = next->next;
				}
				while ( next != node->children );
			}

			queue.pop();
		}

		return this->end();
	}

	/**
	 * Decrease a value.
	 *
	 * @param node Iterator pointing to the value to decrease
	 * @param decrease Function object used to decrease the value
	 * @param key New value key
	 *
	 * @throw ft::out_of_range if new value key of greater than current one
	 * @throw `decrease` specific exception if failed
	 *
	 * @complexity Logarithmic - O(log(n)) with n = heap.size()
	 * @iterator Nothing is invalidated
	 */
	template<
		typename _DecreaseKey
	>
	void
	decrease_key(
		iterator element,
		key_type key,
		_DecreaseKey decrease
	)
	{
		_node_base_type * node = element._get_node();

		if ( this->_compare( this->_get_key_of_value( static_cast< _node_type * >( node )->data ), key ) )
		{
			throw ft::out_of_range("ft::fibonacci_heap::decrease_key : New key is greater than current one.");
		}

		decrease( static_cast< _node_type * >( node )->data, key );

		_node_base_type * parent = node->parent;

		if ( parent != nullptr && this->_compare( this->_get_key_of_value( static_cast< _node_type * >( node )->data ), key ) )
		{
			this->_cut( node, parent );
			this->_cascade_cut( parent );
		}

		if ( this->_compare(
				this->_get_key_of_value( static_cast< _node_type * >( node )->data ),
				this->_get_key_of_value( static_cast< _node_type * >( this->_top )->data )
		) )
		{
			this->_top = node;
		}
	}

	void
	decrease_key(
		iterator element,
		key_type key
	)
	{
		this->decrease_key( element, key, ft::assign_to< key_type >() );
	}

	/**
	 * Extract values from the `other` heap to add them into `this`.
	 *
	 * @param other The heap to merge
	 *
	 * @complexity Constant - O(1)
	 * @iterator Invalidate all iterator from `other`
	 */
	void
	merge(
		_self_type & other
	)
	{
		if ( other.empty() )
		{
			return ;
		}

		if ( this->empty() )
		{
			this->_top = other._top;
			this->_size = other._size;
		}
		else
		{
			_node_base_type * node = other._top;

			this->_top->link(node, node->prev);
			this->_size += other._size;

			if ( this->_compare(
				this->_get_key_of_value( static_cast< _node_type * >( node )->data ),
				this->_get_key_of_value( static_cast< _node_type * >( this->_top )->data )
			) )
			{
				this->_top = node;
			}
		}

		other._top = nullptr;
		other._size = 0;
	}

private:
	/**
	 * Get the `key` of a `value`.
	 *
	 * @param value The value to get the key from
	 *
	 * @return The key of the value
	 */
	key_type const &
	_get_key_of_value(
		value_type const & value
	) const
	{
		return key_of_value_type()( value );
	}

	/**
	 * Create a node with `value`.
	 *
	 * @param value The value to copy into the new node
	 *
	 * @return The created node
	 *
	 * @throw Alloctor specific exception if allocation failed
	 */
	_node_type *
	_create_node(
		value_type const & value
	)
	{
		_node_type * node = _self_base_type::_allocate_node();

		try
		{
			_self_base_type::_construct( node, value );
		}
		catch ( ... )
		{
			_self_base_type::_deallocate_node( node );

			throw ;
		}

		node->degree = 0;
		node->unmark();
		node->parent = nullptr;
		node->children = nullptr;
		node->prev = node;
		node->next = node;

		return node;
	}

	/**
	 * Delete a node, calling it's value destructor, then deallocate it.
	 *
	 * @param node The node to delete
	 */
	void
	_delete_node(
		_node_type * node
	)
	{
		_self_base_type::_destroy( node );
		_self_base_type::_deallocate_node( node );
	}

	/**
	 * Create a copy of a tree, including siblings and children.
	 *
	 * @param root Tree to copy
	 * @param parent Parent for the copied tree
	 *
	 * @return Copied tree
	 *
	 * @throw Alloctor specific exception if allocation failed
	 *
	 * @complexity Linear - O(n) with n = Tree size
	 */
	_node_type *
	_copy_tree(
		_node_type const * root,
		_node_base_type * parent = nullptr
	)
	{
		if ( root == nullptr )
		{
			return nullptr;
		}

		_node_type * copy = nullptr;
		_node_type const * next = root;

		do
		{
			try
			{
				_node_type * node = this->_create_node( next->data );

				node->is_marked = next->is_marked;
				node->degree = next->degree;
				node->parent = parent;

				if ( copy == nullptr )
				{
					copy = node;
				}
				else
				{
					copy->link( node, node );
				}

				node->children = this->_copy_tree( static_cast< _node_type * >( next->children ), node );
			}
			catch ( ... )
			{
				this->_delete_tree( copy );
				throw ;
			}

			next = static_cast< _node_type * >( next->next );
		}
		while ( next != root );

		return copy;
	}

	/**
	 * Delete a tree, including sibligns and children.
	 *
	 * @param root Tree to delete
	 *
	 * @complexity Linear - O(n) with n = Tree size
	 */
	void
	_delete_tree(
		_node_type * root
	)
	{
		_node_type * node = root;

		while ( node != nullptr )
		{
			_node_base_type * next = node->unlink();

			this->_delete_tree( static_cast< _node_type * >( node->children ) );
			this->_delete_node( node );

			node = static_cast< _node_type * >( next );
		}
	}

	/**
	 * Build min-tree.
	 *
	 * @complexity Logarithmic - O(log(n)) with n = this->size() overall
	 */
	void
	_consolidate()
	{
		typedef ft::vector< _node_base_type *, typename allocator_type::template rebind< _node_base_type * >::other >  CTN;

		#define LOG2( T, X )  ( 8 * sizeof(T) - __builtin_clzll((X)) - 1 )

		CTN roots( LOG2( size_type, this->size() ) + 1 );

		#undef LOG2

		_node_base_type * next = this->_top;

		do
		{
			_node_base_type * node = next;

			next = node->unlink();

			while ( roots[ node->degree ] != nullptr )
			{
				_node_base_type * root = roots[ node->degree ];

				if ( this->_compare(
					this->_get_key_of_value( static_cast< _node_type * >( root )->data ),
					this->_get_key_of_value( static_cast< _node_type * >( node )->data )
				) )
				{
					ft::swap( node, root );
				}

				roots[ node->degree ] = nullptr;

				node->push_child( root );
				root->unmark();
			}

			roots[ node->degree ] = node;
		}
		while ( next != nullptr );

		this->_top = nullptr;

		for ( typename CTN::size_type i = 0 ; i < roots.size() ; ++i )
		{
			if ( roots[ i ] == nullptr )
			{
				continue ;
			}

			_node_base_type * node = roots[ i ];

			if ( this->_top != nullptr )
			{
				this->_top->link( node, node );

				if ( this->_compare(
					this->_get_key_of_value( static_cast< _node_type * >( node )->data ),
					this->_get_key_of_value( static_cast< _node_type * >( this->_top )->data )
				) )
				{
					this->_top = node;
				}
			}
			else
			{
				this->_top = node;
			}
		}
	}

	/**
	 * Remove a `child` node from its `parent` children, then add this child as a heap root.
	 * Decreasing `parent` node degree by 1, and unmarking the `child`.
	 *
	 * @param child Child node to remove
	 * @param parent Parent node to remove child from
	 *
	 * @complexity Constant - O(1)
	 */
	void
	_cut(
		_node_base_type * child,
		_node_base_type * parent
	)
	{
		if ( child == child->next )
		{
			parent->children = nullptr;
		}
		else
		{
			child->prev->next = child->next;
			child->next->prev = child->prev;

			if ( parent->children == child )
			{
				parent->children = child->next;
			}
		}

		parent->degree -= 1;

		child->prev = this->_top->prev;
		child->next = this->_top;
		child->parent = nullptr;
		child->unmark();

		this->_top->prev->next = child;
		this->_top->prev = child;
	}

	/**
	 * Propagate a rebalance after a `_cut`.
	 *
	 * @param node Parent of the node that has been `_cut`
	 *
	 * @complexity Logarithmic - O(log(n)) with n = this->size() overall
	 */
	void
	_cascade_cut(
		_node_base_type * node
	)
	{
		_node_base_type * parent = node->parent;

		if ( parent == nullptr )
		{
			return ;
		}

		if ( node->is_marked )
		{
			this->_cut( node, parent );
			this->_cascade_cut( parent );
		}
		else
		{
			node->mark();
		}
	}

}; // class fibonacci_heap

} // namespace ft

#endif
