#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef> // size_t, ptrdiff_t
#include <memory> // std::allocator

#include "algorithm.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "type_traits.hpp"

namespace ft
{

// Forward Declaration to make it friend of _forward_list_iterator
template<
	typename T,
	typename Allocator = std::allocator< T >
>
class forward_list;

namespace
{

/**
 * ListNodeBase
 */
struct _forward_list_node_base
{
	_forward_list_node_base * next;
};

/**
 * ListNode
 */
template<
	typename T
>
struct _forward_list_node
	: public _forward_list_node_base
{
	T data;
};

/**
 * FowardListIterator
 */
template<
	typename T,
	bool IsConst
>
class _forward_list_iterator
	: public ft::iterator<
		ft::forward_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>
{
	// Type --------------------------------------------------------------------
private:
	typedef _forward_list_node_base  _node_base_type;
	typedef _forward_list_node< T >  _node_type;

	typedef ft::iterator<
		ft::forward_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>                                             _self_base_type;
	typedef _forward_list_iterator< T, IsConst >  _self_type;

public:
	using typename _self_base_type::value_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::pointer;

	// Attribute ---------------------------------------------------------------
private:
	_node_base_type * _node;

	// Constructor -------------------------------------------------------------
public:
	_forward_list_iterator(
		_node_base_type * node = nullptr
	)
		: _node( node )
	{
	}

	// Note: Convert non-const to const iterator
	template<
		typename _T
	>
	_forward_list_iterator(
		_forward_list_iterator< _T, false > const & other
	)
		: _node( other._get_node() )
	{
	}

	_forward_list_iterator(
		_self_type const & other
	)
		: _node( other._node )
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
		return ft::addressof( this->operator*() );
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
		this->_node = this->_node->next;
	}

	// Friend ------------------------------------------------------------------
public:
	// - Class -------------------------
	friend class _forward_list_iterator< T, ! IsConst >;
	friend class ft::forward_list< T >;

	// - Relational Operator -----------
	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_forward_list_iterator< _T, _IsConst > const & x,
		_forward_list_iterator< _T, _IsConst > const & y
	);

	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_forward_list_iterator< _T,   _IsConst > const & x,
		_forward_list_iterator< _T, ! _IsConst > const & y
	);

}; // class _forward_list_iterator

// - Relational Operator -------------------------------------------------------
// -- Same Constness -------------------
template<
	typename T,
	bool IsConst
>
bool
operator==(
	_forward_list_iterator< T, IsConst > const & x,
	_forward_list_iterator< T, IsConst > const & y
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
	_forward_list_iterator< T, IsConst > const & x,
	_forward_list_iterator< T, IsConst > const & y
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
	_forward_list_iterator< T,   IsConst > const & x,
	_forward_list_iterator< T, ! IsConst > const & y
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
	_forward_list_iterator< T,   IsConst > const & x,
	_forward_list_iterator< T, ! IsConst > const & y
)
{
	return ( ! ( x == y ) );
}

/**
 * ForwardListBase
 */
template<
	typename T,
	typename Allocator
>
class _forward_list_base
{
	// Type --------------------------------------------------------------------
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
	typedef _forward_list_node_base  _node_base_type;
	typedef _forward_list_node< T >  _node_type;

private:
	typedef typename Allocator::template rebind< _node_type >::other  _node_allocator_type;

	// Attribute ---------------------------------------------------------------
protected:
	_node_base_type * _root;

private:
	allocator_type _allocator;
	_node_allocator_type _node_allocator;

	// Constructor -------------------------------------------------------------
protected:
	_forward_list_base(
		allocator_type const & allocator
	)
		: _allocator( allocator )
		, _node_allocator( allocator )
	{
		this->_root = this->_allocate();
		this->_root->next = nullptr;
	}

	// Destructor --------------------------------------------------------------
public:
	~_forward_list_base()
	{
		this->_deallocate( static_cast< _node_type * >( this->_root ) );
	}

	// Method ------------------------------------------------------------------
public:
	allocator_type
	get_allocator() const
	{
		return this->_allocator;
	}

protected:
	_node_type *
	_allocate()
	{
		return this->_node_allocator.allocate( 1 );
	}

	void
	_deallocate(
		_node_type * node
	)
	{
		this->_node_allocator.deallocate( node, 1 );
	}

	void
	_construct(
		_node_type * node,
		value_type const & value
	)
	{
		this->_allocator.construct( ft::addressof( node->data ), value );
	}

