
#include <utility> // swap
#include "Node.hpp"


namespace ReversePolishNotation
{

// =============================================================================
// Public
// =============================================================================
// - Types ---------------------------------------------------------------------
Node::Token::Token(
	EOperand d
)
	: type{ETokenType::OPERAND}
{
	this->value.d = d;
}

Node::Token::Token(
	EOperator r
)
	: type{ETokenType::OPERATOR}
{
	this->value.r = r;
}


bool
Node::Token::operator==(
	Token const & rhs
) const
{
	if (this->type != rhs.type)
	{
		return false;
	}

	if (this->isOperand())
	{
		return this->value.d == rhs.value.d;
	}

	return this->value.r == rhs.value.r;
}

bool
Node::Token::operator!=(
	Token const & rhs
) const
{
	return !(*this == rhs);
}

bool Node::Token::isOperand()  const noexcept { return (this->type == ETokenType::OPERAND); }
bool Node::Token::isOperator() const noexcept { return (this->type == ETokenType::OPERATOR); }

bool Node::Token::isBool() const noexcept
{
	switch (this->value.d)
	{
		case EOperand::FALSE:
		case EOperand::TRUE:
			return true;
		default:
			return false;
	}
}

bool Node::Token::isVariable() const noexcept
{
	switch (this->value.d)
	{
		case EOperand::A: case EOperand::B: case EOperand::C: case EOperand::D:
		case EOperand::E: case EOperand::F: case EOperand::G: case EOperand::H:
		case EOperand::I: case EOperand::J: case EOperand::K: case EOperand::L:
		case EOperand::M: case EOperand::N: case EOperand::O: case EOperand::P:
		case EOperand::Q: case EOperand::R: case EOperand::S: case EOperand::T:
		case EOperand::U: case EOperand::V: case EOperand::W: case EOperand::X:
		case EOperand::Y: case EOperand::Z:
			return true;
		default:
			return false;
	}
}

bool Node::Token::isNot()   const noexcept { return (this->value.r == EOperator::NOT); }
bool Node::Token::isAnd()   const noexcept { return (this->value.r == EOperator::AND); }
bool Node::Token::isOr()    const noexcept { return (this->value.r == EOperator::OR); }
bool Node::Token::isXor()   const noexcept { return (this->value.r == EOperator::XOR); }
bool Node::Token::isImply() const noexcept { return (this->value.r == EOperator::IMPLY); }
bool Node::Token::isEqual() const noexcept { return (this->value.r == EOperator::EQUAL); }

// - Attributes ----------------------------------------------------------------
// - Constructors & Destructor & Assignment ------------------------------------
Node::Node(
	Token token
)
	: _token{token}
	, _left{nullptr}
	, _right{nullptr}
{
	// Nothing
}

// - Operators -----------------------------------------------------------------
// - Methods -------------------------------------------------------------------
Node::self_ref_type
Node::toNegationNormalForm()
{
	this->toNegationNormalFormRecursion();
	this->simplifyRecursion();

	return *this;
}

Node::self_ref_type
Node::toConjunctiveNormalForm()
{
	this->toNegationNormalFormRecursion();
	this->simplifyRecursion();
	this->toConjunctiveNormalFormRecursion();
	this->simplifyRecursion();

	return *this;
}

// - Getters & Setters ---------------------------------------------------------
Node::Token const &
Node::getToken() const noexcept
{
	return this->_token;
}

Node::self_const_ptr_type
Node::getLeft() const noexcept
{
	return this->_left;
}

Node::self_const_ptr_type
Node::getRight() const noexcept
{
	return this->_right;
}

std::set<Node::EOperand>
Node::getVariables() const
{
	std::set<EOperand> variables;

	if (this->_token.isOperand() && this->_token.isVariable())
	{
		variables.insert(this->_token.value.d);
	}

	if (this->_left)
	{
		auto recursive = this->_left->getVariables();
		variables.insert(recursive.begin(), recursive.end());
	}

	if (this->_right)
	{
		auto recursive = this->_right->getVariables();
		variables.insert(recursive.begin(), recursive.end());
	}

	return variables;
}

std::string
Node::toString() const
{
	std::string left_str  = this->_left  ? this->_left->toString()  : "";
	std::string right_str = this->_right ? this->_right->toString() : "";

	auto value = this->_token.isOperand()
		? static_cast<char>(this->_token.value.d)
		: static_cast<char>(this->_token.value.r)
	;

	return left_str + right_str + std::string(1, value);
}

// - Friends -------------------------------------------------------------------

// =============================================================================
// Protected
// =============================================================================
// - Types ---------------------------------------------------------------------
// - Attributes ----------------------------------------------------------------
// - Constructors & Destructor & Assignment ------------------------------------
// - Operators -----------------------------------------------------------------
// - Methods -------------------------------------------------------------------
// - Getters & Setters ---------------------------------------------------------

// =============================================================================
// Private
// =============================================================================
// - Types ---------------------------------------------------------------------
// - Attributes ----------------------------------------------------------------
// - Constructors & Destructor & Assignment ------------------------------------
// - Operators -----------------------------------------------------------------
// - Methods -------------------------------------------------------------------
void
Node::toNegationNormalFormRecursion()
{
	if (this->_token.isOperator())
	{
		switch (this->_token.value.r)
		{
			case EOperator::IMPLY:
				this->convertImply();
				break;
			case EOperator::XOR:
				this->convertXor();
				break;
			case EOperator::EQUAL:
				this->convertEqual();
				break;
			case EOperator::NOT:
				this->convertDeMorganLaws();
				break;
			default:
				break;
		}
	}

	if (this->_left)  this->_left->toNegationNormalForm();
	if (this->_right) this->_right->toNegationNormalForm();
}

void
Node::toConjunctiveNormalFormRecursion()
{
	if (this->_token.isOperator())
	{
		switch (this->_token.value.r)
		{
			case EOperator::OR:
				this->applyDistributivity();
				break;
			default:
				break;
		}
	}

	if (this->_left)  this->_left->toConjunctiveNormalForm();
	if (this->_right) this->_right->toConjunctiveNormalForm();
}

void
Node::simplifyRecursion()
{
	if (this->_left)  this->_left->simplifyRecursion();
	if (this->_right) this->_right->simplifyRecursion();

	bool redo = false;
	if (this->_token.isOperator())
	{
		switch (this->_token.value.r)
		{
			case EOperator::OR:
			case EOperator::AND:
				redo |= this->applyIdempotency();
				redo |= this->applyCommutativity();
				redo |= this->applyAssociativity();
				redo |= this->applyAbsorptivity();
				break;
			case EOperator::NOT:
				redo |= this->applyDoubleNegation();
				break;
			default:
				break;
		}
	}

	if (redo) this->simplifyRecursion();
}

bool
Node::convertImply()
{
	// P => Q -> !P | Q

	this->_token.value.r = EOperator::OR;

	auto negation = std::make_shared<self_type>(EOperator::NOT);
	negation->_right = std::move(this->_left);

	this->_left = std::move(negation);

	return true;
}

bool
Node::convertEqual()
{
	// P <=> Q -> (P & Q) | (!P & !Q)

	this->_token.value.r = EOperator::OR;

	auto new_left = std::make_shared<self_type>(EOperator::AND);
	new_left->_left = this->_left;
	new_left->_right = this->_right;

	auto new_right = std::make_shared<self_type>(EOperator::AND);
	new_right->_left = std::make_shared<self_type>(EOperator::NOT);
	new_right->_right = std::make_shared<self_type>(EOperator::NOT);
	new_right->_left->_right = std::move(this->_left);
	new_right->_right->_right = std::move(this->_right);

	this->_left = std::move(new_left);
	this->_right = std::move(new_right);

	return true;
}

bool
Node::convertXor()
{
	// P ^ Q -> (P & !Q) | (!P & Q)

	this->_token.value.r = EOperator::OR;

	auto new_left = std::make_shared<self_type>(EOperator::AND);
	new_left->_right = std::make_shared<self_type>(EOperator::NOT);
	new_left->_right->_right = this->_right;
	new_left->_left = this->_left;

	auto new_right = std::make_shared<self_type>(EOperator::AND);
	new_right->_left = std::make_shared<self_type>(EOperator::NOT);
	new_right->_left->_right = std::move(this->_left);
	new_right->_right = std::move(this->_right);

	this->_left = std::move(new_left);
	this->_right = std::move(new_right);

	return true;
}

bool
Node::convertDeMorganLaws()
{
	// !(P | Q) -> !P & !Q
	// !(P & Q) -> !P | !Q

	if (!this->_right->_token.isOperator())
	{
		return false;
	}

	if (!this->_right->_token.isAnd() && !this->_right->_token.isOr())
	{
		return false;
	}

	this->_token.value.r = this->_right->_token.isOr() ? EOperator::AND : EOperator::OR;

	auto new_left = std::make_shared<self_type>(EOperator::NOT);
	new_left->_right = std::move(this->_right->_left);

	auto new_right = std::make_shared<self_type>(EOperator::NOT);
	new_right->_right = std::move(this->_right->_right);

	this->_left = std::move(new_left);
	this->_right = std::move(new_right);

	return true;
}

bool
Node::applyIdempotency()
{
	// P & P -> P
	// P | P -> P

	if (this->_left != this->_right)
	{
		return false;
	}

	*this = *this->_left.get();

	return true;
}

bool
Node::applyDoubleNegation()
{
	// !!P => P

	if (!this->_right->_token.isOperator() || !this->_right->_token.isNot())
	{
		return false;
	}

	*this = *this->_right->_right.get();

	return true;
}

bool
Node::applyCommutativity()
{
	// Q & P -> P & Q
	// Q | P -> P | Q

	if (!this->_left->_token.isVariable() || !this->_right->_token.isVariable())
	{
		return false;
	}

	if (this->_left->_token.value.d <= this->_right->_token.value.d)
	{
		return false;
	}

	std::swap(this->_left, this->_right);

	return true;
}

bool
Node::applyAssociativity()
{
	// (P | Q) | R -> P | (Q | R)
	// (P & Q) & R -> P & (Q & R)

	if (this->_token != this->_left->_token)
	{
		return false;
	}

	auto new_left = std::move(this->_left->_left);

	auto new_right = std::move(this->_left);
	new_right->_left = std::move(new_right->_right);
	new_right->_right = std::move(this->_right);

	this->_left = std::move(new_left);
	this->_right = std::move(new_right);

	return true;
}

bool
Node::applyDistributivity()
{
	// (Q & R) | P -> (P | Q) & (P | R)
	// P | (Q & R) -> (P | Q) & (P | R)

	if (!this->_right->_token.isOperator() && !this->_right->_token.isOperator())
	{
		return false;
	}

	if (this->_left->_token.isOperator() && this->_left->_token.isAnd())
	{
		std::swap(this->_left, this->_right);
	}

	if (!this->_right->_token.isOperator() || !this->_right->_token.isAnd())
	{
		return false;
	}

	this->_token.value.r = EOperator::AND;

	auto new_left = std::make_shared<self_type>(EOperator::OR);
	new_left->_left = this->_left;
	new_left->_right = std::move(this->_right->_left);

	auto new_right = std::make_shared<self_type>(EOperator::OR);
	new_right->_left = std::move(this->_left);
	new_right->_right = std::move(this->_right->_right);

	this->_left = std::move(new_left);
	this->_right = std::move(new_right);

	return true;
}

bool
Node::applyAbsorptivity()
{
	// P | (P & Q) -> P
	// P & (P | Q) -> P

	if (!this->_left->_token.isVariable() || this->_right->_token.isOperator())
	{
		return false;
	}

	if (this->_right->_token.value.r != (this->_token.isOr() ? EOperator::AND : EOperator::OR))
	{
		return false;
	}

	if (this->_left->_token != this->_right->_left->_token)
	{
		return false;
	}

	*this = *this->_left.get();

	return true;
}

// - Getters & Setters ---------------------------------------------------------

// =============================================================================
// Overload
// =============================================================================

} // End - Namespace
