#ifndef UNORDERED_MULTIMAP
#define UNORDERED_MULTIMAP

#include <memory> // std::allocator

#include "functional.hpp"
#include "hash_table.hpp"

namespace ft
{

/**
 * UnorderedSet
 *
 * @ref https://cplusplus.com/reference/unordered_map/unordered_multimap/
 * @ref https://en.cppreference.com/w/cpp/container/unordered_multimap
 */
template<
	typename Key,
	typename Value,
	typename Hash = ft::hash< Key >,
	typename Equal = ft::equal_to< Key >,
	typename Allocator = std::allocator< ft::pair< Key const, Value > >
>
class unordered_multimap
{
	// Type --------------------------------------------------------------------
private:
	typedef ft::unordered_multimap< Key, Value, Hash, Equal, Allocator >  _self_type;

public:
	typedef Key                           key_type;
	typedef Value                         mapped_type;
	typedef ft::pair< Key const, Value >  value_type;

private:
	typedef ft::hash_table< key_type, value_type, ft::select1st< value_type >, Hash, Equal, Allocator >  _container_type;

public:
	typedef typename _container_type::allocator_type        allocator_type;

	typedef typename _container_type::size_type             size_type;
	typedef typename _container_type::difference_type       difference_type;

	typedef typename _container_type::hasher                hasher;
	typedef typename _container_type::key_equal             key_equal;

	typedef typename _container_type::reference             reference;
	typedef typename _container_type::const_reference       const_reference;
	typedef typename _container_type::pointer               pointer;
	typedef typename _container_type::const_pointer         const_pointer;

	typedef typename _container_type::iterator              iterator;
	typedef typename _container_type::const_iterator        const_iterator;
	typedef typename _container_type::local_iterator        local_iterator;
	typedef typename _container_type::const_local_iterator  const_local_iterator;

	// Attribute ---------------------------------------------------------------
private:
	_container_type _container;

	// Constructor -------------------------------------------------------------
public:
	explicit
	unordered_multimap(
		allocator_type const & allocator
	)
		: _container( allocator )
	{
	}

	explicit
	unordered_multimap(
		size_type buckets = 0,
		hasher const & hash = hasher(),
		key_equal const & equal = key_equal(),
		allocator_type const & allocator = allocator_type()
	)
		: _container( buckets, hash, equal, allocator )
	{
	}

	template<
		typename _InputIterator
	>
	unordered_multimap(
		_InputIterator first,
		_InputIterator last,
		size_type buckets = 0,
		hasher const & hash = hasher(),
		key_equal const & equal = key_equal(),
		allocator_type const & allocator = allocator_type()
	)
		: _container( buckets, hash, equal, allocator )
	{
		this->insert( first, last );
	}

	// - Copy --------------------------
	unordered_multimap(
		_self_type const & other
	)
		: _container( other._container )
	{
	}

	unordered_multimap(
		_self_type const & other,
		allocator_type const & allocator
	)
		: _container( other._container, allocator )
	{
	}

	// Operator ----------------------------------------------------------------
public:
	_self_type &
	operator=(
		_self_type const & other
	)
	{
		this->_container = other._container;
	}

	// Method ------------------------------------------------------------------
public:
	// - Observer ----------------------
	allocator_type get_allocator() const { return this->_container.get_allocator(); }

	hasher    hash_function() const { return this->_container.hash_function(); }
	key_equal key_eq()        const { return this->_container.key_eq(); }

	// - Iterator ----------------------
	iterator       begin()        { return this->_container.begin(); }
	const_iterator begin()  const { return this->_container.begin(); }
	iterator       end()          { return this->_container.end(); }
	const_iterator end()    const { return this->_container.end(); }

	local_iterator       begin ( size_type bucket )        { return this->_container.begin( bucket ); }
	const_local_iterator begin ( size_type bucket ) const  { return this->_container.begin( bucket ); }
	local_iterator       end   ( size_type bucket )        { return this->_container.end( bucket ); }
	const_local_iterator end   ( size_type bucket ) const  { return this->_container.end( bucket ); }

