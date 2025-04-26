#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

namespace ft
{

/**
 * Exception
 *
 * @ref https://cplusplus.com/reference/exception/exception/
 * @ref https://en.cppreference.com/w/cpp/error/exception
 */
class exception
{
	// Destructor --------------------------------------------------------------
public:
	virtual ~exception()
	{
	}

	// Method ------------------------------------------------------------------
public:
	virtual char const *
	what() const
	{
		return "exception";
	}

}; // class exception

} // namespace ft

#endif
