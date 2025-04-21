
#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <string>
# include <map>

# include "ASpell.hpp"
# include "ATarget.hpp"

class Warlock
{
	// Typedef
	typedef std::map<const std::string, const ASpell *> t_spells_ctn;

	// Attributes
	private:
	std::string name;
	std::string title;
	t_spells_ctn spells;

	// Constructors & Destructors
	private:
	Warlock();
	Warlock(const Warlock & other);

	public:
	Warlock(const std::string & name, const std::string & title);

	public:
	~Warlock();

	// Operators
	private:
	Warlock & operator=(const Warlock & other);

	// Methods
	public:
	void introduce() const;

	void learnSpell(const ASpell * spell);
	void forgetSpell(const std::string & name);

	void launchSpell(const std::string & name, const ATarget & target) const;

	// Getters & Setters
	public:
	const std::string & getName() const;
	const std::string & getTitle() const;

	void setTitle(const std::string & title);

};

#endif
