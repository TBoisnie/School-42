
#ifndef BRICK_WALL_HPP
# define BRICK_WALL_HPP

# include "ATarget.hpp"

class BrickWall
	: public ATarget
{

	// Constructors & Destructors
	public:
	BrickWall();

	// Methods
	public:
	ATarget * clone() const;

};

#endif
