#include "evaluator.h"

#include <algorithm>
#include <sstream>
#include <cctype>

const std::string binOp = "+-*/%";
const std::string symbols = "()";
const std::string validTokens = binOp + symbols;

enum class Token {
	ADD, SUB, MULT, DIV, MOD, PAR_LEFT, PAR_RIGHT, UNKNOWN
};

Token getToken(char c) {
	size_t idx = validTokens.find(c);
	return idx != std::string::npos ? (Token) idx : Token::UNKNOWN;
}

bool validToken(char c) { return getToken(c) != Token::UNKNOWN; }

bool isBinop(char c) { return getToken(c) < Token::PAR_LEFT; }

int opCompute(int a, int b, Token op) {
	switch (op) {
		case Token::ADD:
			return a + b;
		case Token::SUB:
			return a - b;
		case Token::MULT:
			return a * b;
		case Token::DIV:
			return a / b;
		case Token::MOD:
			return a % b;
		default:
			return 0;
	}
}

// Fonction permettant de récupérer un nombre à partir d'une expression.
// Renvoie le nombre de caractères formant le nombre.
int parse_integer(const std::string& expr, std::size_t& num_size) {
	if (!std::isdigit(expr[0])) return 0;
	std::istringstream iss(expr);
	char c = iss.get();
	std::string num;
	do {
		num += c;
		c = iss.get();
		if (!std::isdigit(c)) { iss.putback(c); }
	} while (std::isdigit(c));
	num_size = num.size();
	return std::stoi(num);
}

std::string remove_blanks(const std::string& str) {
	std::string copy = str;
	copy.erase(std::remove_if(copy.begin(), copy.end(), ::isblank), copy.end());
	return copy;
}

// Fonction permettant de récupérer la position de la parenthèse fermante
// correspondant à la parenthèse ouvrante actuelle.
std::size_t get_outermost_parenthesis(const std::string& expr) {
	size_t depth = 0;
	for (size_t i = 0; i < expr.size(); ++i) {
		if (getToken(expr[i]) == Token::PAR_LEFT)
			++depth;
		if (getToken(expr[i]) == Token::PAR_RIGHT) {
			--depth;
			if (depth == 0)
				return i;
		}
	}
	return (size_t) -1;
}

int evalue(const std::string& expr) {
	std::string expr_copy = remove_blanks(expr);
	std::size_t size = expr_copy.size();

   // On construit un arbre correspondant à l'expression.
   // Exemple avec (3 * 4) + (6 - 2)
   //                      +
   //                     / \
   //                    *   -
   //                   / \ / \
   //                  3  4 6  2
	if (getToken(expr_copy[0]) == Token::PAR_LEFT) {
		size_t outerId = get_outermost_parenthesis(expr_copy);
		if (outerId == -1) { throw bad_expression(); }
		if (isBinop(expr_copy[outerId + 1]))

         // On sépare en deux une expression binaire en passant les opérandes à
         // gauche et à droite de l'arbre.
			return opCompute(evalue(expr_copy.substr(1, outerId - 1)),
							 evalue(expr_copy.substr(outerId + 2, size -outerId)),
							 getToken(expr_copy[outerId + 1]));
		return evalue(expr_copy.substr(1, outerId - 1));
	} else if (std::isdigit(expr_copy[0])) {
		size_t num_size;
		int num = parse_integer(expr, num_size);
		if (num_size == expr_copy.size()) { return num; }
		if (isBinop(expr_copy[num_size])) {
			return opCompute(num, evalue(expr_copy.substr(num_size + 1, size - num_size)),getToken(expr_copy[num_size]));
		} else {
			throw bad_expression();
		}
	} else {
		throw bad_expression();
	}
}
