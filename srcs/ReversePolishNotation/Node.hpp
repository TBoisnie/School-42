
#ifndef REVERSE_POLISH_NOTATION_NODE_HPP
#define REVERSE_POLISH_NOTATION_NODE_HPP

#include <memory> // SharedPtr
#include <set>


namespace ReversePolishNotation
{

class Node
{

// =============================================================================
// Public
// =============================================================================
public:
	// - Types -----------------------------------------------------------------
	using self_type           = Node;
	using self_ref_type       = Node &;
	using self_const_ref_type = Node const &;
	using self_ptr_type       = std::shared_ptr<Node>;
	using self_const_ptr_type = std::shared_ptr<const Node>;
	using self_mov_type       = Node &&;

	enum class EOperand : char
	{
		// Bool
		FALSE = '0',
		TRUE  = '1',
		// Variable
		A = 'A',
		B = 'B',
		C = 'C',
		D = 'D',
		E = 'E',
		F = 'F',
		G = 'G',
		H = 'H',
		I = 'I',
		J = 'J',
		K = 'K',
		L = 'L',
		M = 'M',
		N = 'N',
		O = 'O',
		P = 'P',
		Q = 'Q',
		R = 'R',
		S = 'S',
		T = 'T',
		U = 'U',
		V = 'V',
		W = 'W',
		X = 'X',
		Y = 'Y',
		Z = 'Z',
	};

	enum class EOperator : char
	{
		// Unary
		NOT   = '!',
		// Binary
		AND   = '&',
		OR    = '|',
		XOR   = '^',
		IMPLY = '>',
		EQUAL = '=',
	};

	enum class ETokenType : short
	{
		OPERAND  = 0,
		OPERATOR = 1,
	};

	union UToken
	{
		EOperand  d;
		EOperator r;
	};

	struct Token
	{
		UToken     value;
		ETokenType type;

		Token(EOperand d);
		Token(EOperator r);

		bool operator==(Token const & rhs) const;
		bool operator!=(Token const & rhs) const;

		bool isOperand()  const noexcept;
		bool isOperator() const noexcept;

		bool isBool()     const noexcept;
		bool isVariable() const noexcept;

		bool isNot()   const noexcept;
		bool isAnd()   const noexcept;
		bool isOr()    const noexcept;
		bool isXor()   const noexcept;
		bool isImply() const noexcept;
		bool isEqual() const noexcept;
	};

	// - Attributes ------------------------------------------------------------
	// - Constructors & Destructor & Assignment --------------------------------
	Node(Token token);
	~Node() = default;

	// - Operators -------------------------------------------------------------
	// - Methods ---------------------------------------------------------------
	self_ref_type toNegationNormalForm();
	self_ref_type toConjunctiveNormalForm();

	self_ref_type simplify();

	// - Getters & Setters -----------------------------------------------------
	Token const &       getToken() const noexcept;
	self_const_ptr_type getLeft()  const noexcept;
	self_const_ptr_type getRight() const noexcept;

	std::set<EOperand> getVariables() const;

	std::string toString() const;

	// - Friends ---------------------------------------------------------------
	friend self_ptr_type parse(std::string const & formula);

// =============================================================================
// Protected
// =============================================================================
protected:
	// - Types -----------------------------------------------------------------
	// - Attributes ------------------------------------------------------------
	// - Constructors & Destructor & Assignment --------------------------------
	// - Operators -------------------------------------------------------------
	// - Methods ---------------------------------------------------------------
	// - Getters & Setters -----------------------------------------------------

// =============================================================================
// Private
// =============================================================================
private:
	// - Types -----------------------------------------------------------------
	// - Attributes ------------------------------------------------------------
	Token _token;
	self_ptr_type _left;
	self_ptr_type _right;

	// - Constructors & Destructor & Assignment --------------------------------
	Node() = delete;

	// Node(self_const_ref_type other) = default;
	// Node(self_mov_type other) noexcept = default;

	// self_ref_type operator=(self_const_ref_type other) = default;
	// self_ref_type operator=(self_mov_type other) noexcept = default;

	// - Operators -------------------------------------------------------------
	// - Methods ---------------------------------------------------------------
	void toNegationNormalFormRecursion();
	void toConjunctiveNormalFormRecursion();

	void simplifyRecursion();

	bool convertImply();
	bool convertEqual();
	bool convertXor();
	bool convertDeMorganLaws();

	bool applyIdempotency();
	bool applyDoubleNegation();
	bool applyCommutativity();
	bool applyAssociativity();
	bool applyDistributivity();
	bool applyAbsorptivity();

	// - Getters & Setters -----------------------------------------------------

};

// =============================================================================
// Overload
// =============================================================================

} // End - Namespace

#endif
