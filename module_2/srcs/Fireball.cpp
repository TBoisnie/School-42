
#include "Fireball.hpp"

// Constructors & Destructors
Fireball::Fireball()
	: ASpell("Fireball", "burnt to a crisp")
{

}

// Methods
ASpell *
Fireball::clone() const
{
	return new Fireball();
}
