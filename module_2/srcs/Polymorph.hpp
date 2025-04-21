
#ifndef POLYMORPH_HPP
# define POLYMORPH_HPP

# include "ASpell.hpp"

class Polymorph
	: public ASpell
{

	// Constructors & Destructors
	public:
	Polymorph();

	// Methods
	public:
	ASpell * clone() const;

};

#endif
