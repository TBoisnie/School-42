
#ifndef DUMMY_HPP
# define DUMMY_HPP

# include "ATarget.hpp"

class Dummy
	: public ATarget
{

	// Constructors & Destructors
	public:
	Dummy();

	// Methods
	public:
	ATarget * clone() const;

};

#endif
