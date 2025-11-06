#pragma once
#include <vector>
#include <string>

#include "Token.h"

class Lexer {
public:
    static std::vector<Token> tokenize(std::string_view expr);
    static void print(const std::vector<Token> &tokens);
};
