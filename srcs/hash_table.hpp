#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

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
	typename Hash = ft::hash< Key >,
	typename Equal = ft::equal_to< Key >,
	typename Allocator = std::allocator< Value >
>
class hash_table;

namespace
{

/**
 * HashTableNodeBase
 */
struct _hash_table_node_base
{
	_hash_table_node_base * prev;
	_hash_table_node_base * next;
};

/**
 * HashTableNode
 */
template<
	typename T
>
struct _hash_table_node
	: public _hash_table_node_base
{
	T data;
};

/**
 * HashTableNodeCache
 */

template<
	typename T,
	typename H
>
struct _hash_table_node_cache
	: public _hash_table_node< T >
{
	H hash;
};

/**
 * HashTableIterator
 */
template<
	typename T,
	bool IsConst
>
class _hash_table_iterator
	: public ft::iterator<
		ft::forward_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>
{
	// Type --------------------------------------------------------------------
private:
	typedef _hash_table_node_base  _node_base_type;
	typedef _hash_table_node< T >  _node_type;

	typedef ft::iterator<
		ft::forward_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>                                           _self_base_type;
	typedef _hash_table_iterator< T, IsConst >  _self_type;

public:
	using typename _self_base_type::pointer;

	typedef T const &  reference;

	// Attribute ---------------------------------------------------------------
private:
	_node_base_type * _node;

	// Constructor -------------------------------------------------------------
public:
	explicit
	_hash_table_iterator(
		_node_type * node = nullptr
	)
		: _node( node )
	{
	}

	template<
		typename _T
	>
	_hash_table_iterator(
		_hash_table_iterator< _T, false > const & other
	)
		: _node( other._node )
	{
	}

	_hash_table_iterator(
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
		return ( static_cast< _node_type * >( this->_node )->data );
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

	// Method ------------------------------------------------------------------
private:
	// - Access ------------------------
	_node_base_type *
	_get_node() const
	{
		return this->_node;
	}

	// - Iteration ---------------------
	void
	_increment()
	{
		if ( this->_node != nullptr )
		{
			this->_node = this->_node->next;
		}
	}

	// Friend ------------------------------------------------------------------
public:
	// - Class -------------------------
	friend class _hash_table_iterator< T, ! IsConst >;

	template<
		typename _Key,
		typename _Value,
		typename _KeyOfValue,
		typename _Hash,
		typename _Equal,
		typename _Allocator
	>
	friend class ft::hash_table;

	// - Relational Operator -----------
	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_hash_table_iterator< _T, _IsConst > const & x,
		_hash_table_iterator< _T, _IsConst > const & y
	);

	template<
		typename _T,
		bool _IsConst
	>
	friend bool
	operator==(
		_hash_table_iterator< _T,   _IsConst > const & x,
		_hash_table_iterator< _T, ! _IsConst > const & y
	);

}; // class _hash_table_iterator

// - Relational Operator -------------------------------------------------------
// -- Same Constness -------------------
template<
	typename T,
	bool IsConst
>
bool
operator==(
	_hash_table_iterator< T, IsConst > const & x,
	_hash_table_iterator< T, IsConst > const & y
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
	_hash_table_iterator< T, IsConst > const & x,
	_hash_table_iterator< T, IsConst > const & y
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
	_hash_table_iterator< T,   IsConst > const & x,
	_hash_table_iterator< T, ! IsConst > const & y
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
	_hash_table_iterator< T,   IsConst > const & x,
	_hash_table_iterator< T, ! IsConst > const & y
)
{
	return ( ! ( x == y ) );
}

/**
 * HashTableLocalIterator
 */
template<
	typename T,
	typename S,
	bool IsConst
>
class _hash_table_local_iterator
	: public ft::iterator<
		ft::forward_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>
{
	// Type --------------------------------------------------------------------
private:
	typedef _hash_table_node_base           _node_base_type;
	typedef _hash_table_node< T >           _node_type;
	typedef _hash_table_node_cache< T, S >  _node_cache_type;

	typedef S  _size_type;

	typedef ft::iterator<
		ft::forward_iterator_tag,
		typename ft::conditional< IsConst, T const, T >::type
	>                                                    _self_base_type;
	typedef _hash_table_local_iterator< T, S, IsConst >  _self_type;

public:
	using typename _self_base_type::pointer;

	typedef T const &  reference;

	// Attribute ---------------------------------------------------------------
private:
	_node_base_type * _node;
	_size_type _bucket_index;
	_size_type _bucket_count;

	// Constructor -------------------------------------------------------------
public:
	explicit
	_hash_table_local_iterator(
		_node_cache_type * node = nullptr,
		_size_type bucket_index = 0,
		_size_type bucket_count = 0
	)
		: _node( node )
		, _bucket_index( bucket_index )
		, _bucket_count( bucket_count )
	{
	}

	template<
		typename _T
	>
	_hash_table_local_iterator(
		_hash_table_local_iterator< _T, S, false > const & other
	)
		: _node( other._node )
		, _bucket_index( other._bucket_index )
		, _bucket_count( other._bucket_count )
	{
	}

	_hash_table_local_iterator(
		_self_type const & other
	)
		: _node( other._node )
		, _bucket_index( other._bucket_index )
		, _bucket_count( other._bucket_count )
	{
	}

	// Operator ----------------------------------------------------------------
public:
	// - Access ------------------------
	reference
	operator*() const
	{
		return ( static_cast< _node_type * >( this->_node )->data );
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

	// Method ------------------------------------------------------------------
private:
	// - Access ------------------------
	_node_base_type *
	_get_node() const
	{
		return this->_node;
	}

	// - Iteration ---------------------
	void
	_increment()
	{
		if ( this->_node == nullptr )
		{
			return ;
		}

		this->_node = this->_node->next;

		if ( this->_node == nullptr )
		{
			return ;
		}

		_size_type bucket = static_cast< _node_cache_type * >( this->_node )->hash % this->_bucket_count;

		if ( bucket != this->_bucket_index )
		{
			this->_node = nullptr;
		}
	}

	// Friend ------------------------------------------------------------------
public:
	// - Class -------------------------
	friend class _hash_table_local_iterator< T, S, ! IsConst >;

	template<
		typename _Key,
		typename _Value,
		typename _KeyOfValue,
		typename _Hash,
		typename _Equal,
		typename _Allocator
	>
	friend class ft::hash_table;

	// - Relational Operator -----------
	template<
		typename _T,
		typename _S,
		bool _IsConst
	>
	friend bool
	operator==(
		_hash_table_local_iterator< _T, _S, _IsConst > const & x,
		_hash_table_local_iterator< _T, _S, _IsConst > const & y
	);

	template<
		typename _T,
		typename _S,
		bool _IsConst
	>
	friend bool
	operator==(
		_hash_table_local_iterator< _T, _S,   _IsConst > const & x,
		_hash_table_local_iterator< _T, _S, ! _IsConst > const & y
	);

}; // class _hash_table_local_iterator

// - Relational Operator -------------------------------------------------------
// -- Same Constness -------------------
template<
	typename T,
	typename S,
	bool IsConst
>
bool
operator==(
	_hash_table_local_iterator< T, S, IsConst > const & x,
	_hash_table_local_iterator< T, S, IsConst > const & y
)
{
	return ( x._get_node() == y._get_node() );
}

template<
	typename T,
	typename S,
	bool IsConst
>
bool
operator!=(
	_hash_table_local_iterator< T, S, IsConst > const & x,
	_hash_table_local_iterator< T, S, IsConst > const & y
)
{
	return ( ! ( x == y ) );
}

// -- Different Constness --------------
template<
	typename T,
	typename S,
	bool IsConst
>
bool
operator==(
	_hash_table_local_iterator< T, S,   IsConst > const & x,
	_hash_table_local_iterator< T, S, ! IsConst > const & y
)
{
	return ( x._get_node() == y._get_node() );
}

template<
	typename T,
	typename S,
	bool IsConst
>
bool
operator!=(
	_hash_table_local_iterator< T, S,   IsConst > const & x,
	_hash_table_local_iterator< T, S, ! IsConst > const & y
)
{
	return ( ! ( x == y ) );
}


/**
 * HashTableBase
 */
template<
	typename Key,
	typename Value,
	typename Allocator
>
class _hash_table_base
{
	// Type --------------------------------------------------------------------
public:
	typedef Allocator  allocator_type;

	typedef size_t     size_type;
	typedef ptrdiff_t  difference_type;

	typedef Key const  key_type;
	typedef Value      value_type;

	typedef value_type &        reference;
	typedef value_type const &  const_reference;
	typedef value_type *        pointer;
	typedef value_type const *  const_pointer;

protected:
	typedef _hash_table_node_base                            _node_base_type;
	typedef _hash_table_node< value_type >                   _node_type;
	typedef _hash_table_node_cache< value_type, size_type >  _node_cache_type;

	typedef _node_cache_type *   _bucket_type;
	typedef _node_cache_type **  _table_type;

private:
	typedef _hash_table_base< Key, Value, Allocator >  _self_type;

	typedef typename Allocator::template rebind< _bucket_type >::other      _table_allocator_type;
	typedef typename Allocator::template rebind< _node_cache_type >::other  _node_allocator_type;

	// Attribute ---------------------------------------------------------------
private:
	_table_allocator_type _table_allocator;
	_node_allocator_type _node_allocator;
	allocator_type _allocator;

protected:
	_table_type _table;
	size_type _table_size;

	// Constructor -------------------------------------------------------------
protected:
	explicit
	_hash_table_base(
		allocator_type allocator,
		size_type size = 1
	)
		: _table_allocator( allocator )
		, _node_allocator( allocator )
		, _allocator( allocator )
		, _table( nullptr )
		, _table_size( ( size <= 0 ) ? 1 : size )
	{
		this->_table = this->_allocate_table( this->_table_size );
	}

public:
	~_hash_table_base()
	{
		if ( this->_table != nullptr )
		{
			this->_deallocate_table( this->_table, this->_table_size );
		}
	}

	// Method ------------------------------------------------------------------
public:
	allocator_type
	get_allocator() const
	{
		return this->_allocator;
	}

protected:
	// - Allocation --------------------
	_table_type
	_allocate_table(
		size_type size
	)
	{
		_table_type table = this->_table_allocator.allocate( size );

		while ( size-- > 0 )
		{
			table[ size ] = nullptr;
		}

		return table;
	}

	void
	_deallocate_table(
		_table_type table,
		size_type size
	)
	{
		this->_table_allocator.deallocate( table, size );
	}

	_node_cache_type *
	_allocate_node()
	{
		return this->_node_allocator.allocate( 1 );
	}

	void
	_deallocate_node(
		_node_cache_type * node
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

};

} // namespace

/**
 * HashTable
 */
template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Hash, // = ft::hash< Key >,
	typename Equal, // = ft::equal_to< Key >,
	typename Allocator // = std::allocator< Value >
>
class hash_table
	: public _hash_table_base< Key, Value, Allocator >
{
	// Type --------------------------------------------------------------------
private:
	typedef _hash_table_base< Key, Value, Allocator >                         _self_base_type;
	typedef ft::hash_table< Key, Value, KeyOfValue, Hash, Equal, Allocator >  _self_type;

	using typename _self_base_type::_node_base_type;
	using typename _self_base_type::_node_type;
	using typename _self_base_type::_node_cache_type;

	using typename _self_base_type::_bucket_type;
	using typename _self_base_type::_table_type;

public:
	using typename _self_base_type::allocator_type;

	using typename _self_base_type::size_type;
	using typename _self_base_type::difference_type;

	typedef Hash   hasher;
	typedef Equal  key_equal;

	using typename _self_base_type::key_type;
	using typename _self_base_type::value_type;

	using typename _self_base_type::reference;
	using typename _self_base_type::const_reference;
	using typename _self_base_type::pointer;
	using typename _self_base_type::const_pointer;

	typedef _hash_table_iterator< value_type, false >                   iterator;
	typedef _hash_table_iterator< value_type, true >                    const_iterator;
	typedef _hash_table_local_iterator< value_type, size_type, false >  local_iterator;
	typedef _hash_table_local_iterator< value_type, size_type, true >   const_local_iterator;

	// Attribute ---------------------------------------------------------------
private:
	hasher _hash;
	key_equal _equal;
	float _max_load_factor;

	iterator _start;
	size_type _size;

	// Constructor -------------------------------------------------------------
public:
	explicit
	hash_table(
		allocator_type const & allocator
	)
		: _self_base_type( allocator )
		, _max_load_factor( 1 )
		, _start( nullptr )
		, _size( 0 )
	{
	}

	explicit
	hash_table(
		size_type buckets = 1,
		hasher const & hash = hasher(),
		key_equal const & equal = key_equal(),
		allocator_type const & allocator = allocator_type()
	)
		: _self_base_type( allocator, buckets )
		, _hash( hash )
		, _equal( equal )
		, _max_load_factor( 1 )
		, _start( nullptr )
		, _size( 0 )
	{
	}

	// - Copy --------------------------
	hash_table(
		_self_type const & other
	)
		: _self_base_type( other.get_allocator(), other.bucket_count() )
		, _hash( other.hash_function() )
		, _equal( other.key_eq() )
		, _max_load_factor( other.max_load_factor() )
		, _start( nullptr )
		, _size( 0 )
	{
		*this = other;
	}

	hash_table(
		_self_type const & other,
		allocator_type const & allocator
	)
		: _self_base_type( allocator, other.bucket_count() )
		, _hash( other.hash_function() )
		, _equal( other.key_eq() )
		, _max_load_factor( other.max_load_factor() )
		, _start( nullptr )
		, _size( 0 )
	{
		*this = other;
	}

	// Destructor --------------------------------------------------------------
public:
	~hash_table()
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
			this->clear();
			this->reserve( other.size() );
			this->insert_equal( other.begin(), other.end() );
		}

		return *this;
	}

