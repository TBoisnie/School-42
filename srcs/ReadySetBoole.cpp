
#include <stdexcept>
#include <iostream>
#include <memory> // SharedPtr
#include "Bool.hpp"
#include "Set.hpp"
#include "ReversePolishNotation/Utils.hpp"
#include "ReversePolishNotation/Node.hpp"
#include "Combinatorics.hpp"
#include "ReadySetBoole.hpp"


namespace ReadySetBoole
{

// https://en.wikipedia.org/wiki/Adder_(electronics)
u32 adder(u32 a, u32 b) noexcept
{
	u32 carry;

	while (b != 0)
	{
		carry = a & b;
		a ^= b;
		b = carry << 1;
	}

	return a;
}

// https://en.wikipedia.org/wiki/Ancient_Egyptian_multiplication
u32 multiplier(u32 a, u32 b) noexcept
{
	u32 result = 0;

	while (b != 0)
	{
		if (b & 1)
		{
			result = adder(result, a);
		}

		a <<= 1;
		b >>= 1;
	}

	return result;
}

// https://en.wikipedia.org/wiki/Gray_code
u32 gray_code(u32 n) noexcept
{
	return n ^ (n >> 1);
}

bool eval_formula(std::string const & formula)
{
	namespace RPN = ReversePolishNotation;

	auto tree = RPN::parse(formula);

	using OP = RPN::Node::EOperand;
	std::map<OP, Bool> operands_values;

	// Boolean
	operands_values.insert(std::make_pair(OP::FALSE, Bool{false}));
	operands_values.insert(std::make_pair(OP::TRUE,  Bool{true} ));

	return RPN::eval(tree, operands_values).getValue();
}

void print_truth_table(std::string const & formula)
{
	namespace RPN = ReversePolishNotation;

	auto tree = RPN::parse(formula);
	auto variables = tree->getVariables();

	using OP = RPN::Node::EOperand;
	std::map<OP, Bool> operands_values;

	// Boolean
	operands_values.insert(std::make_pair(OP::FALSE, Bool{false}));
	operands_values.insert(std::make_pair(OP::TRUE,  Bool{true} ));

	// Variables
	for (auto const variable : variables)
	{
		operands_values.insert(std::make_pair(variable, operands_values[OP::FALSE]));
	}

	// Header
	for (auto const variable : variables)
	{
		std::cout << "| " << static_cast<char>(variable) << " ";
	}
	std::cout << "| = |" << std::endl;

	// Separator
	for (auto const variable : variables)
	{
		(void) variable;
		std::cout << "|---";
	}
	std::cout << "|---|" << std::endl;

	// Table
	RPN::forEachTruthTableRow(operands_values,
		[&tree, &variables, &operands_values] () {
			for (auto const variable : variables)
			{
				std::cout << "| " << operands_values.at(variable) << " ";
			}
			std::cout << "| " << RPN::eval(tree, operands_values) << " |" << std::endl;
		}
	);
}

std::string negation_normal_form(std::string const & formula)
{
	auto tree = ReversePolishNotation::parse(formula);

	return tree->toNegationNormalForm().toString();
}

std::string conjunctive_normal_form(std::string const & formula)
{
	auto tree = ReversePolishNotation::parse(formula);

	return tree->toConjunctiveNormalForm().toString();
}

bool sat(std::string const & formula)
{
	namespace RPN = ReversePolishNotation;

	auto tree = RPN::parse(formula);
	auto variables = tree->getVariables();

	using OP = RPN::Node::EOperand;
	std::map<OP, Bool> operands_values;

	// Boolean
	operands_values.insert(std::make_pair(OP::FALSE, Bool{false}));
	operands_values.insert(std::make_pair(OP::TRUE,  Bool{true} ));

	// Variables
	for (auto const variable : variables)
	{
		operands_values.insert(std::make_pair(variable, operands_values[OP::FALSE]));
	}

	// Solvable
	bool has_solution = false;

	RPN::forEachTruthTableRow(operands_values,
		[&tree, &operands_values, &has_solution] () {
			has_solution |= RPN::eval(tree, operands_values).getValue();
		}
	);

	return has_solution;
}

std::vector<std::set<i32>> powerset(std::set<i32> const & set)
{
	return Combinatorics::combinations(set);
}

std::set<i32> eval_set(std::string const & formula, std::vector<std::set<i32>> const & sets)
{
	namespace RPN = ReversePolishNotation;

	RPN::Node::self_ptr_type tree = RPN::parse(formula);

	// Arguments
	auto const variables = tree->getVariables();

	if (sets.size() != variables.size())
	{
		throw std::invalid_argument("ReadySetBoole::eval_set() : Different number of variables and provided sets.");
	}

	tree->toNegationNormalForm();

	// Space
	auto space = std::make_shared<Set::space_type>();

	for (auto const & set : sets)
	{
		space->insert(set.begin(), set.end());
	}

	using OP = RPN::Node::EOperand;
	std::map<OP, Set> operands_values;

	// Boolean
	operands_values.insert(std::make_pair(OP::FALSE, Set{{},           space}));
	operands_values.insert(std::make_pair(OP::TRUE,  Set{*space.get(), space}));

	// Variables
	auto sets_it = sets.begin();

	for (auto variable : variables)
	{
		operands_values.insert(std::make_pair(variable, Set{*sets_it, space}));
		++sets_it;
	}

	return RPN::eval<Set>(tree, operands_values).getValue();
}

f64 map(u16 x, u16 y)
{
	u32 concat = x;

	concat <<= 16;
	concat |= y;

	f64 n = static_cast<f64>(concat);

	n /= UINT32_MAX;

	return n;
}

std::pair<u16, u16> reverse_map(f64 n)
{
	n *= UINT32_MAX;

	u32 concat = static_cast<u32>(n);

	u16 y = concat >> 0;
	u16 x = concat >> 16;

	return std::make_pair(x, y);
}

} // namespace ReadySetBoole
