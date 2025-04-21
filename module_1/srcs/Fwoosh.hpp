
#ifndef FWOOSH_HPP
# define FWOOSH_HPP

# include "ASpell.hpp"

class Fwoosh
	: public ASpell
{

	// Constructors & Destructors
	public:
	Fwoosh();

	// Methods
	public:
	ASpell * clone() const;

};

#endif