	void
	_destroy(
		_node_type * node
	)
	{
		this->_allocator.destroy( ft::addressof( node->data ) );
	}

	_node_type *
	_create_node(
		value_type const & value
	)
	{
		_node_type * node = this->_allocate();

		try
		{
			this->_construct( node, value );
		}
		catch( ... )
		{
			this->_deallocate( node );
			throw ;
		}

		return node;
	}

	void
	_delete_node(
		_node_type * node
	)
	{
		this->_destroy( node );
		this->_deallocate( node );
	}

}; // class _forward_list_base

} // namespace

/**
 * ForwardList
 *
 * @ref https://en.cppreference.com/w/cpp/container/forward_list
 * @ref https://cplusplus.com/reference/forward_list/forward_list/
 */
template<
	typename T,
	typename Allocator /* = std::allocator< T > */
>
class forward_list
	: public _forward_list_base< T, Allocator >
{
	// Type --------------------------------------------------------------------
private:
	typedef _forward_list_base< T, Allocator >  _self_base_type;
	typedef ft::forward_list< T, Allocator >    _self_type;

	using typename _self_base_type::_node_base_type;
	using typename _self_base_type::_node_type;

public:
	using typename _self_base_type::allocator_type;

	using typename _self_base_type::difference_type;
	using typename _self_base_type::size_type;

	using typename _self_base_type::value_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::const_reference;
	using typename _self_base_type::pointer;
	using typename _self_base_type::const_pointer;

	typedef _forward_list_iterator< T, false >  iterator;
	typedef _forward_list_iterator< T, true >   const_iterator;

	// Constructor -------------------------------------------------------------
public:
	explicit
	forward_list(
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
	{
	}

	explicit
	forward_list(
		size_type count,
		value_type const & value = value_type(),
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
	{
		this->insert_after( this->before_begin(), count, value );
	}

	template<
		typename _InputIterator
	>
	forward_list(
		_InputIterator first,
		_InputIterator last,
    	allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
	{
		this->insert_after( this->before_begin(), first, last );
	}

	forward_list(
		_self_type const & other
	)
		: _self_base_type( other.get_allocator() )
	{
		this->insert_after( this->before_begin(), other.begin(), other.end() );
	}

	forward_list(
		_self_type const & other,
    	allocator_type const & allocator
	)
		: _self_base_type( allocator )
	{
		this->insert_after( this->before_begin(), other.begin(), other.end() );
	}

	// Destructor --------------------------------------------------------------
public:
	~forward_list()
	{
		this->clear();
	}

	// Operator ----------------------------------------------------------------
public:
	_self_type &
	operator=(
		_self_type const & other
	)
	{
		if ( this != &other )
		{
			this->assign( other.begin(), other.end() );
		}

		return *this;
	}

	// Method ------------------------------------------------------------------
public:
	// - Observer ----------------------
	allocator_type get_allocator() const { return _self_base_type::get_allocator(); }

	// - Iterator ----------------------
	iterator       before_begin()       { return iterator( this->_root ); }
	const_iterator before_begin() const { return const_iterator( this->_root ); }
	iterator       begin()              { return iterator( this->_root->next ); }
	const_iterator begin()        const { return const_iterator( this->_root->next ); }
	iterator       end()                { return iterator( nullptr ); }
	const_iterator end()          const { return const_iterator( nullptr ); }

	// - Capacity ----------------------
	size_type max_size() const { return size_type( -1 ) / sizeof( _node_type ) / 2; }

	bool empty() const { return ( this->begin() == this->end() ); }

	// - Access ------------------------
	value_type &       front()       { return ( *( this->begin() ) ); }
	value_type const & front() const { return ( *( this->begin() ) ); }

	// - Modifier ----------------------
	void push_front( value_type const & value ) { this->insert_after( this->before_begin(), value ); }
	void pop_front()                            { this->erase_after( this->before_begin() ); }

	void
	resize(
		size_type size,
		value_type const & value = value_type()
	)
	{
		iterator previous = this->before_begin();
		iterator current = this->begin();

		while ( size > 0 && current != this->end() )
		{
			++previous;
			++current;
			--size;
		}

		if ( size == 0 )
		{
			this->erase_after( previous, this->end() );
		}
		else
		{
			this->insert_after( previous, size, value );
		}
	}

	iterator
	insert_after(
		const_iterator position,
		value_type const & value
	)
	{
		_node_base_type * previous = position._get_node();
		_node_base_type * node = _self_base_type::_create_node( value );

		node->next = previous->next;
		previous->next = node;

		return iterator( node );
	}

	void
	insert_after(
		const_iterator position,
		size_type count,
		value_type const & value
	)
	{
		while ( count-- > 0 )
		{
			this->insert_after( position, value );
		}
	}

	template<
		typename _InputIterator
	>
	typename ft::enable_if< ! ft::is_integer< _InputIterator >::value, void >::type
	insert_after(
		const_iterator position,
		_InputIterator first,
		_InputIterator last
	)
	{
		while ( first != last )
		{
			position = this->insert_after( position, *first );
			++first;
		}
	}

	iterator
	erase_after(
		const_iterator position
	)
	{
		_node_base_type * previous = position._get_node();
		_node_base_type * node = previous->next;

		previous->next = node->next;

		_self_base_type::_delete_node( static_cast< _node_type * >( node ) );

		return iterator( previous->next );
	}

	iterator
	erase_after(
		const_iterator first,
		const_iterator last
	)
	{
		const_iterator previous = first++;

		while ( previous != last && first != last )
		{
			first = this->erase_after( previous );
		}

		return iterator( last._get_node() );
	}

	void
	assign(
		size_type count,
		value_type const & value
	)
	{
		iterator previous = this->before_begin();
		iterator current = this->begin();

		while ( count > 0 && current != this->end() )
		{
			*current++ = value;
			--count;
			++previous;
		}

		if ( count == 0 )
		{
			this->erase_after( previous, this->end() );
		}
		else
		{
			this->insert_after( previous, count, value );
		}
	}

	template<
		typename _InputIterator
	>
	typename ft::enable_if< ! ft::is_integer< _InputIterator >::value, void >::type
	assign(
		_InputIterator first,
		_InputIterator last
	)
	{
		iterator previous = this->before_begin();
		iterator current = this->begin();

		while ( first != last && current != this->end() )
		{
			*current++ = *first;
			++first;
			++previous;
		}

		if ( first == last )
		{
			this->erase_after( previous, this->end() );
		}
		else
		{
			this->insert_after( previous, first, last );
		}
	}

	void
	clear()
	{
		this->erase_after( this->before_begin(), this->end() );
	}

	void
	swap(
		_self_type & other
	)
	{
		ft::swap( this->_root, other._root );
	}

	// - Operation ---------------------
	template<
		typename _Compare
	>
	void
	merge(
		_self_type & other,
		_Compare compare
	)
	{
		if ( this == &other )
		{
			return ;
		}

		this->_root->next = this->_merge( this->_root->next, other.begin()._get_node(), compare );
		other.before_begin()._get_node()->next = nullptr;
	}

	void
	merge(
		_self_type & other
	)
	{
		this->merge( other, ft::less< value_type >() );
	}

	void
	splice_after(
		const_iterator position,
		_self_type & other
	)
	{
		if ( ! other.empty() )
		{
			this->_transfer_after( position, other.before_begin(), other.end() );
		}
	}

	void
	splice_after(
		const_iterator position,
		_self_type &, // unused
		const_iterator element
	)
	{
		const_iterator next = element;

		this->_transfer_after( position, element, ++++next );
	}

	void
	splice_after(
		const_iterator position,
		_self_type &, // unused
		const_iterator first,
		const_iterator last
	)
	{
		if ( first != last )
		{
			this->_transfer_after( position, first, last );
		}
	}

	void
	remove(
		value_type const & value
	)
	{
		iterator previous = this->before_begin();
		iterator current = this->begin();

		while ( current != this->end() )
		{
			if ( *current == value )
			{
				current = this->erase_after( previous );
			}
			else
			{
				previous = current++;
			}
		}
	}

	template<
		typename _UnaryPredicate
	>
	void
	remove_if(
		_UnaryPredicate predicate
	)
	{
		iterator previous = this->before_begin();
		iterator current = this->begin();

		while ( current != this->end() )
		{
			if ( predicate( *current ) )
			{
				current = this->erase_after( previous );
			}
			else
			{
				previous = current++;
			}
		}
	}

	void
	reverse()
	{
		_node_base_type * previous = nullptr;
		_node_base_type * current = this->_root->next;
		_node_base_type * next = nullptr;

		while ( current != nullptr )
		{
			next = current->next;
			current->next = previous;

			previous = current;
			current = next;
		}

		this->_root->next = previous;
	}

	template<
		typename _BinaryPredicate
	>
	void
	unique(
		_BinaryPredicate predicate
	)
	{
		if ( this->empty() )
		{
			return ;
		}

		const_iterator current = this->begin();
		const_iterator next = ++this->begin();

		while ( next != this->end() )
		{
			if ( predicate( *current, *next ) )
			{
				next = this->erase_after( current );
			}
			else
			{
				current = next++;
			}
		}
	}

	void
	unique()
	{
		this->unique( ft::equal_to< value_type >() );
	}

	template<
		typename _Compare
	>
	void
	sort(
		_Compare compare
	)
	{
		this->_root->next = this->_sort( this->_root->next, compare );
	}

	void
	sort()
	{
		this->sort( ft::less< value_type >() );
	}

private:
	void
	_transfer_after(
		const_iterator before_position,
		const_iterator before_first,
		const_iterator last
	)
	{
		const_iterator before_last = before_first;

		while ( before_last._get_node()->next != last._get_node() )
		{
			++before_last;
		}

		_node_base_type * next = before_last._get_node()->next;

		    before_last._get_node()->next = before_position._get_node()->next;
		before_position._get_node()->next = before_first._get_node()->next;
		   before_first._get_node()->next = next;
	}

	template<
		typename Compare
	>
	_node_base_type *
	_sort(
		_node_base_type * list,
		Compare compare
	)
	{
		if ( list == nullptr || list->next == nullptr )
		{
			return list;
		}

		_node_base_type * slow = list;
		_node_base_type * fast = slow->next;

		while ( fast != nullptr )
		{
			fast = fast->next;

			if ( fast != nullptr )
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		_node_base_type * x = list;
		_node_base_type * y = slow->next;

		slow->next = nullptr;

		x = this->_sort( x, compare );
		y = this->_sort( y, compare );

		return this->_merge( x, y, compare );
	}

	template<
		typename Compare
	>
	_node_base_type *
	_merge(
		_node_base_type * x,
		_node_base_type * y,
		Compare compare
	)
	{
		if ( x == nullptr ) return y;
		if ( y == nullptr ) return x;

		_node_base_type root;
		_node_base_type * node = &root;

		while ( x != nullptr && y != nullptr )
		{
			if ( compare(
					static_cast< _node_type * >( y )->data,
					static_cast< _node_type * >( x )->data
				)
			)
			{
				node->next = y;
				y = y->next;
			}
			else
			{
				node->next = x;
				x = x->next;
			}

			node = node->next;
		}

		node->next = ( x == nullptr ) ? y : x;

		return root.next;
	}

}; // class forward_list

// - Relational Operator -------------------------------------------------------
template<
	typename T,
	typename Allocator
>
bool
operator==(
	ft::forward_list< T, Allocator > const & x,
	ft::forward_list< T, Allocator > const & y
)
{
	return ft::equal( x.begin(), x.end(), y.begin(), y.end() );
}

template<
	typename T,
	typename Allocator
>
bool
operator!=(
	ft::forward_list< T, Allocator > const & x,
	ft::forward_list< T, Allocator > const & y
)
{
	return ( ! ( x == y ) );
}

template<
	typename T,
	typename Allocator
>
bool
operator<(
	ft::forward_list< T, Allocator > const & x,
	ft::forward_list< T, Allocator > const & y
)
{
	return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
}

template<
	typename T,
	typename Allocator
>
bool
operator<=(
	ft::forward_list< T, Allocator > const & x,
	ft::forward_list< T, Allocator > const & y
)
{
	return ( ! ( y < x ) );
}

template<
	typename T,
	typename Allocator
>
bool
operator>(
	ft::forward_list< T, Allocator > const & x,
	ft::forward_list< T, Allocator > const & y
)
{
	return ( y < x );
}

template<
	typename T,
	typename Allocator
>
bool
operator>=(
	ft::forward_list< T, Allocator > const & x,
	ft::forward_list< T, Allocator > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * Swap
 *
 * @ref https://cplusplus.com/reference/forward_list/forward_list/swap-free/
 * @ref https://en.cppreference.com/w/cpp/container/forward_list/swap2
 */
template<
	class T,
	class Allocator
>
void
swap(
	ft::forward_list< T, Allocator > & x,
	ft::forward_list< T, Allocator > & y
)
{
	x.swap( y );
}

} // namespace ft

#endif
