#ifndef STDEXCEPT_HPP
#define STDEXCEPT_HPP

#include <string> // std::string
#include "exception.hpp"

namespace ft
{

/**
 * LogicError
 *
 * @ref https://cplusplus.com/reference/stdexcept/logic_error/
 * @ref https://en.cppreference.com/w/cpp/error/logic_error
 */
class logic_error
	: public ft::exception
{
	// Property ----------------------------------------------------------------
private:
	std::string _msg;

public:
	// Constructor -------------------------------------------------------------
	explicit
	logic_error(
		std::string const & msg
	)
		: _msg( msg )
	{
	}

	// Destructor --------------------------------------------------------------
public:
	virtual ~logic_error()
	{
	}

	// Method ------------------------------------------------------------------
public:
	virtual char const * what() const
	{
		return this->_msg.c_str();
	}

}; // class logic_error

/**
 * OutOfRange
 *
 * @ref https://cplusplus.com/reference/stdexcept/out_of_range/
 * @ref https://en.cppreference.com/w/cpp/error/out_of_range
 */
class out_of_range
	: public ft::logic_error
{
public:
	// Constructor -------------------------------------------------------------
	explicit
	out_of_range(
		std::string const & str
	)
		: logic_error(str)
	{
	}

}; // class out_of_range

} // namespace ft

#endif
