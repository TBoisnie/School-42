
#include "BrickWall.hpp"

// Constructors & Destructors
BrickWall::BrickWall()
	: ATarget("Inconspicuous Red-brick Wall")
{

}

// Methods
ATarget *
BrickWall::clone() const
{
	return new BrickWall();
}