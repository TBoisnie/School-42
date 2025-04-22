
#include <stdexcept>
#include <stack>
#include <map>
#include "Utils.hpp"

namespace ReversePolishNotation
{

// - Parser --------------------------------------------------------------------
Node::self_ptr_type
parse(
	std::string const & formula
)
{
	#define ERROR_MSG(MSG) "ReversePolishNotation::parse() : " #MSG "."

	std::stack<Node::self_ptr_type> stack;
	std::map<char, Node::self_ptr_type> variables;

	for (char const c : formula)
	{
		switch (c)
		{
			// Operand (Bool)
			case static_cast<char>(Node::EOperand::FALSE):
			case static_cast<char>(Node::EOperand::TRUE):
				{
					auto node = std::make_shared<Node::self_type>(static_cast<Node::EOperand>(c));
					stack.push(node);
				}
				break;
			// Operand (Variable)
			case static_cast<char>(Node::EOperand::A) ... static_cast<char>(Node::EOperand::Z): // C++ extension allows range, not standard.
				{
					auto node = (variables.contains(c))
						? variables.at(c)
						: std::make_shared<Node::self_type>(static_cast<Node::EOperand>(c))
					;
					stack.push(node);
				}
				break;
			// Operator (Unary)
			case static_cast<char>(Node::EOperator::NOT):
				{
					if (stack.size() < 1)
					{
						throw std::invalid_argument(ERROR_MSG("Missing Operand"));
					}

					auto node = std::make_shared<Node::self_type>(static_cast<Node::EOperator>(c));

					node->_right = stack.top();
					stack.pop();

					stack.push(node);
				}
				break;
			// Operator (Binary)
			case static_cast<char>(Node::EOperator::AND):
			case static_cast<char>(Node::EOperator::OR):
			case static_cast<char>(Node::EOperator::XOR):
			case static_cast<char>(Node::EOperator::IMPLY):
			case static_cast<char>(Node::EOperator::EQUAL):
				{
					if (stack.size() < 2)
					{
						throw std::invalid_argument(ERROR_MSG("Missing Operand"));
					}

					auto node = std::make_shared<Node::self_type>(static_cast<Node::EOperator>(c));

					node->_right = stack.top();
					stack.pop();
					node->_left = stack.top();
					stack.pop();

					stack.push(node);
				}
				break;
			// Unknown
			default:
				throw std::invalid_argument(ERROR_MSG("Unsupported Symbol"));
				break;
		}
	}

	if (stack.size() != 1)
	{
		throw std::invalid_argument(ERROR_MSG("Missing Operator"));
	}

	return stack.top();

	#undef ERROR_MSG
}

} // End - Namespace
