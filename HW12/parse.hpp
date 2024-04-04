
#ifndef parse_hpp
#include "Expr.h"
#define parse_hpp

#include <stdio.h>

PTR(Expr)parse_num(std::istream &in);
static void consume(std::istream &in, int expect);
static void skip_whitespace(std::istream &in);
static PTR(Expr)parse_expr(std::istream &in);
PTR(Expr)parse_addend(std::istream &in);
PTR(Expr)parse_multicand(std::istream &in);
PTR(Expr)parse(std::istream &in);
PTR(Expr)parse_var(std::istream &inn);
static void consumeWord(std::istream &in, std::string word);

static void consume(std::istream &in, int expect);

PTR(Expr)parse_if(std::istream &inn);

PTR(Expr)parse_comparg(std::istream &in);

PTR(Expr)parse_fun(std::istream &in);

PTR(Expr) parse_inner(std::istream &in);

#endif