	// Method ------------------------------------------------------------------
public:
	// - Observer ----------------------
	allocator_type get_allocator() const { return _self_base_type::get_allocator(); }

	hasher    hash_function() const { return this->_hash; }
	key_equal key_eq() const        { return this->_equal; }

	// - Iterator ----------------------
	iterator       begin()        { return iterator( this->_start ); }
	const_iterator begin() const  { return const_iterator( this->_start ); }
	iterator       end()          { return iterator( nullptr ); }
	const_iterator end() const    { return const_iterator( nullptr ); }

	local_iterator       begin( size_type bucket )       { return local_iterator( this->_table[ bucket ], bucket, this->bucket_count() ); }
	const_local_iterator begin( size_type bucket ) const { return const_local_iterator( this->_table[ bucket ], bucket, this->bucket_count() ); }
	local_iterator       end( size_type bucket )         { return local_iterator( nullptr, bucket, this->bucket_count() ); }
	const_local_iterator end( size_type bucket ) const   { return const_local_iterator( nullptr, bucket, this->bucket_count() ); }

	// - Capacity ----------------------
	size_type size()     const { return this->_size; }
	size_type max_size() const { return size_type( -1 ) / sizeof( _node_cache_type ); }

	bool empty() const { return ( this->_size == 0 ); }

