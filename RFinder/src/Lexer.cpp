#include "../include/Lexer.h"

#include <iostream>
#include <math.h>
#include <stdexcept>

std::vector<Token> Lexer::tokenize(std::string_view expr) {
    if (expr.empty()) return {};
    
    std::vector<Token> tokens;

    int i = 0;
    while (i < expr.length()) {
        char c = expr[i];

        // Whitespaces (skip)
        if (isspace(c)) { i++; continue; }

        // Numbers
        if (isdigit(c) || c == '.') {
            int start = i;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) i++;
            tokens.push_back({TokenType::Number, expr.substr(start, i - start), start});
            continue;
        }

        // Alphanumerical
        if (isalpha(c)) {
            int start = i;
            while (i < expr.length() && isalpha(expr[i])) i++;
            tokens.push_back({TokenType::Identifier, expr.substr(start, i - start), start});
            continue;
        }

        switch (c) {
            case '+': tokens.push_back({TokenType::Plus, "+", i}); break;
            case '-': tokens.push_back({TokenType::Minus, "-", i}); break;
            case '*': tokens.push_back({TokenType::Star, "*", i}); break;
            case '/': tokens.push_back({TokenType::Slash, "/", i}); break;
            case '^': tokens.push_back({TokenType::Caret, "^", i}); break;
            case '(': tokens.push_back({TokenType::LParen, "(", i}); break;
            case ')': tokens.push_back({TokenType::RParen, ")", i}); break;
            case '=': tokens.push_back({TokenType::Equal, "=", i}); break;
            default: throw std::runtime_error("Unknown character: " + std::string(1, c));
        }
        i++;
    }

    tokens.push_back({TokenType::End, "", i});
    
    return tokens;
}

void Lexer::print(const std::vector<Token> &tokens) {
    for (const auto& token : tokens) {
        std::string typeStr;
        switch (token.type) {
            case TokenType::Number: typeStr = "Number"; break;
            case TokenType::Identifier: typeStr = "Identifier"; break;
            case TokenType::Plus: typeStr = "Plus"; break;
            case TokenType::Minus: typeStr = "Minus"; break;
            case TokenType::Star: typeStr = "Star"; break;
            case TokenType::Slash: typeStr = "Slash"; break;
            case TokenType::Caret: typeStr = "Caret"; break;
            case TokenType::LParen: typeStr = "LParen"; break;
            case TokenType::RParen: typeStr = "RParen"; break;
            case TokenType::Comma: typeStr = "Comma"; break;
            case TokenType::End: typeStr = "End"; break;
            default: typeStr = "Unknown"; break;
        }
        std::cout << "Token(Type: " << typeStr << ", Value: '" << token.value << "', Pos: " << token.pos << ")\n";
    }
}