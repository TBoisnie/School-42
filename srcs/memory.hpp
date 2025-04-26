#ifndef MEMORY_HPP
#define MEMORY_HPP

#if __cplusplus < 201103L
# define nullptr  ( 0 )
#endif

namespace ft
{

/**
 * AddressOf
 *
 * @ref https://cplusplus.com/reference/memory/addressof/
 * @ref https://en.cppreference.com/w/cpp/memory/addressof
 */
template<
	typename T
>
T *
addressof(
	T & ref
)
{
	// @see https://stackoverflow.com/questions/16195032/implementation-of-addressof
	return reinterpret_cast< T * >( & const_cast< char & >( reinterpret_cast< volatile char const & >( ref ) ) );
}

} // namespace ft

#endif
