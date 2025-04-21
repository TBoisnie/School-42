
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
	for (
		t_spells_ctn::iterator it = this->spells.begin();
		it != this->spells.end();
		++it
	)
	{
		delete it->second;
	}

	this->spells.clear();

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
	if (!spell)
		return ;

	this->forgetSpell(spell->getName());
	this->spells[spell->getName()] = spell->clone();
}

void
Warlock::forgetSpell(
	const std::string & name
)
{
	t_spells_ctn::iterator found = this->spells.find(name);

	if (found != this->spells.end())
		delete found->second;

	this->spells.erase(name);
}

void
Warlock::launchSpell(
	const std::string & name,
	const ATarget & target
) const
{
	t_spells_ctn::const_iterator found = this->spells.find(name);

	if (found != this->spells.end())
		target.getHitBySpell(*found->second);
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