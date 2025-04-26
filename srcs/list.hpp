#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef> // size_t, ptrdiff_t
#include <memory> // std::allocator

#include "algorithm.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "type_traits.hpp"

namespace ft
{

// Forward Declaration to make it friend for _list_iterator
template<
	typename T,
	typename Allocator = std::allocator< T >
>
class list;

namespace
{

/**
 * ListNodeBase
 */
struct _list_node_base
{
	_list_node_base * prev;
	_list_node_base * next;
};

/**
 * ListNode
 */
template<
	typename T
>
struct _list_node
	: public _list_node_base
{
	T data;
};

/**
 * ListIterator
 */
template<
	typename T,
	bool IsConst
>
class _list_iterator
	: public ft::iterator<
		ft::bidirectional_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>
{
	// Type --------------------------------------------------------------------
private:
	typedef _list_node_base  _node_base_type;
	typedef _list_node< T >  _node_type;

	typedef ft::iterator<
		ft::bidirectional_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>                                     _self_base_type;
	typedef _list_iterator< T, IsConst >  _self_type;

public:
	using typename _self_base_type::value_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::pointer;

	// Attribute ---------------------------------------------------------------
private:
	_node_base_type * _node;

	// Constructor -------------------------------------------------------------
public:
	_list_iterator(
		_node_base_type * node = nullptr
	)
		: _node( node )
	{
	}

	// Note: Convert non-const to const iterator
	template<
		typename _T
	>
	_list_iterator(
		_list_iterator< _T, false > const & other
	)
		: _node( other._get_node() )
	{
	}

	_list_iterator(
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
		this->_node = this->_node->next;
	}

	void
	_decrement()
	{
		this->_node = this->_node->prev;
	}

	// Friend ------------------------------------------------------------------
public:
	// - Class -------------------------
	friend class _list_iterator< T, ! IsConst >;
	friend class ft::list< T >;

	// - Relational Operator -----------
	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_list_iterator< _T, _IsConst > const & x,
		_list_iterator< _T, _IsConst > const & y
	);

	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_list_iterator< _T,   _IsConst > const & x,
		_list_iterator< _T, ! _IsConst > const & y
	);

}; // class _list_iterator

// - Relational Operator -------------------------------------------------------
// -- Same Constness -------------------
template<
	typename T,
	bool IsConst
>
bool
operator==(
	_list_iterator< T, IsConst > const & x,
	_list_iterator< T, IsConst > const & y
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
	_list_iterator< T, IsConst > const & x,
	_list_iterator< T, IsConst > const & y
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
	_list_iterator< T,   IsConst > const & x,
	_list_iterator< T, ! IsConst > const & y
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
	_list_iterator< T,   IsConst > const & x,
	_list_iterator< T, ! IsConst > const & y
)
{
	return ( ! ( x == y ) );
}

/**
 * ListBase
 */
template<
	typename T,
	typename Allocator
>
class _list_base
{
	// Type --------------------------------------------------------------------
public:
	typedef Allocator  allocator_type;

	typedef ptrdiff_t  difference_type;
	typedef size_t     size_type;

	typedef T                   value_type;
	typedef value_type &        reference;
	typedef value_type const &  const_reference;
	typedef value_type *        pointer;
	typedef value_type const *  const_pointer;

protected:
	typedef _list_node_base  _node_base_type;
	typedef _list_node< T >  _node_type;

private:
	typedef typename Allocator::template rebind< _node_type >::other  _node_allocator_type;

	// Attribute ---------------------------------------------------------------
protected:
	_node_type * _root;

private:
	allocator_type _allocator;
	_node_allocator_type _node_allocator;

	// Constructor -------------------------------------------------------------
protected:
	_list_base(
		allocator_type const & allocator
	)
		: _allocator( allocator )
		, _node_allocator( allocator )
	{
		this->_root = this->_allocate();
		this->_root->next = this->_root;
		this->_root->prev = this->_root;
	}

	// Destructor --------------------------------------------------------------
public:
	~_list_base()
	{
		this->_deallocate( this->_root );
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

}; // class _list_base

} // namespace

/**
 * List
 *
 * @ref https://en.cppreference.com/w/cpp/container/list
 * @ref https://cplusplus.com/reference/list/list/
 */
template<
	typename T,
	typename Allocator
