#include <iostream>
#include <iomanip>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"

static std::string format_double(double v) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(10) << v;
    std::string s = oss.str();
    if (s.find('.') != std::string::npos) {
        while (!s.empty() && s.back() == '0') s.pop_back();
        if (!s.empty() && s.back() == '.') s.pop_back();
    }
    return s;
}

int main() {
    std::string input;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, input);
    const auto tokens = Lexer::tokenize(input);

    Parser parser;
    const auto f_x = parser.parse(tokens);

    double x = 0;
    while (true) {
        std::cout << "Enter value of 'x': ";
        if (!(std::cin >> x)) break;
        std::cout << format_double(f_x.eval(x)) << std::endl;
    }

    return 0;
}
