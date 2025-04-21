
#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <string>

class Warlock
{
	// Attributes
	private:
	std::string name;
	std::string title;

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

	// Getters & Setters
	public:
	const std::string & getName() const;
	const std::string & getTitle() const;

	void setTitle(const std::string & title);

};

#endif
