
#include <algorithm> // set_*
#include "Set.hpp"


// =============================================================================
// Public
// =============================================================================
// - Types ---------------------------------------------------------------------
// - Attributes ----------------------------------------------------------------
// - Constructors & Destructor & Assignment ------------------------------------
Set::Set(
	value_const_ref_type value,
	space_const_ptr_type space
)
	: _value{value}
	, _space{space}
{
	// Nothing
}

// - Operators -----------------------------------------------------------------
Set::self_type
Set::operator~() const
{
	value_type neg;

	std::set_difference(
		this->_value.begin(), this->_value.end(),
		this->_space->begin(), this->_space->end(),
		std::inserter(neg, neg.end())
	);

	std::set_difference(
		this->_space->begin(), this->_space->end(),
		this->_value.begin(), this->_value.end(),
		std::inserter(neg, neg.end())
	);

	return self_type{neg, this->_space};
}

Set::self_type
Set::operator&(
	self_const_ref_type other
) const
{
	value_type inter;

	std::set_intersection(
		this->_value.begin(), this->_value.end(),
		other._value.begin(), other._value.end(),
		std::inserter(inter, inter.end())
	);

	return self_type{inter, this->_space};
}

Set::self_type
Set::operator|(
	self_const_ref_type other
) const
{
	value_type uni;

	std::set_union(
		this->_value.begin(), this->_value.end(),
		other._value.begin(), other._value.end(),
		std::inserter(uni, uni.end())
	);

	return self_type{uni, this->_space};
}

// - Methods -------------------------------------------------------------------
// - Getters & Setters ---------------------------------------------------------
Set::value_const_ref_type
Set::getValue() const noexcept
{
	return this->_value;
}

Set::space_const_ptr_type
Set::getSpace() const noexcept
{
	return this->_space;
}

// - Friends -------------------------------------------------------------------

// =============================================================================
// Protected
// =============================================================================
// - Types ---------------------------------------------------------------------
// - Attributes ----------------------------------------------------------------
// - Constructors & Destructor & Assignment ------------------------------------
// - Operators -----------------------------------------------------------------
// - Methods -------------------------------------------------------------------
// - Getters & Setters ---------------------------------------------------------

// =============================================================================
// Private
// =============================================================================
// - Types ---------------------------------------------------------------------
// - Attributes ----------------------------------------------------------------
// - Constructors & Destructor & Assignment ------------------------------------
// - Operators -----------------------------------------------------------------
// - Methods -------------------------------------------------------------------
// - Getters & Setters ---------------------------------------------------------

// =============================================================================
// Overload
// =============================================================================
// - IO Stream -----------------------------------------------------------------
std::ostream &
operator<<(
	std::ostream & os,
	Set::self_const_ref_type set
)
{
	os << "{ ";
	for (auto const value : set.getValue())
	{
		os << value << " ";
	}
	os << "}";

	return os;
}
