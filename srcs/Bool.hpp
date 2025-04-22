
#ifndef BOOL_HPP
#define BOOL_HPP

#include <ostream>


class Bool
{

// =============================================================================
// Public
// =============================================================================
public:
	// - Types -----------------------------------------------------------------
	using self_type           = Bool;
	using self_ref_type       = self_type &;
	using self_const_ref_type = self_type const &;
	using self_ptr_type       = self_type *;
	using self_const_ptr_type = self_type const *;

	using value_type           = bool;
	using value_ref_type       = value_type &;
	using value_const_ref_type = value_type const &;
	using value_ptr_type       = value_type *;
	using value_const_ptr_type = value_type const *;

	// - Attributes ------------------------------------------------------------
	// - Constructors & Destructor & Assignment --------------------------------
	Bool() = default;
	Bool(value_type value);
	~Bool() = default;

	Bool(self_const_ref_type other) = default;

	self_ref_type operator=(self_const_ref_type other) = default;

	// - Operators -------------------------------------------------------------
	self_type operator~() const;
	self_type operator&(self_const_ref_type other) const;
	self_type operator|(self_const_ref_type other) const;

	// - Methods ---------------------------------------------------------------
	// - Getters & Setters -----------------------------------------------------
	value_type getValue() const noexcept;

	// - Friends ---------------------------------------------------------------
	friend std::ostream & operator<<(std::ostream & os, self_const_ref_type b);

// =============================================================================
// Protected
// =============================================================================
protected:
	// - Types -----------------------------------------------------------------
	// - Attributes ------------------------------------------------------------
	// - Constructors & Destructor & Assignment --------------------------------
	// - Operators -------------------------------------------------------------
	// - Methods ---------------------------------------------------------------
	// - Getters & Setters -----------------------------------------------------

// =============================================================================
// Private
// =============================================================================
private:
	// - Types -----------------------------------------------------------------
	// - Attributes ------------------------------------------------------------
	value_type _value;

	// - Constructors & Destructor & Assignment --------------------------------
	// - Operators -------------------------------------------------------------
	// - Methods ---------------------------------------------------------------
	// - Getters & Setters -----------------------------------------------------

};

// =============================================================================
// Overload
// =============================================================================
// - IO Stream -----------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, Bool::self_const_ref_type b);

#endif
