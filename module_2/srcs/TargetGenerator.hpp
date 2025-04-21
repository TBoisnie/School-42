
#ifndef TARGET_GENERATOR_HPP
# define TARGET_GENERATOR_HPP

# include <string>
# include <map>

# include "ATarget.hpp"

class TargetGenerator
{

	// Typedef
	typedef std::map<const std::string, ATarget *> t_targets_ctn;

	// Attributes
	private:
	t_targets_ctn targets;

	// Constructors & Destructors
	public:
	TargetGenerator();
	~TargetGenerator();

	private:
	TargetGenerator(const TargetGenerator & other);

	// Operators
	private:
	TargetGenerator & operator=(const TargetGenerator & other);

	// Methods
	public:
	void learnTargetType(const ATarget * target);
	void forgetTargetType(const std::string & type);

	ATarget * createTarget(const std::string & type) const;

};

#endif
