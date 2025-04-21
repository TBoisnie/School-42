
#ifndef FIREBALL_HPP
# define FIREBALL_HPP

# include "ASpell.hpp"

class Fireball
	: public ASpell
{

	// Constructors & Destructors
	public:
	Fireball();

	// Methods
	public:
	ASpell * clone() const;

};

#endif
