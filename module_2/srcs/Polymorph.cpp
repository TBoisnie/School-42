
#include "Polymorph.hpp"

// Constructors & Destructors
Polymorph::Polymorph()
	: ASpell("Polymorph", "turned into a critter")
{

}

// Methods
ASpell *
Polymorph::clone() const
{
	return new Polymorph();
}