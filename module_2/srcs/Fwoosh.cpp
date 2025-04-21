
#include "Fwoosh.hpp"

// Constructors & Destructors
Fwoosh::Fwoosh()
	: ASpell("Fwoosh", "fwooshed")
{

}

// Methods
ASpell *
Fwoosh::clone() const
{
	return new Fwoosh();
}