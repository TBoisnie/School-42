
#include "SpellBook.hpp"

// Constructors & Destructors
SpellBook::SpellBook()
{

}

SpellBook::SpellBook(
	const SpellBook & other
)
{
	(void)other;
}

SpellBook::~SpellBook()
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
}

// Operators
SpellBook &
SpellBook::operator=(
	const SpellBook & other
)
{
	(void)other;

	return *this;
}

// Methods
void
SpellBook::learnSpell(
	const ASpell * spell
)
{
	if (!spell)
		return ;

	this->forgetSpell(spell->getName());
	this->spells[spell->getName()] = spell->clone();
}

void
SpellBook::forgetSpell(
	const std::string & name
)
{
	t_spells_ctn::iterator found = this->spells.find(name);

	if (found != this->spells.end())
	{
		delete found->second;
		this->spells.erase(found);
	}
}

ASpell *
SpellBook::createSpell(
	const std::string & name
) const
{
	t_spells_ctn::const_iterator found = this->spells.find(name);

	if (found == this->spells.end())
		return 0;

	return found->second;
}
