
#ifndef parse_hpp
#include "Expr.h"
#define parse_hpp

#include <stdio.h>

Expr *parse_num(std::istream &in);
static void consume(std::istream &in, int expect);
static void skip_whitespace(std::istream &in);
static Expr *parse_expr(std::istream &in);
Expr *parse_addend(std::istream &in);
Expr *parse_multicand(std::istream &in);
Expr *parse(std::istream &in);
Expr *parse_var(std::istream &inn);
static void consumeWord(std::istream &in, std::string word);

static void consume(std::istream &in, int expect);

#endif

