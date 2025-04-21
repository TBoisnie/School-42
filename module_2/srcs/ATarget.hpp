
#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <string>

class ASpell;
# include "ASpell.hpp"

class ATarget
{
	// Attributes
	protected:
	std::string type;

	// Constructors & Destructors
	public:
	ATarget();
	ATarget(const std::string & type);
	ATarget(const ATarget & other);

	virtual ~ATarget();

	// Operators
	public:
	ATarget & operator=(const ATarget & other);

	// Methods
	public:
	void getHitBySpell(const ASpell & spell) const;

	virtual ATarget * clone() const = 0;

	// Getters & Setters
	public:
	const std::string & getType() const;

};

#endif
