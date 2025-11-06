#include "Parser.h"

#include <cmath>

MathFunction Parser::parse(const std::vector<Token> &tokens, char var) {
    this->tokens = &tokens;
    this->var = var;
    return parseEquation();
}


std::unique_ptr<Node> Parser::parseEquation() {
    auto left = parseExpression();
    if ( match({TokenType::Equal}) ) {
        auto right = parseExpression();
        return std::make_unique<BinOp>('-', std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Node> Parser::parseExpression() {
    auto left = parseTerm();
    while ( match({TokenType::Plus, TokenType::Minus}) ) {
        char op = !previous().value.empty() ? previous().value[0] : '?';
        auto right = parseTerm();
        left = std::make_unique<BinOp>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Node> Parser::parseTerm() {
    auto left = parsePower();

    while (true) {
        if ( match({TokenType::Star, TokenType::Slash}) ) {
            char op = !previous().value.empty() ? previous().value[0] : '?';
            auto right = parsePower();
            left = std::make_unique<BinOp>(op, std::move(left), std::move(right));
        }
        else if ( !isAtEnd() && peek().type == TokenType::Identifier ) {
            // implicit multiplication: next token is an identifier -> parse it as right operand
            auto right = parsePower();
            left = std::make_unique<BinOp>('*', std::move(left), std::move(right));
        }
        else break;
    }

    return left;
}

std::unique_ptr<Node> Parser::parsePower() {
    auto left = parseFactor();
    while ( match({TokenType::Caret}) ) {
        auto right = parseFactor();
        left = std::make_unique<BinOp>('^', std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Node> Parser::parseFactor() {
    if ( match({TokenType::Number}) ) {
        auto sv = previous().value;
        if (sv.empty()) throw std::runtime_error("Token Number senza valore");
        std::string s(sv.data(), sv.size());
        double val;
        try { val = std::stod(s); }
        catch (const std::exception&) { throw std::runtime_error("Numero non valido: " + s); }
        return std::make_unique<Number>(val);
    }

    if ( match({TokenType::Identifier}) ) {
        auto sv = previous().value;
        if (sv.empty()) throw std::runtime_error("Token Identifier senza valore");

        // TODO: Implement actual const recognition in parser and remove this if-mess
        // costanti recognize
        if (sv == "pi") {
            return std::make_unique<Number>(M_PI);
        }
        if (sv == "e") {
            return std::make_unique<Number>(M_E);
        }

        // nome come variabile?
        std::string name(sv.data(), sv.size());
        if (!name.empty() && name[0] == var) {
            return std::make_unique<Var>();
        }

        // funzione: name(args)
        consume(TokenType::LParen, "Assente '(' dopo la funzione");
        auto arg = parseExpression();
        consume(TokenType::RParen, "Manca ')' dopo la funzione");
        return std::make_unique<Function>(std::move(name), std::move(arg));
    }

    if ( match({TokenType::LParen}) ) {
        auto expr = parseExpression();
        consume(TokenType::RParen, "Manca ')'");
        return expr;
    }

    auto psv = peek().value;
    std::string p(psv.data(), psv.size());
    throw std::runtime_error(std::string("Token inaspettato: ") + (p.empty() ? "<empty>" : p));
}