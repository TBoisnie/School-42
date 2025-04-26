#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <cstddef> // size_t, ptrdiff_t
#include <memory> // std::allocator

#include "algorithm.hpp"
#include "functional.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft
{

// Forward declaration
template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Compare = ft::less< Key >,
	typename Allocator = std::allocator< Value >
>
class rb_tree;

namespace
{

/**
 * RBTreeNodeBase
 */
struct _rb_tree_node_base
{
	// Enum --------------------------------------------------------------------
private:
	enum _color_type
	{
		Red = 0,
		Black = 1,
	};

	// Type --------------------------------------------------------------------
private:
	typedef _rb_tree_node_base  _self_type;

	// Attribute ---------------------------------------------------------------
public:
	_self_type * parent;
	_self_type * left;
	_self_type * right;
	_color_type color;

	// Method ------------------------------------------------------------------
public:
	bool
	is_red() const
	{
		return ( this->color == Red );
	}

	bool
	is_black() const
	{
		return ( this->color == Black );
	}

	void
	set_red()
	{
		this->color = Red;
	}

	void
	set_black()
	{
		this->color = Black;
	}

	bool
	has_left() const
	{
		return ( this->left != nullptr );
	}

	bool
	has_right() const
	{
		return ( this->right != nullptr );
	}

	bool
	has_parent() const
	{
		return ( this->parent != nullptr );
	}

	bool
	is_left_child() const
	{
		return ( this->parent->left == this );
	}

	bool
	is_right_child() const
	{
		return ( this->parent->right == this );
	}

	_self_type *
	get_left_most()
	{
		_self_type * node = this;

		// `node->left != node` is required to avoid infinite loop since `root->left = root` in an empty tree
		while ( node->has_left() && node->left != node )
		{
			node = node->left;
		}

		return node;
	}

	_self_type *
	get_right_most()
	{
		_self_type * node = this;

		// `node->right != node` is required to avoid infinite loop since `root->right = root` in an empty tree
		while ( node->has_right() && node->right != node )
		{
			node = node->right;
		}

		return node;
	}

}; // struct _rb_tree_node_base

/**
 * RBTreeNode
 */
template<
	typename T
>
struct _rb_tree_node
	: public _rb_tree_node_base
{
	T data;
}; // struct _rb_tree_node

/**
 * RBTreeIterator
 */
template<
	typename T,
	bool IsConst
>
class _rb_tree_iterator
	: public ft::iterator<
		ft::bidirectional_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>
{
	// Type --------------------------------------------------------------------
private:
	typedef _rb_tree_node_base  _node_base_type;
	typedef _rb_tree_node< T >  _node_type;

	typedef ft::iterator<
		ft::bidirectional_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>                                        _self_base_type;
	typedef _rb_tree_iterator< T, IsConst >  _self_type;

public:
	using typename _self_base_type::value_type;
	using typename _self_base_type::pointer;

	typedef T & reference;

	// Attribute ---------------------------------------------------------------
private:
	_node_base_type * _node;

	// Constructor -------------------------------------------------------------
public:
	explicit
	_rb_tree_iterator(
		_node_base_type * node = nullptr
	)
		: _node( node )
	{
	}

	// Note: Convert non-const to const iterator
	template<
		typename _T
	>
	_rb_tree_iterator(
		_rb_tree_iterator< _T, false > const & other
	)
		: _node( other._node )
	{
	}

	_rb_tree_iterator(
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
		if ( this->_node->has_right() )
		{
			this->_node = this->_node->right->get_left_most();
			return ;
		}

		_node_base_type * parent = this->_node->parent;

		while ( this->_node == parent->right )
		{
			this->_node = parent;
			parent = parent->parent;
		}

		if ( this->_node->right != parent )
		{
			this->_node = parent;
		}
	}

	void
	_decrement()
	{
		if ( this->_node->is_red() && this->_node->parent->parent == this->_node )
		{
			this->_node = this->_node->right;
			return ;
		}

		if ( this->_node->has_left() )
		{
			this->_node = this->_node->left->get_right_most();
			return ;
		}

		_node_base_type * parent = this->_node->parent;

		while ( this->_node == parent->left )
		{
			this->_node = parent;
			parent = parent->parent;
		}

		this->_node = parent;
	}

	// Friend ------------------------------------------------------------------
public:
	// - Class -------------------------
	friend class _rb_tree_iterator< T, ! IsConst >;

	template<
		typename _Key,
		typename _Value,
		typename _KeyOfValue,
		typename _Compare,
		typename _Allocator
	>
	friend class ft::rb_tree;

	// - Relational Operator -----------
	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_rb_tree_iterator< _T, _IsConst > const & x,
		_rb_tree_iterator< _T, _IsConst > const & y
	);

	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_rb_tree_iterator< _T,   _IsConst > const & x,
		_rb_tree_iterator< _T, ! _IsConst > const & y
	);

}; // class rb_tree_iterator

