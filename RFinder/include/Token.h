#pragma once

enum class TokenType {
    Number,
    Identifier,
    Plus, Minus, Star, Slash, Caret,
    LParen, RParen, Comma,
    Equal,
    End
};

struct Token {
    TokenType type;
    std::string_view value;
    int pos;
};

inline Token ERR_TOKEN {TokenType::End, "Error", -1};