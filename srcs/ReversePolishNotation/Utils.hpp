
#ifndef REVERSE_POLISH_NOTATION_UTILS_HPP
#define REVERSE_POLISH_NOTATION_UTILS_HPP

#include <map>
#include "Node.hpp"

namespace ReversePolishNotation
{

// =============================================================================
// Functions
// =============================================================================
// - Parser --------------------------------------------------------------------
Node::self_ptr_type parse(std::string const & formula);

// =============================================================================
// Templated Functions
// =============================================================================
// - Evaluer -------------------------------------------------------------------
template<typename T>
T
eval(
	Node::self_const_ptr_type node,
	std::map<Node::EOperand, T> const & operands_values
)
{
	#define ERROR_MSG(MSG) "ReversePolishNotation::eval<...>() : " #MSG "."

	if (node->getToken().isOperand())
	{
		try
		{
			return operands_values.at(node->getToken().value.d);
		}
		catch (std::exception const & e)
		{
			throw std::invalid_argument(ERROR_MSG("Missing Operand Value"));
		}
	}

	if (node->getToken().isOperator())
	{
		// Unary
		auto right = eval<T>(node->getRight(), operands_values);

		if (node->getToken().isNot()) return (~right);

		// Binary
		auto left = eval<T>(node->getLeft(), operands_values);

		if (node->getToken().isAnd())   return ( left & right);
		if (node->getToken().isOr())    return ( left | right);
		if (node->getToken().isImply()) return (~left | right);
		if (node->getToken().isXor())   return ((left & ~right) | (~left &  right));
		if (node->getToken().isEqual()) return ((left &  right) | (~left & ~right));
	}

	throw std::logic_error(ERROR_MSG("Missing Token Support"));

	#undef ERROR_MSG
}


// - Truth Table ---------------------------------------------------------------
template<
	typename T,
	typename Functor
>
void
forEachTruthTableRow(
	std::map<Node::EOperand, T> & operands_values,
	Functor lambda
)
{
	auto variables_count = operands_values.size();
	variables_count -= operands_values.contains(Node::EOperand::FALSE);
	variables_count -= operands_values.contains(Node::EOperand::TRUE);

	if (variables_count == 0)
	{
		throw std::logic_error("ReversePolishNotation::Utils::forEachTruthTableRow() : No variable found.");
	}

	forEachTruthTableRowRecursion(operands_values, lambda, operands_values.begin());
}

template<
	typename T,
	typename Functor
>
static void
forEachTruthTableRowRecursion(
	std::map<Node::EOperand, T> & operands_values,
	Functor lambda,
	typename std::map<Node::EOperand, T>::iterator it
)
{
	while (
		it != operands_values.end() &&
		(
			it->first == Node::EOperand::FALSE ||
			it->first == Node::EOperand::TRUE
		)
	)
	{
		++it;
	}

	if (it == operands_values.end())
	{
		lambda();
		return;
	}

	auto current = it;
	auto next = ++it;

	current->second = operands_values[Node::EOperand::FALSE];
	forEachTruthTableRowRecursion(operands_values, lambda, next);

	current->second = operands_values[Node::EOperand::TRUE];
	forEachTruthTableRowRecursion(operands_values, lambda, next);
}

} // End - Namespace

#endif
