
#include "ASpell.hpp"

// Constructors & Destructors
ASpell::ASpell()
	: name(), effects()
{

}

ASpell::ASpell(
	const std::string & name,
	const std::string & effects
)
	: name(name), effects(effects)
{

}

ASpell::ASpell(
	const ASpell & other
)
	: name(other.name), effects(other.effects)
{

}

ASpell::~ASpell()
{

}

// Operators
ASpell &
ASpell::operator=(
	const ASpell & other
)
{
	this->name = other.name;
	this->effects = other.effects;

	return *this;
}

// Methods
void
ASpell::launch(
	const ATarget & target
) const
{
	target.getHitBySpell(*this);
}

// Getters & Setters
const std::string &
ASpell::getName() const
{
	return this->name;
}

const std::string &
ASpell::getEffects() const
{
	return this->effects;
}