>
class list
	: public _list_base< T, Allocator >
{
	// Type --------------------------------------------------------------------
private:
	typedef _list_base< T, Allocator >  _self_base_type;
	typedef ft::list< T, Allocator >    _self_type;

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

	typedef _list_iterator< T, false >              iterator;
	typedef _list_iterator< T, true >               const_iterator;
	typedef ft::reverse_iterator< iterator >        reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >  const_reverse_iterator;

	// Constructor -------------------------------------------------------------
public:
	explicit
	list(
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
	{
	}

	explicit
	list(
		size_type count,
		value_type const & value = value_type(),
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
	{
		this->insert( this->begin(), count, value );
	}

	template<
		typename _InputIterator
	>
	list(
		_InputIterator first,
		_InputIterator last,
    	allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
	{
		this->insert( this->begin(), first, last );
	}

	list(
		_self_type const & other
	)
		: _self_base_type( other.get_allocator() )
	{
		this->insert( this->begin(), other.begin(), other.end() );
	}

	// Destructor --------------------------------------------------------------
public:
	~list()
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
	iterator               begin()        { return iterator( static_cast< _node_type * >( this->_root->next ) ); }
	const_iterator         begin() const  { return const_iterator( static_cast< _node_type * >( this->_root->next ) ); }
	iterator               end()          { return iterator( this->_root ); }
	const_iterator         end() const    { return const_iterator( this->_root ); }
	reverse_iterator       rbegin()       { return reverse_iterator( this->end() ); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator( this->end() ); }
	reverse_iterator       rend()         { return reverse_iterator( this->begin() ); }
	const_reverse_iterator rend() const   { return const_reverse_iterator( this->begin() ); }

	// - Capacity ----------------------
	size_type size() const     { return ft::distance( this->begin(), this->end() ); }
	size_type max_size() const { return size_type( -1 ) / sizeof( _node_type ) / 2; }

	bool empty() const { return ( this->begin() == this->end() ); }

	// - Access ------------------------
	value_type &       front()       { return ( *( this->begin() ) ); }
	value_type const & front() const { return ( *( this->begin() ) ); }
	value_type &       back()        { return ( *( --this->end() ) ); }
	value_type const & back() const  { return ( *( --this->end() ) ); }

	// - Modifier ----------------------
	void push_front( value_type const & value ) { this->insert( this->begin(), value ); }
	void push_back( value_type const & value )  { this->insert( this->end(), value ); }

	void pop_front() { this->erase( this->begin() ); }
	void pop_back()  { this->erase( --this->end() ); }

	void
	clear()
	{
		this->erase( this->begin(), this->end() );
	}

	void
	swap(
		_self_type & other
	)
	{
		ft::swap( this->_root, other._root );
	}

	void
	resize(
		size_type size,
		value_type const & value = value_type()
	)
	{
		iterator current = this->begin();

		while ( size > 0 && current != this->end() )
		{
			++current;
			--size;
		}

		if ( size == 0 )
		{
			this->erase( current, this->end() );
		}
		else
		{
			this->insert( current, size, value );
		}
	}

	iterator
	insert(
		iterator position,
		value_type const & value
	)
	{
		_node_type * node = _self_base_type::_create_node( value );

		node->prev = position._get_node()->prev;
		node->next = position._get_node();

		position._get_node()->prev->next = node;
		position._get_node()->prev = node;

		return iterator( node );
	}

	void
	insert(
		iterator position,
		size_type count,
		value_type const & value
	)
	{
		while ( count-- > 0 )
		{
			this->insert( position, value );
		}
	}

	template<
		typename _InputIterator
	>
	typename ft::enable_if< ! ft::is_integer< _InputIterator >::value, void >::type
	insert(
		iterator position,
		_InputIterator first,
		_InputIterator last
	)
	{
		while ( first != last )
		{
			this->insert( position, *first );
			++first;
		}
	}

	iterator
	erase(
		iterator position
	)
	{
		_node_base_type * node = position._get_node();

		node->prev->next = node->next;
		node->next->prev = node->prev;

		_node_base_type * next = node->next;

		_self_base_type::_delete_node( static_cast< _node_type * >( node ) );

		return iterator( static_cast< _node_type * >( next ) );
	}

	iterator
	erase(
		iterator first,
		iterator last
	)
	{
		while ( first != last )
		{
			this->erase( first++ );
		}

		return last;
	}

	void
	assign(
		size_type count,
		value_type const & value
	)
	{
		iterator current = this->begin();

		while ( count > 0 && current != this->end() )
		{
			*current++ = value;
			--count;
		}

		if ( count == 0 )
		{
			this->erase( current, this->end() );
		}
		else
		{
			this->insert( current, count, value );
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
		iterator current = this->begin();

		while ( first != last && current != this->end() )
		{
			*current++ = *first; // Note: Can't use *first++ with InputIterator
			++first;
		}

		if ( first == last )
		{
			this->erase( current, this->end() );
		}
		else
		{
			this->insert( current, first, last );
		}
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
		iterator current = this->begin();
		iterator first = other.begin();

		while ( current != this->end() && first != other.end() )
		{
			if ( compare( *first, *current ) )
			{
				iterator next = first;

				this->_transfer( current, first, ++next );

				first = next;
			}
			else
			{
				++current;
			}
		}

		if ( first != other.end() )
		{
			this->_transfer( current, first, other.end() );
		}
	}

	void
	merge(
		_self_type & other
	)
	{
		this->merge( other, ft::less< value_type >() );
	}

	void
	splice(
		iterator position,
		_self_type & other
	)
	{
		if ( ! other.empty() )
		{
			this->_transfer( position, other.begin(), other.end() );
		}
	}

	void
	splice(
		iterator position,
		_self_type &, // unused
		iterator element
	)
	{
		iterator next = element;
		++next;

		if ( position == element || position == next )
		{
			return ;
		}

		this->_transfer( position, element, next );
	}

	void
	splice(
		iterator position,
		_self_type &, // unused
		iterator first,
		iterator last
	)
	{
		if ( first != last )
		{
			this->_transfer( position, first, last );
		}
	}

	void
	remove(
		value_type const & value
	)
	{
		iterator current = this->begin();
		iterator next = current;

		while ( current != this->end() )
		{
			++next;

			if ( *current == value )
			{
				this->erase( current );
			}

			current = next;
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
		iterator current = this->begin();
		iterator next = current;

		while ( current != this->end() )
		{
			++next;

			if ( predicate( *current ) )
			{
				this->erase( current );
			}

			current = next;
		}
	}

	void
	reverse()
	{
		_node_base_type * node = this->_root;

		do
		{
			ft::swap( node->next, node->prev );
			node = node->prev;
		}
		while ( node != this->_root );
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

		iterator current = this->begin();
		iterator next = current;

		while ( ++next != this->end() )
		{
			if ( predicate( *current, *next ) )
			{
				this->erase( next );
			}
			else
			{
				current = next;
			}

			next = current;
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
		if ( this->empty() || this->_root->next->next == this->_root )
		{
			return ;
		}

		this->_root->prev->next = nullptr;

		this->_root->next = this->_sort( this->_root->next, compare );
		this->_root->prev = this->_root->next->prev;

		this->_root->next->prev = this->_root;
		this->_root->prev->next = this->_root;
	}

	void
	sort()
	{
		this->sort( ft::less< value_type >() );
	}

private:
	void
	_transfer(
		iterator position,
		iterator first,
		iterator last
	)
	{
		if ( position != last )
		{
			    last._get_node()->prev->next = position._get_node();
			   first._get_node()->prev->next =     last._get_node();
			position._get_node()->prev->next =    first._get_node();

			_node_base_type * tmp = position._get_node()->prev;

			position._get_node()->prev =  last._get_node()->prev;
			    last._get_node()->prev = first._get_node()->prev;
			   first._get_node()->prev = tmp;
		}
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
		if ( x == nullptr )
		{
			y->prev = y;
			return y;
		}
		if ( y == nullptr )
		{
			x->prev = x;
			return x;
		}

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
				y->prev = node;
				y = y->next;
			}
			else
			{
				node->next = x;
				x->prev = node;
				x = x->next;
			}

			node = node->next;
		}

		if ( x != nullptr || y != nullptr )
		{
			if ( x == nullptr )
			{
				node->next = y;
				y->prev = node;
			}
			else
			{
				node->next = x;
				x->prev = node;
			}
		}

		while ( node->next != nullptr )
		{
			node = node->next;
		}

		// Set prev of the first node to point to last node
		root.next->prev = node;

		return root.next;
	}

}; // class list

// - Relational Operator -------------------------------------------------------
template<
	typename T,
	typename Allocator
>
bool
operator==(
	ft::list< T, Allocator > const & x,
	ft::list< T, Allocator > const & y
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
	ft::list< T, Allocator > const & x,
	ft::list< T, Allocator > const & y
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
	ft::list< T, Allocator > const & x,
	ft::list< T, Allocator > const & y
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
	ft::list< T, Allocator > const & x,
	ft::list< T, Allocator > const & y
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
	ft::list< T, Allocator > const & x,
	ft::list< T, Allocator > const & y
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
	ft::list< T, Allocator > const & x,
	ft::list< T, Allocator > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * Swap
 *
 * @ref https://cplusplus.com/reference/list/list/swap-free/
 * @ref https://en.cppreference.com/w/cpp/container/list/swap2
 */
template<
	class T,
	class Allocator
>
void
swap(
	ft::list< T, Allocator > & x,
	ft::list< T, Allocator > & y
)
{
	x.swap( y );
}

} // namespace ft

#endif