// - Relational Operator -------------------------------------------------------
// -- Same Constness -------------------
template<
	typename T,
	bool IsConst
>
bool
operator==(
	_rb_tree_iterator< T, IsConst > const & x,
	_rb_tree_iterator< T, IsConst > const & y
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
	_rb_tree_iterator< T, IsConst > const & x,
	_rb_tree_iterator< T, IsConst > const & y
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
	_rb_tree_iterator< T,   IsConst > const & x,
	_rb_tree_iterator< T, ! IsConst > const & y
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
	_rb_tree_iterator< T,   IsConst > const & x,
	_rb_tree_iterator< T, ! IsConst > const & y
)
{
	return ( ! ( x == y ) );
}

/**
 * RBTreeBase
 */
template<
	typename T,
	typename Allocator
>
class _rb_tree_base
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
	typedef _rb_tree_node_base  _node_base_type;
	typedef _rb_tree_node< T >  _node_type;

private:
	typedef typename Allocator::template rebind< _node_type >::other  _node_allocator_type;

	// Property ----------------------------------------------------------------
protected:
	/**
	 * _root : Define a node without any value, used to store shortcuts
	 * _root->parent : ( alias top ) Define the top element of the tree
	 * _root->left : ( alias leftmost ) Define the minimum element of the tree
	 * _root->right : ( alias rightmost ) Define the maxmimum element of the tree
	 * _root->color : Defined as red to differenciate from top element in iterator
	 */
	_node_base_type * _root;

private:
	allocator_type _allocator;
	_node_allocator_type _node_allocator;

	// Constructor -------------------------------------------------------------
protected:
	_rb_tree_base(
		allocator_type const & allocator
	)
		: _allocator( allocator )
		, _node_allocator( allocator )
	{
		_node_base_type * node = this->_allocate();

		node->parent = nullptr;
		node->left = node;
		node->right = node;
		node->set_red();

		this->_root = node;
	}

	// Destructor --------------------------------------------------------------
public:
	~_rb_tree_base()
	{
		this->_deallocate( static_cast< _node_type * >( this->_root ));
	}

	// Method ------------------------------------------------------------------
public:
	allocator_type
	get_allocator() const
	{
		return this->_allocator;
	}

protected:
	// - Allocate ----------------------
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
		this->_allocator.destroy( ft::addressof( node->data ));
	}

	// - Utility -----------------------
	_node_type *
	_create_node(
		value_type const & value
	)
	{
		_node_type * node = this->_allocate();

		try
		{
			this->_construct( node, value );

			node->parent = nullptr;
			node->left = nullptr;
			node->right = nullptr;
			node->set_red();
		}
		catch ( ... )
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

}; // class _rb_tree_base

} // namespace

/**
 * RBTree
 *
 * @ref https://www.geeksforgeeks.org/introduction-to-red-black-tree/
 * @ref https://www.programiz.com/dsa/red-black-tree
 * @ref https://www.youtube.com/watch?v=qvZGUFHWChY&list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin&index=1
 */