	void
	reserve(
		size_type elements
	)
	{
		if ( elements > ( this->max_load_factor() * this->bucket_count() ) )
		{
			this->rehash( elements / this->max_load_factor() );
		}
	}

	// - Bucket ------------------------
	size_type
	bucket(
		key_type const & key
	) const
	{
		return ( this->_hash( key ) % this->bucket_count() );
	}

	size_type
	bucket_size(
		size_type bucket
	) const
	{
		_node_base_type * node = this->_table[ bucket ];
		size_type size = 0;

		while ( node != nullptr && this->_get_node_bucket( static_cast< _node_cache_type * >( node ) ) == bucket )
		{
			size += 1;
			node = node->next;
		}

		return size;
	}

	size_type
	bucket_count() const
	{
		return this->_table_size;
	}

	size_type
	max_bucket_count() const
	{
		return size_type( -1 ) / sizeof( _node_cache_type ) / 2;
	}

	// - Hash Policy -------------------
	float load_factor()     const { return this->_expected_load_factor(); }
	float max_load_factor() const { return this->_max_load_factor; }

	void
	max_load_factor(
		float factor
	)
	{
		// Note: Should NOT be 0. Could throw an exception, but std does not
		this->_max_load_factor = factor;
		this->_ask_for_rehash();
	}

