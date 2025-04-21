
#include "Dummy.hpp"

// Constructors & Destructors
Dummy::Dummy()
	: ATarget("Target Practice Dummy")
{

}

// Methods
ATarget *
Dummy::clone() const
{
	return new Dummy();
}