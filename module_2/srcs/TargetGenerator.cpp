
#include "TargetGenerator.hpp"

// Constructors & Destructors
TargetGenerator::TargetGenerator()
{

}

TargetGenerator::~TargetGenerator()
{
	// todo clear
}

TargetGenerator::TargetGenerator(
	const TargetGenerator & other
)
{
	(void)other;
}

// Operators
TargetGenerator &
TargetGenerator::operator=(
	const TargetGenerator & other
)
{
	(void)other;
	return *this;
}

// Methods
void
TargetGenerator::learnTargetType(
	const ATarget * target
)
{
	if (!target)
		return ;

	this->forgetTargetType(target->getType());
	this->targets[target->getType()] = target->clone();
}

void
TargetGenerator::forgetTargetType(
	const std::string & type
)
{
	t_targets_ctn::iterator found = this->targets.find(type);

	if (found != this->targets.end())
	{
		delete found->second;
		this->targets.erase(found);
	}
}


ATarget *
TargetGenerator::createTarget(
	const std::string & type
) const
{
	t_targets_ctn::const_iterator found = this->targets.find(type);

	if (found == this->targets.end())
		return 0;

	return found->second;
}