	void
	rehash(
		size_type buckets
	)
	{
		if ( buckets <= this->bucket_count() )
		{
			return ;
		}

		size_type table_size = buckets;
		_table_type table = _self_base_type::_allocate_table( buckets );

		ft::swap( this->_table, table );
		ft::swap( this->_table_size, table_size );

		_node_base_type * node = this->_start._get_node();

		this->_size = 0;
		this->_start = iterator( nullptr );

		while ( node != nullptr )
		{
			_node_base_type * next = node->next;

			this->_insert( static_cast< _node_cache_type * >( node ), false );

			node = next;
		}

		_self_base_type::_deallocate_table( table, table_size );
	}

	// - Lookup ------------------------
	size_type
	count(
		key_type const & key
	) const
	{
		ft::pair< const_iterator, const_iterator > const range = this->equal_range( key );

		return ft::distance( range.first, range.second );
	}

	iterator
	find(
		key_type const & key
	)
	{
		size_type const bucket_index = this->bucket( key );
		_node_base_type * node = this->_table[ bucket_index ];

		while ( node != nullptr )
		{
			if ( this->_equal( key, this->_get_key_of_value( static_cast< _node_type * >( node )->data ) ) )
			{
				break ;
			}

			node = node->next;
		}

		return iterator( static_cast< _node_type * >( node ) );
	}

