
#include <iostream>

#include "Warlock.hpp"

Warlock::Warlock(
	const std::string & name,
	const std::string & title
)
	: name(name), title(title)
{
	std::cout << this->name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
	std::cout << this->name << ": My job here is done!" << std::endl;
}


void
Warlock::introduce() const
{
	std::cout << this->name << ": I am " << this->name << ", " << this->title << "!" << std::endl;
}

void
Warlock::learnSpell(
	const ASpell * spell
)
{
	this->spellbook.learnSpell(spell);
}

void
Warlock::forgetSpell(
	const std::string & name
)
{
	this->spellbook.forgetSpell(name);
}

void
Warlock::launchSpell(
	const std::string & name,
	const ATarget & target
) const
{
	const ASpell * spell = this->spellbook.createSpell(name);

	if (spell)
		target.getHitBySpell(*spell);
}

const std::string &
Warlock::getName() const
{
	return this->name;
}

const std::string &
Warlock::getTitle() const
{
	return this->title;
}

void
Warlock::setTitle(
	const std::string & title
)
{
	this->title = title;
}