
#ifndef SET_HPP
#define SET_HPP

#include <ostream>
#include <memory> // SharedPtr
#include <set>
#include "Types.hpp"


class Set
{

// =============================================================================
// Public
// =============================================================================
public:
	// - Types -----------------------------------------------------------------
	using self_type           = Set;
	using self_ref_type       = self_type &;
	using self_const_ref_type = self_type const &;
	using self_ptr_type       = self_type *;
	using self_const_ptr_type = self_type const *;

	using value_type           = std::set<i32>;
	using value_ref_type       = value_type &;
	using value_const_ref_type = value_type const &;
	using value_ptr_type       = value_type *;
	using value_const_ptr_type = value_type const *;

	using space_type           = std::set<i32>;
	using space_ref_type       = space_type &;
	using space_const_ref_type = space_type const &;
	using space_ptr_type       = std::shared_ptr<space_type>;
	using space_const_ptr_type = std::shared_ptr<space_type const>;

	// - Attributes ------------------------------------------------------------
	// - Constructors & Destructor & Assignment --------------------------------
	Set() = default;
	Set(value_const_ref_type value, space_const_ptr_type space);
	~Set() = default;

	Set(self_const_ref_type other) = default;

	self_ref_type operator=(self_const_ref_type other) = default;

	// - Operators -------------------------------------------------------------
	self_type operator~() const;
	self_type operator&(self_const_ref_type other) const;
	self_type operator|(self_const_ref_type other) const;

	// - Methods ---------------------------------------------------------------
	// - Getters & Setters -----------------------------------------------------
	value_const_ref_type getValue() const noexcept;
	space_const_ptr_type getSpace() const noexcept;

	// - Friends ---------------------------------------------------------------
	friend std::ostream & operator<<(std::ostream & os, self_const_ref_type set);

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
	space_const_ptr_type _space;

	// - Constructors & Destructor & Assignment --------------------------------
	// - Operators -------------------------------------------------------------
	// - Methods ---------------------------------------------------------------
	// - Getters & Setters -----------------------------------------------------

};

// =============================================================================
// Overload
// =============================================================================
// - IO Stream -----------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, Set::self_const_ref_type set);

#endif