	const_iterator
	find(
		key_type const & key
	) const
	{
		size_type const bucket_index = this->bucket( key );
		_node_base_type * node = this->_table[ bucket_index ];

		while ( node != nullptr )
		{
			if ( this->_equal( key, this->_get_key_of_value( static_cast< _node_type * >( node )->data ) ) )
			{
				break ;
			}

			node = node->next;
		}

		return const_iterator( static_cast< _node_type * >( node ) );
	}

	ft::pair< iterator, iterator >
	equal_range(
		key_type const & key
	)
	{
		iterator last = this->find( key );

		if ( last == this->end() )
		{
			return ft::make_pair( last, last );
		}

		iterator first = last;

		while ( ++last != this->end() )
		{
			if ( ! this->_equal( key, this->_get_key_of_value( *last ) ) )
			{
				break ;
			}
		}

		return ft::make_pair( first, last );
	}

	ft::pair< const_iterator, const_iterator >
	equal_range(
		key_type const & key
	) const
	{
		const_iterator last = this->find( key );

		if ( last == this->end() )
		{
			return ft::make_pair( last, last );
		}

		const_iterator first = last;

		while ( ++last != this->end() )
		{
			if ( ! this->_equal( key, this->_get_key_of_value( *last ) ) )
			{
				break ;
			}
		}

		return ft::make_pair( first, last );
	}

	// - Modifier ----------------------
	// -- Insert -----------------------
	ft::pair< iterator, bool >
	insert_unique(
		value_type const & value
	)
	{
		iterator position = this->find( this->_get_key_of_value( value ) );

		if ( position != this->end() )
		{
			return ft::make_pair( position, false );
		}

		this->_ask_for_rehash( 1 );

		_node_cache_type * node = this->_create_node( value );

		this->_insert( node, true );

		return ft::make_pair( iterator( node ), true );
	}