template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Compare,
	typename Allocator
>
class rb_tree
	: public _rb_tree_base< Value, Allocator >
{
	// Type --------------------------------------------------------------------
private:
	typedef _rb_tree_base< Value, Allocator >                          _self_base_type;
	typedef ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator >  _self_type;

	using typename _self_base_type::_node_base_type;
	using typename _self_base_type::_node_type;

public:
	using typename _self_base_type::allocator_type;

	using typename _self_base_type::difference_type;
	using typename _self_base_type::size_type;

	typedef Key  key_type;

	using typename _self_base_type::value_type;
	using typename _self_base_type::reference;
	using typename _self_base_type::const_reference;
	using typename _self_base_type::pointer;
	using typename _self_base_type::const_pointer;

	typedef KeyOfValue  key_of_value_type;
	typedef Compare     compare_type;

	typedef _rb_tree_iterator< value_type, false >  iterator;
	typedef _rb_tree_iterator< value_type, true >   const_iterator;
	typedef ft::reverse_iterator< iterator >        reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >  const_reverse_iterator;

	// Attribute ---------------------------------------------------------------
private:
	compare_type _compare;
	size_type _size;

	// Constructor -------------------------------------------------------------
public:
	explicit
	rb_tree(
		compare_type const & compare = compare_type(),
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator )
		, _compare( compare )
		, _size( 0 )
	{
	}

	rb_tree(
		_self_type const & other
	)
		: _self_base_type( other.get_allocator() )
		, _compare( other.key_comp() )
		, _size( other.size() )
	{
		if ( ! other.empty() )
		{
			this->_root->parent = this->_copy( other._root->parent, this->_root );
			this->_root->left = this->_root->parent->get_left_most();
			this->_root->right = this->_root->parent->get_right_most();
		}
	}

	// Destructor --------------------------------------------------------------
public:
	~rb_tree()
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
			_self_type copy( other );

			this->swap( copy );
		}

		return *this;
	}

	// Method ------------------------------------------------------------------
