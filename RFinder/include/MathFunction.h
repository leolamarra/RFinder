#pragma once

#include "AST.h"

struct MathFunction {
    std::unique_ptr<Node> f;
    
    MathFunction(std::unique_ptr<Node> function) : f(std::move(function)) {}
    double eval(double x) const { return f->eval(x); }
};