	// - Capacity ----------------------
	size_type size()     const { return this->_container.size(); }
	size_type max_size() const { return this->_container.max_size(); }
	bool      empty() const    { return this->_container.empty(); }

	// - Bucket ------------------------
	size_type bucket( key_type const & key ) const  { return this->_container.bucket( key ); }
	size_type bucket_size( size_type bucket ) const { return this->_container.bucket_size( bucket ); }
	size_type bucket_count() const                  { return this->_container.bucket_count(); }
	size_type max_bucket_count() const              { return this->_container.max_bucket_count(); }

	// - Hash Policy -------------------
	float load_factor() const             { return this->_container.load_factor(); }
	float max_load_factor() const         { return this->_container.max_load_factor(); }
	void  max_load_factor( float factor ) {        this->_container.max_load_factor( factor ); }
	void  rehash( size_type buckets )     {        this->_container.rehash( buckets ); }

	// - Lookup ------------------------
	size_type     count( key_type const & key ) const { return this->_container.count( key ); }
	iterator       find( key_type const & key )       { return this->_container.find( key ); }
	const_iterator find( key_type const & key ) const { return this->_container.find( key ); }

	ft::pair< iterator, iterator >             equal_range( key_type const & key )       { return this->_container.equal_range( key ); }
	ft::pair< const_iterator, const_iterator > equal_range( key_type const & key ) const { return this->_container.equal_range( key ); }

	// - Modifier ----------------------
	void reserve( size_type elements ) { this->_container.reserve( elements ); }

	// -- Insert -----------------------
	ft::pair< iterator, bool >
	insert(
		value_type const & value
	)
	{
		return this->_container.insert_equal( value );
	}

	iterator
	insert(
		const_iterator hint,
		value_type const & value

	)
	{
		return this->_container.insert_equal( hint, value );
	}

	template<
		typename _InputIterator
	>
	void
	insert(
		_InputIterator first,
		_InputIterator last
	)
	{
		this->_container.insert_equal( first, last );
	}

	// -- Erase ------------------------
	iterator
	erase(
		const_iterator position
	)
	{
		return this->_container.erase( position );
	}

	size_type
	erase(
		key_type const & key
	)
	{
		return this->_container.erase( key );
	}

	iterator
	erase(
		const_iterator first,
		const_iterator last
	)
	{
		return this->_container.erase( first, last );
	}

	// -- Clear / Swap -----------------
	void clear()                    { this->_container.clear(); }
	void swap( _self_type & other ) { this->_container.swap( other._container ); }

	// Friend ------------------------------------------------------------------
public:
	template<
		typename _T,
		typename _Hash,
		typename _Equal,
		typename _Allocator
	>
	bool
	friend operator==(
		ft::unordered_multimap< _T, _Hash, _Equal, _Allocator > const & x,
		ft::unordered_multimap< _T, _Hash, _Equal, _Allocator > const & y
	);

}; // class unordered_multimap

// - Relational Operator -------------------------------------------------------
template<
	typename T,
	typename Hash,
	typename Equal,
	typename Allocator
>
bool
operator==(
	ft::unordered_multimap< T, Hash, Equal, Allocator > const & x,
	ft::unordered_multimap< T, Hash, Equal, Allocator > const & y
)
{
	return ( x._container == y._container );
}

template<
	typename T,
	typename Hash,
	typename Equal,
	typename Allocator
>
bool
operator!=(
	ft::unordered_multimap< T, Hash, Equal, Allocator > const & x,
	ft::unordered_multimap< T, Hash, Equal, Allocator > const & y
)
{
	return ( ! ( x == y ) );
}

/**
 * Swap
 *
 * @ref https://cplusplus.com/reference/unordered_map/unordered_multimap/swap(global)/
 * @ref https://en.cppreference.com/w/cpp/container/unordered_multimap/swap2
 */
template<
	typename T,
	typename Hash,
	typename Equal,
	typename Allocator
>
void
swap(
	ft::unordered_multimap< T, Hash, Equal, Allocator > & x,
	ft::unordered_multimap< T, Hash, Equal, Allocator > & y
)
{
	x.swap( y );
}

} // namespace ft

#endif
