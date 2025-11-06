#pragma once
#include <vector>

#include "MathFunction.h"
#include "Token.h"

class Parser {
public:
    Parser() = default;
    MathFunction parse(const std::vector<Token>& tokens, char var = 'x');

private:
    const std::vector<Token>* tokens = nullptr;
    size_t index = 0;
    char var = 'x';

    const Token& peek() const { return (*tokens)[index]; }
    const Token& previous() const { return (*tokens)[index - 1]; }
    bool isAtEnd() const { return peek().type == TokenType::End; }

    const Token& advance() {
        if (!isAtEnd()) index++;
        return previous();
    }

    bool match(std::initializer_list<TokenType> types) {
        for (const auto t : types) {
            if (!isAtEnd() && peek().type == t) {
                advance();
                return true;
            }
        }
        return false;
    }

    void consume(TokenType type, const std::string& msg) {
        if (!isAtEnd() && peek().type == type) {
            advance();
            return;
        }
        throw std::runtime_error("Errore di parsing: " + msg);
    }

    std::unique_ptr<Node> parseEquation();
    std::unique_ptr<Node> parseExpression();
    std::unique_ptr<Node> parseTerm();
    std::unique_ptr<Node> parsePower();
    std::unique_ptr<Node> parseFactor();
};
