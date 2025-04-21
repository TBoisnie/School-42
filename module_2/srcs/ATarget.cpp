
#include <iostream>

#include "ATarget.hpp"

// Constructors & Destructors
ATarget::ATarget()
	: type()
{

}

ATarget::ATarget(
	const std::string & type
)
	: type(type)
{

}

ATarget::ATarget(
	const ATarget & other
)
	: type(other.type)
{

}

ATarget::~ATarget()
{

}

// Operators
ATarget &
ATarget::operator=(
	const ATarget & other
)
{
	this->type = other.type;

	return *this;
}

// Methods
void
ATarget::getHitBySpell(
	const ASpell & spell
) const
{
	std::cout << this->type << " has been " << spell.getEffects() << "!" << std::endl;
}

// Getters & Setters
const std::string &
ATarget::getType() const
{
	return this->type;
}