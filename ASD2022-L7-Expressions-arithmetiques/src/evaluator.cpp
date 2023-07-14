#include "evaluator.h"
#include <stack> // std::stack
#include <sstream>
#include <iostream>

const std::string binOp = "+-*/%";
const std::string symbols = "()";
const std::string validTokens = binOp + symbols;

enum class Token { ADD, SUB, MULT, DIV, MOD, PAR_LEFT, PAR_RIGHT, UNKNOWN };

// On considère deux types de contextes, soit lorsque nous sommes dans des
// opérations binaires ou lorsque nous sommes dans des parenthèses.
enum class Context { PAR_GROUP, BINOP };

Token getToken(char c);

bool validToken(char c);

Token getToken(char c) {
    size_t idx = validTokens.find(c);
    return idx != std::string::npos ? (Token) idx : Token::UNKNOWN;
}

bool validToken(char c) { return getToken(c) != Token::UNKNOWN; }

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

int evalue(const std::string &expr) {
    std::stack<Token> ops;
    std::stack<int> values;
    std::stack<Context> ctx;
    std::istringstream iss(expr);
    char currentChar;

    while (iss.rdbuf()->in_avail() != 0) {
        iss.get(currentChar);

        if (getToken(currentChar) == Token::PAR_LEFT) {
            ctx.push(Context::PAR_GROUP);
        } else if (std::isblank(currentChar)) {
            continue;
        } else if (validToken(currentChar)) {
            if (getToken(currentChar) == Token::PAR_RIGHT) {

               // Si l'opération est invalide (pas dans une opération binaire ou
               // parenthèses). On vérifie la taille des piles pour ne pas avoir
               // d'erreur lorsque l'on pop.
                if (ctx.empty() || (ctx.size() == 1 && ctx.top() == Context::BINOP) || values.size() < 2 || ops.empty())
                    throw bad_expression();

                int b = values.top();
                values.pop();
                int a = values.top();
                values.pop();
                int result = opCompute(a, b, ops.top());
                ops.pop();
                values.push(result);
                if (ctx.top() == Context::BINOP) ctx.pop();
                ctx.pop();
            } else {

               // On vérifie que l'on n'est pas déjà dans une opération binaire.
                if (ctx.top() != Context::BINOP) {
                    ops.push(getToken(currentChar));
                    ctx.push(Context::BINOP);
                } else throw bad_expression();
            }
        } else if (std::isdigit(currentChar)) {
            std::string number = "";
            do {
                number += currentChar;
                iss.get(currentChar);
                if (!std::isdigit(currentChar)) {
                    iss.putback(currentChar);
                }
            } while (std::isdigit(currentChar));
            values.push(std::stoi(number));
            if (ctx.top() == Context::BINOP) ctx.pop();
        } else {
            throw bad_expression();
        }
    }
    if (ctx.size() > 0) throw bad_expression();
    return values.top();
}