	// Note: hint is unused, since key is unique ( do not need to be next to equivalent key )
	// only required for interface compatibility with set/map
	// ( ex: swap between map <-> unordered_map without any change )
	iterator
	insert_unique(
		const_iterator,
		value_type const & value
	)
	{
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

	ft::pair< iterator, bool >
	insert_equal(
		value_type const & value
	)
	{
		ft::pair< iterator, bool > inserted = this->insert_unique( value );

		if ( inserted.second == true )
		{
			return inserted;
		}

		this->_ask_for_rehash( 1 );

		_node_cache_type * node = this->_create_node( value );

		this->_insert( node, false );

		return ft::make_pair( iterator( node ), true );
	}

	iterator
	insert_equal(
		const_iterator,
		value_type const & value
	)
	{
		return this->insert_equal( value ).first;
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

	// -- Erase ------------------------
	iterator
	erase(
		const_iterator position
	)
	{
		_node_cache_type * node = static_cast< _node_cache_type * >( position._get_node() );

		_node_base_type * prev = node->prev;
		_node_cache_type * next = static_cast< _node_cache_type * >( node->next );

		if ( prev != nullptr )
		{
			prev->next = next;
		}

		if ( next != nullptr )
		{
			next->prev = prev;
		}

		if ( position == this->begin() )
		{
			this->_start = iterator( next );
		}

		size_type const bucket_index = this->_get_node_bucket( node );
		_bucket_type * bucket = &( this->_table[ bucket_index ] );

		if ( *bucket == node )
		{
			*bucket = ( next != nullptr && this->_get_node_bucket( next ) == bucket_index )
				? next
				: nullptr
			;
		}

		this->_delete_node( node );
		this->_size -= 1;

		return iterator( next );
	}

	size_type
	erase(
		key_type const & key
	)
	{
		ft::pair< const_iterator, const_iterator > const range = this->equal_range( key );
		size_type const count = ft::distance( range.first, range.second );

		this->erase( range.first, range.second );

		return count;
	}

	iterator
	erase(
		const_iterator first,
		const_iterator last
	)
	{
		while ( first != last )
		{
			this->erase( first++ );
		}

		return iterator( static_cast< _node_cache_type * >( last._get_node() ) );
	}

	// -- Clear / Swap -----------------
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
		ft::swap( this->_table,           other._table );
		ft::swap( this->_table_size,      other._table_size );
		ft::swap( this->_size,            other._size );
		ft::swap( this->_max_load_factor, other._max_load_factor );
		ft::swap( this->_start,           other._start );
	}

private:
	key_type const &
	_get_key_of_value(
		value_type const & value
	) const
	{
		return ( KeyOfValue()( value ) );
	}

	size_type
	_get_node_bucket(
		_node_cache_type * node
	) const
	{
		return ( node->hash % this->bucket_count() );
	}

	_node_cache_type *
	_create_node(
		value_type const & value
	)
	{
		_node_cache_type * node = _self_base_type::_allocate_node();

		try
		{
			_self_base_type::_construct( node, value );
			node->hash = this->_hash( this->_get_key_of_value( value ) );
		}
		catch ( ... )
		{
			_self_base_type::_deallocate_node( node );
			throw ;
		}

		return node;
	}

	void
	_delete_node(
		_node_cache_type * node
	)
	{
		_self_base_type::_destroy( node );
		_self_base_type::_deallocate_node( node );
	}

	float
	_expected_load_factor(
		size_type added = 0
	) const
	{
		return ( static_cast< float >( this->size() + added ) / static_cast< float >( this->bucket_count() ) );
	}

	void
	_ask_for_rehash(
		size_type added = 0
	)
	{
		if ( this->_expected_load_factor( added ) > this->max_load_factor() )
		{
			this->rehash( ( ft::max( this->size() * 2, this->size() + added ) ) / this->max_load_factor() );
		}
	}

	void
	_insert(
		_node_cache_type * node,
		bool is_unique
	)
	{
		size_type const bucket_index = this->_get_node_bucket( node );
		_bucket_type * bucket = &( this->_table[ bucket_index ] );

		if ( *bucket == nullptr )
		{
			_node_base_type * next = this->_start._get_node();

			node->prev = nullptr;
			node->next = next;

			if ( next != nullptr )
			{
				next->prev = node;
			}

			*bucket = node;
		}
		else
		{
			const_local_iterator it = this->begin( bucket_index );

			if ( is_unique == false )
			{
				while ( it != this->end( bucket_index ) )
				{
					if ( this->_equal( this->_get_key_of_value( *it ), this->_get_key_of_value( node->data ) ) )
					{
						break ;
					}

					++it;
				}
			}

			_node_base_type * next = ( it == this->end( bucket_index ) ) ? *bucket : it._get_node();

			node->prev = next->prev;
			node->next = next;

			next->prev = node;

			if ( node->prev != nullptr )
			{
				node->prev->next = node;
			}

			if ( next == *bucket )
			{
				*bucket = node;
			}
		}

		if ( this->_start._get_node() == node->next )
		{
			this->_start = iterator( node );
		}

		this->_size += 1;
	}

}; // class hash_table

// - Relational Operator -------------------------------------------------------
template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Hash,
	typename Equal,
	typename Allocator
>
bool
operator==(
	ft::hash_table< Key, Value, KeyOfValue, Hash, Equal, Allocator > const & x,
	ft::hash_table< Key, Value, KeyOfValue, Hash, Equal, Allocator > const & y
)
{
	if ( x.size() != y.size() )
	{
		return false;
	}

	typedef typename ft::hash_table< Key, Value, KeyOfValue, Hash, Equal, Allocator >::const_iterator  const_iterator;

	const_iterator it = x.begin();

	while ( it != x.end() )
	{
		ft::pair< const_iterator, const_iterator > range_x = x.equal_range( KeyOfValue()( *it ) );
		ft::pair< const_iterator, const_iterator > range_y = y.equal_range( KeyOfValue()( *it ) );

		if ( ft::distance( range_x.first, range_x.second ) != ft::distance( range_y.first, range_y.second ) )
		{
			return false;
		}

		if ( ! ft::is_permutation( range_x.first, range_x.second, range_y.first, range_y.second ) )
		{
			return false;
		}

		it = range_x.second;
	}

	return true;
}

template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Hash,
	typename Equal,
	typename Allocator
>
bool
operator!=(
	ft::hash_table< Key, Value, KeyOfValue, Hash, Equal, Allocator > const & x,
	ft::hash_table< Key, Value, KeyOfValue, Hash, Equal, Allocator > const & y
)
{
	return ( ! ( x == y ) );
}

/**
 * Swap
 */
template<
	typename Key,
	typename Value,
	typename KeyOfValue,
	typename Hash,
	typename Equal,
	typename Allocator
>
void
swap(
	ft::hash_table< Key, Value, KeyOfValue, Hash, Equal, Allocator > & x,
	ft::hash_table< Key, Value, KeyOfValue, Hash, Equal, Allocator > & y
)
{
	x.swap( y );
}

} // namespace ft

#endif