public:
	// - Observer ----------------------
	allocator_type get_allocator() const { return _self_base_type::get_allocator(); }

	compare_type key_comp() const { return this->_compare; }

	// - Iterator ----------------------
	iterator               begin()        { return iterator( this->_root->left ); }
	const_iterator         begin() const  { return const_iterator( this->_root->left ); }
	iterator               end()          { return iterator( this->_root ); }
	const_iterator         end() const    { return const_iterator( this->_root ); }
	reverse_iterator       rbegin()       { return reverse_iterator( this->end() ); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator( this->end() ); }
	reverse_iterator       rend()         { return reverse_iterator( this->begin() ); }
	const_reverse_iterator rend() const   { return const_reverse_iterator( this->begin() ); }

	// - Capacity ----------------------
	size_type size() const     { return this->_size; }
	size_type max_size() const { return size_type( -1 ) / sizeof( _node_type ) / 2; }

	bool empty() const { return ( this->_size == 0 ); }

	// - Access ------------------------
	size_type
	count(
		key_type const & key
	) const
	{
		ft::pair< const_iterator, const_iterator > range = this->equal_range( key );
		return ft::distance( range.first, range.second );
	}

	iterator
	find(
		key_type const & key
	)
	{
		_node_base_type * last = this->_root;
		_node_base_type * current = this->_root->parent;

		while ( current != nullptr )
		{
			if ( ! this->_compare( this->_get_value_key( static_cast< _node_type * >( current )->data ), key ) )
			{
				last = current;
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		iterator position = iterator( last );

		if ( position == this->end() || this->_compare( key, this->_get_value_key( static_cast< _node_type * >( last )->data )) )
		{
			position = this->end();
		}

		return position;
	}

	const_iterator
	find(
		key_type const & key
	) const
	{
		_node_base_type * last = this->_root;
		_node_base_type * current = this->_root->parent;

		while ( current != nullptr )
		{
			if ( ! this->_compare( this->_get_value_key( static_cast< _node_type * >( current )->data ), key ) )
			{
				last = current;
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		const_iterator position = const_iterator( last );

		if ( position == this->end() || this->_compare( key, this->_get_value_key( static_cast< _node_type * >( last )->data )) )
		{
			position = this->end();
		}

		return position;
	}

	iterator
	lower_bound(
		key_type const & key
	)
	{
		_node_base_type * last = this->_root;
		_node_base_type * current = this->_root->parent;

		while ( current != nullptr )
		{
			if ( ! this->_compare( this->_get_value_key( static_cast< _node_type * >( current )->data ), key ) )
			{
				last = current;
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		return iterator( last );
	}

	const_iterator
	lower_bound(
		key_type const & key
	) const
	{
		_node_base_type * last = this->_root;
		_node_base_type * current = this->_root->parent;

		while ( current != nullptr )
		{
			if ( ! this->_compare( this->_get_value_key( static_cast< _node_type * >( current )->data ), key ) )
			{
				last = current;
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		return const_iterator( last );
	}

	iterator
	upper_bound(
		key_type const & key
	)
	{
		_node_base_type * last = this->_root;
		_node_base_type * current = this->_root->parent;

		while ( current != nullptr )
		{
			if ( this->_compare( key, this->_get_value_key( static_cast< _node_type * >( current )->data )) )
			{
				last = current;
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		return iterator( last );
	}

	const_iterator
	upper_bound(
		key_type const & key
	) const
	{
		_node_base_type * last = this->_root;
		_node_base_type * current = this->_root->parent;

		while ( current != nullptr )
		{
			if ( this->_compare( key, this->_get_value_key( static_cast< _node_type * >( current )->data )) )
			{
				last = current;
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		return const_iterator( last );
	}

	ft::pair< iterator, iterator >
	equal_range(
		key_type const & key
	)
	{
		return ft::pair< iterator, iterator >( this->lower_bound( key ), this->upper_bound( key ));
	}

	ft::pair< const_iterator, const_iterator >
	equal_range(
		key_type const & key
	) const
	{
		return ft::pair< const_iterator, const_iterator >( this->lower_bound( key ), this->upper_bound( key ));
	}

	// - Modifier ----------------------
	ft::pair< iterator, bool >
	insert_unique(
		value_type const & value
	)
	{
		_node_base_type * last = this->_root;
		_node_base_type * current = this->_root->parent;

		bool is_before = true;

		while ( current != nullptr )
		{
			last = current;
			is_before = this->_compare( this->_get_value_key( value ), this->_get_value_key( static_cast< _node_type * >( current )->data ));
			current = ( is_before ) ? current->left : current->right;
		}

		iterator it = iterator( last );

		if ( is_before )
		{
			if ( it == this->begin() )
			{
				return ft::pair< iterator, bool >( this->_insert( current, last, value ), true );
			}
			else
			{
				--it;
			}
		}

		if ( this->_compare( this->_get_value_key( static_cast< _node_type * >( it._get_node() )->data ), this->_get_value_key( value )) )
		{
			return ft::pair< iterator, bool >( this->_insert( current, last, value ), true );
		}

		return ft::pair< iterator, bool >( it, false );
	}

	iterator
	insert_unique(
		iterator position,
		value_type const & value
	)
	{
		if ( position == this->begin() )
		{
			_node_base_type * node = this->_root->left;

			if ( ! this->empty() && this->_compare( this->_get_value_key( value ), this->_get_value_key( static_cast< _node_type * >( node )->data )) )
			{
				return this->_insert( node, node, value );
			}

			return this->insert_unique( value ).first;
		}

		if ( position == this->end() )
		{
			_node_base_type * node = this->_root->right;

			if ( this->_compare( this->_get_value_key( static_cast< _node_type * >( node )->data ), this->_get_value_key( value )) )
			{
				return this->_insert( nullptr, node, value );
			}

			return this->insert_unique( value ).first;
		}

		_node_base_type * node = position._get_node();
		_node_base_type * prev = ( --position )._get_node();

		if (
			   this->_compare( this->_get_value_key( static_cast< _node_type * >( prev )->data ), this->_get_value_key( value ))
			&& this->_compare( this->_get_value_key( value ), this->_get_value_key( static_cast< _node_type * >( node )->data ))
		)
		{
			if ( ! prev->has_right() )
			{
				return this->_insert( nullptr, prev, value );
			}

			return this->_insert( node, node, value );
		}

		return this->insert_unique( value ).first;
	}

	template<
		typename _InputIterator
	>
	void
	insert_unique(
		_InputIterator first,
		_InputIterator last
	)
	{
		while ( first != last )
		{
			this->insert_unique( *first );
			++first;
		}
	}

	iterator
	insert_equal(
		value_type const & value
	)
	{
		_node_base_type * last = this->_root;
		_node_base_type * current = this->_root->parent;

		while ( current != nullptr )
		{
			last = current;
			current = this->_compare( this->_get_value_key( value ), this->_get_value_key( static_cast< _node_type * >( current )->data )) ? current->left : current->right;
		}

		return this->_insert( current, last, value );
	}

	iterator
	insert_equal(
		iterator position,
		value_type const & value
	)
	{
		if ( position == this->begin() )
		{
			_node_base_type * node = this->_root->left;

			if ( ! this->empty() && ! this->_compare( this->_get_value_key( static_cast< _node_type * >( node )->data ), this->_get_value_key( value )) )
			{
				return this->_insert( node, node, value );
			}

			return this->insert_equal( value );
		}

		if ( position == this->end() )
		{
			_node_base_type * node = this->_root->right;

			if ( ! this->_compare( this->_get_value_key( value ), this->_get_value_key( static_cast< _node_type * >( node )->data )) )
			{
				return this->_insert( nullptr, node, value );
			}

			return this->insert_equal( value );
		}

		iterator next = position;
		iterator prev = --position;

		while ( ! (
			   ! this->_compare( this->_get_value_key( value ), this->_get_value_key( static_cast< _node_type * >( prev._get_node() )->data ))
			&& ! this->_compare( this->_get_value_key( static_cast< _node_type * >( next._get_node() )->data ), this->_get_value_key( value ))
		) )
		{
			++prev;
			++next;

			if ( next == this->end() )
			{
				return this->insert_equal( next, value );
			}
		}

		if (
			   ! this->_compare( this->_get_value_key( value ), this->_get_value_key( static_cast< _node_type * >( prev._get_node() )->data ))
			&& ! this->_compare( this->_get_value_key( static_cast< _node_type * >( next._get_node() )->data ), this->_get_value_key( value ))
		)
		{
			if ( ! prev._get_node()->has_right() )
			{
				return this->_insert( nullptr, prev._get_node(), value );
			}

			return this->_insert( next._get_node(), next._get_node(), value );
		}

		return this->insert_equal( value );
	}

	template<
		typename _InputIterator
	>
	void
	insert_equal(
		_InputIterator first,
		_InputIterator last
	)
	{
		while ( first != last )
		{
			this->insert_equal( *first );
			++first;
		}
	}

	void
	erase(
		iterator position
	)
	{
		_node_base_type * node = this->_rebalance_for_erase( position._get_node() );

		_self_base_type::_delete_node( static_cast< _node_type * >( node ));
		this->_size -= 1;
	}

	size_type
	erase(
		key_type const & key
	)
	{
		ft::pair< iterator, iterator > range = this->equal_range( key );
		size_type count = ft::distance( range.first, range.second );

		this->erase( range.first, range.second );

		return count;
	}

	void
	erase(
		iterator first,
		iterator last
	)
	{
		if ( first == this->begin() && last == this->end() )
		{
			return this->clear();
		}

		while ( first != last )
		{
			this->erase( first++ );
		}
	}

	void
	erase(
		key_type const * first,
		key_type const * last
	)
	{
		while ( first != last )
		{
			this->erase( *first++ );
		}
	}

	void
	clear()
	{
		if ( this->empty() )
		{
			return ;
		}

		this->_erase( this->_root->parent );

		this->_root->parent = nullptr;
		this->_root->left = this->_root;
		this->_root->right = this->_root;

		this->_size = 0;
	}

	void
	swap(
		_self_type & other
	)
	{
		ft::swap( this->_root, other._root );
		ft::swap( this->_size, other._size );
		ft::swap( this->_compare, other._compare );
	}

private:
	key_type const &
	_get_value_key(
		value_type const & value
	) const
	{
		return ( key_of_value_type()( value ));
	}

	_node_type *
	_copy(
		_node_base_type * node,
		_node_base_type * root
	)
	{
		_node_type * top = _self_base_type::_create_node( static_cast< _node_type * >( node )->data );
		top->color = node->color;
		top->parent = root;

		try
		{
			if ( node->has_right() )
			{
				top->right = this->_copy( node->right, top );
			}

			root = top;
			node = node->left;

			while ( node != nullptr )
			{
				_node_type * clone = _self_base_type::_create_node( static_cast< _node_type * >( node )->data );
				clone->color = node->color;
				clone->parent = root;

				root->left = clone;

				if ( node->has_right() )
				{
					clone->right = this->_copy( node->right, clone );
				}

				root = clone;
				node = node->left;
			}
		}
		catch ( ... )
		{
			this->_erase( top );
			throw ;
		}

		return top;
	}

	iterator
	_insert(
		_node_base_type * parent,
		_node_base_type * root,
		value_type const & value
	)
	{
		_node_type * node = _self_base_type::_create_node( value );
		node->parent = root;

		if ( parent != nullptr || root == this->_root || this->_compare( this->_get_value_key( value ), this->_get_value_key( static_cast< _node_type * >( root )->data )) )
		{
			root->left = node;

			if ( root == this->_root )
			{
				this->_root->parent = node;
				this->_root->right = node;
			}
			else if ( root == this->_root->left )
			{
				this->_root->left = node;
			}
		}
		else
		{
			root->right = node;

			if ( root == this->_root->right )
			{
				this->_root->right = node;
			}
		}

		this->_rebalance_for_insert( node );
		this->_size += 1;

		return iterator( node );
	}

	void
	_erase(
		_node_base_type * node
	)
	{
		while ( node != nullptr )
		{
			_node_base_type * left = node->left;

			this->_erase( node->right );
			_self_base_type::_delete_node( static_cast< _node_type * >( node ));

			node = left;
		}
	}

	// - Balance -----------------------
	void
	_rotate_left(
		_node_base_type * node
	)
	{
		_node_base_type * top = node->right;

		node->right = top->left;

		if ( top->has_left() )
		{
			top->left->parent = node;
		}

		top->parent = node->parent;

		if ( node == this->_root->parent )
		{
			this->_root->parent = top;
		}
		else if ( node == node->parent->left )
		{
			node->parent->left = top;
		}
		else
		{
			node->parent->right = top;
		}

		top->left = node;
		node->parent = top;
	}

	void
	_rotate_right(
		_node_base_type * node
	)
	{
		_node_base_type * top = node->left;

		node->left = top->right;

		if ( top->has_right() )
		{
			top->right->parent = node;
		}

		top->parent = node->parent;

		if ( node == this->_root->parent )
		{
			this->_root->parent = top;
		}
		else if ( node == node->parent->right )
		{
			node->parent->right = top;
		}
		else
		{
			node->parent->left = top;
		}

		top->right = node;
		node->parent = top;
	}

	void
	_rebalance_for_insert(
		_node_base_type * node
	)
	{
		node->set_red();

		while ( node != this->_root->parent && node->parent->is_red() )
		{
			bool is_parent_left_child = ( node->parent == node->parent->parent->left );

			_node_base_type * uncle = ( is_parent_left_child )
				? node->parent->parent->right
				: node->parent->parent->left
			;

			if ( uncle != nullptr && uncle->is_red() )
			{
				uncle->set_black();

				node->parent->set_black();
				node->parent->parent->set_red();
				node = node->parent->parent;
			}
			else
			{
				if ( is_parent_left_child )
				{
					if ( node == node->parent->right )
					{
						node = node->parent;
						this->_rotate_left( node );
					}
				}
				else
				{
					if ( node == node->parent->left )
					{
						node = node->parent;
						this->_rotate_right( node );
					}
				}

				node->parent->set_black();
				node->parent->parent->set_red();

				if ( is_parent_left_child )
				{
					this->_rotate_right( node->parent->parent );
				}
				else
				{
					this->_rotate_left( node->parent->parent );
				}
			}
		}

		this->_root->parent->set_black();
	}

	_node_base_type *
	_rebalance_for_erase(
		_node_base_type * node
	)
	{
		_node_base_type * top = node;
		_node_base_type * x = nullptr;
		_node_base_type * parent = nullptr;

		if ( ! top->has_left() )
		{
			x = top->right;
		}
		else if ( ! top->has_right() )
		{
			x = top->left;
		}
		else
		{
			top = top->right->get_left_most();
			x = top->right;
		}

		// Remove `node` from the tree
		if ( top == node )
		{
			parent = node->parent;

			if ( x != nullptr )
			{
				x->parent = parent;
			}

			if ( node == this->_root->parent )
			{
				this->_root->parent = x;
			}
			else
			{
				if ( node == node->parent->left )
				{
					node->parent->left = x;
				}
				else
				{
					node->parent->right = x;
				}
			}

			if ( node == this->_root->left )
			{
				this->_root->left = ( node->right == nullptr ) ? node->parent : x->get_left_most();
			}

			if ( node == this->_root->right )
			{
				this->_root->right = ( node->left == nullptr ) ? node->parent : x->get_right_most();
			}
		}
		else
		{
			node->left->parent = top;
			top->left = node->left;

			if ( top != node->right )
			{
				parent = top->parent;

				if ( x != nullptr )
				{
					x->parent = top->parent;
				}

				top->parent->left = x;
				top->right = node->right;
				node->right->parent = top;
			}
			else
			{
				parent = top;
			}

			if ( node == this->_root->parent )
			{
				this->_root->parent = top;
			}
			else if ( node == node->parent->left )
			{
				node->parent->left = top;
			}
			else
			{
				node->parent->right = top;
			}

			top->parent = node->parent;
			ft::swap( top->color, node->color );
			top = node;
		}

		if ( top->is_red() )
		{
			return top;
		}

		// Rebalance
		while ( x != this->_root->parent && ( x == nullptr || x->is_black() ) )
		{
			if ( x == parent->left )
			{
				_node_base_type * sibling = parent->right;

				if ( sibling->is_red() )
				{
					sibling->set_black();
					parent->set_red();

					this->_rotate_left( parent );

					sibling = parent->right;
				}

				if ( ( ! sibling->has_left() || sibling->left->is_black() ) && ( ! sibling->has_right() || sibling->right->is_black() ) )
				{
					sibling->set_red();
					x = parent;
					parent = parent->parent;
				}
				else
				{
					if ( ! sibling->has_right() || sibling->right->is_black() )
					{
						if ( sibling->has_left() )
						{
							sibling->left->set_black();
						}

						sibling->set_red();

						this->_rotate_right( sibling );

						sibling = parent->right;
					}

					sibling->color = parent->color;
					parent->set_black();

					if ( sibling->has_right() )
					{
						sibling->right->set_black();
					}

					this->_rotate_left( parent );

					break;
				}
			}
			else
			{
				_node_base_type * sibling = parent->left;

				if ( sibling->is_red() )
				{
					sibling->set_black();
					parent->set_red();

					this->_rotate_right( parent );

					sibling = parent->left;
				}

				if ( ( ! sibling->has_right() || sibling->right->is_black() ) && ( ! sibling->has_left()  || sibling->left->is_black() ) )
				{
					sibling->set_red();
					x = parent;
					parent = parent->parent;
				}
				else
				{
					if ( ! sibling->has_left() || sibling->left->is_black() )
					{
						if ( sibling->has_right() )
						{
							sibling->right->set_black();
						}

						sibling->set_red();

						this->_rotate_left( sibling );

						sibling = parent->left;
					}

					sibling->color = parent->color;
					parent->set_black();

					if ( sibling->has_left() )
					{
						sibling->left->set_black();
					}

					this->_rotate_right( parent );

					break;
				}
			}
		}

		if ( x != nullptr )
		{
			x->set_black();
		}

		return top;
	}

private:
	// Debug ---------------------------
	size_type
	_black_count(
		_node_base_type * node,
		_node_base_type * root
	) const
	{
		if ( node == nullptr )
		{
			return 0;
		}

		size_type count = 0;

		do
		{
			if ( node->is_black() )
			{
				count += 1;
			}

			if ( node == root )
			{
				break;
			}

			node = node->parent;
		} while ( true );

		return count;
	}

	bool
	_verify() const
	{
		if ( this->empty() || this->begin() == this->end() )
		{
			return ( this->empty() && this->begin() == this->end() && this->_root->left == this->_root && this->_root->right == this->_root );
		}

		size_type black_node_count = this->_black_count( this->_root->left, this->_root->parent );

		for ( const_iterator it = this->begin() ; it != this->end() ; ++it )
		{
			_node_base_type * node = it._get_node();
			_node_base_type * left = node->left;
			_node_base_type * right = node->right;

			if ( node->is_red() )
			{
				if ( ( left != nullptr && left->is_red() ) || ( right != nullptr && right->is_red() ) )
				{
					return false;
				}
			}

			if ( left != nullptr && this->_compare( this->_get_value_key( static_cast< _node_type * >( node )->data ), this->_get_value_key( static_cast< _node_type * >( left )->data )) )
			{
				return false;
			}

			if ( right != nullptr && this->_compare( this->_get_value_key( static_cast< _node_type * >( right )->data ), this->_get_value_key( static_cast< _node_type * >( node )->data )) )
			{
				return false;
			}

			if ( left == nullptr && right == nullptr && this->_black_count( node, this->_root->parent ) != black_node_count )
			{
				return false;
			}
		}

		if ( this->_root->left != this->_root->parent->get_left_most() )
		{
			return false;
		}

		if ( this->_root->right != this->_root->parent->get_right_most() )
		{
			return false;
		}

		return true;
	}

}; // class rb_tree

// - Relational Operator -------------------------------------------------------
template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Compare,
	typename Allocator
>
bool
operator==(
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & x,
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & y
)
{
	return ( ( x.size() == y.size() ) && ft::equal( x.begin(), x.end(), y.begin(), y.end() ) );
}

template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Compare,
	typename Allocator
>
bool
operator!=(
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & x,
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & y
)
{
	return ( ! ( x == y ) );
}

template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Compare,
	typename Allocator
>
bool
operator<(
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & x,
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & y
)
{
	return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
}

template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Compare,
	typename Allocator
>
bool
operator<=(
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & x,
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & y
)
{
	return ( ! ( y < x ) );
}

template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Compare,
	typename Allocator
>
bool
operator>(
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & x,
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & y
)
{
	return ( y < x );
}

template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Compare,
	typename Allocator
>
bool
operator>=(
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & x,
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & y
)
{
	return ( ! ( x < y ) );
}

/**
 * Swap
 */
template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Compare,
	typename Allocator
>
void
swap(
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & x,
	ft::rb_tree< Key, Value, KeyOfValue, Compare, Allocator > const & y
)
{
	x.swap( y );
}

}; // namespace ft::_rb_tree

#endif /* __SGI_STL_INTERNAL_TREE_H */
