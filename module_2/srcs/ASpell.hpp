
#ifndef ASPELL_HPP
# define ASPELL_HPP

# include <string>

class ATarget;
# include "ATarget.hpp"

class ASpell
{
	// Attributes
	protected:
	std::string name;
	std::string effects;

	// Constructors & Destructors
	public:
	ASpell();
	ASpell(const std::string & name, const std::string & effects);
	ASpell(const ASpell & other);

	virtual ~ASpell();

	// Operators
	public:
	ASpell & operator=(const ASpell & other);

	// Methods
	public:
	void launch(const ATarget & target) const;

	virtual ASpell * clone() const = 0;

	// Getters & Setters
	public:
	const std::string & getName() const;
	const std::string & getEffects() const;

};

#endif
