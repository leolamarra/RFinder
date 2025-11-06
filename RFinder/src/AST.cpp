#include "AST.h"

#include <cmath>

double Number::eval(double x) { return val; }

double Var::eval(double x) { return x; }

double BinOp::eval(double x) {
    const double a = l->eval(x);
    const double b = r->eval(x);

    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : NAN;
        case '^': return std::pow(a, b);
        default: return NAN;
    }
}

double Function::eval(double x) {
    const double a = arg->eval(x);

    if (name == "sin") return std::sin(a);
    if (name == "cos") return std::cos(a);
    if (name == "tan") return std::tan(a);
    if (name == "exp") return std::exp(a);
    if (name == "log") return std::log(a);
    if (name == "sqrt") return std::sqrt(a);

    return NAN;
}
