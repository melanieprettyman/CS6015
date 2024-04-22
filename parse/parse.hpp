
#ifndef parse_hpp
#include "Expr.h"
#define parse_hpp

#include <stdio.h>

Expr *parse_num(std::istream &in);
static void consume(std::istream &in, int expect);
static void skip_whitespace(std::istream &in);
Expr *parse_expr(std::istream &in);

#endif

