
#ifndef SPELL_BOOK_HPP
# define SPELL_BOOK_HPP

# include <string>
# include <map>

# include "ASpell.hpp"

class SpellBook
{
	// Typedef
	typedef std::map<const std::string, ASpell *> t_spells_ctn;

	// Attributes
	private:
	t_spells_ctn spells;

	// Constructors & Destructors
	public:
	SpellBook();
	private:
	SpellBook(const SpellBook & other);

	public:
	~SpellBook();

	// Operators
	private:
	SpellBook & operator=(const SpellBook & other);

	// Methods
	public:
	void learnSpell(const ASpell * spell);
	void forgetSpell(const std::string & name);

	ASpell * createSpell(const std::string & name) const;

	// Getters & Setters

};

#endif
