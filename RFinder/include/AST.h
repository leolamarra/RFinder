#pragma once
#include <memory>
#include <utility>

// Base AST Node
struct Node {
    virtual double eval(double x) = 0;
    virtual ~Node() = default;
};

// Numbers
struct Number : Node {
    double val;
    Number(double val) : val(val) {}
    double eval(double x) override;
};

// Variable 'x'
struct Var : Node {
    double eval(double x) override;
};

// Binary Operations (+, -, *, /, ^)
struct BinOp : Node {
    char op;
    std::unique_ptr<Node> l, r;

    BinOp(char op, std::unique_ptr<Node> l, std::unique_ptr<Node> r) : op(op), l(std::move(l)), r(std::move(r)) {}
    double eval(double x) override;
};

struct Function : Node {
    std::string name;
    std::unique_ptr<Node> arg;

    Function(std::string name, std::unique_ptr<Node> arg) : name(std::move(name)), arg(std::move(arg)) {}
    double eval(double x) override;
};