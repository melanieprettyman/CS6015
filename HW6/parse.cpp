#include <iostream>
#include "parse.hpp"



Expr *parse_num(std::istream &inn) {
    int n = 0;
    bool negative = false;
    
    if (inn.peek() == '-') {
        negative = true;
        consume (inn, '-');
        
    }

    while (1) {
        int c = inn.peek(); 
        if (isdigit(c))
        {
            consume(inn, c);
            n = n*10 + (c - '0');
        }
        else
            break;
    }
    
    if (negative)
        n = -n;
  
    return new Num(n);
}


static void consume(std::istream &in, int expect) {
    int c = in.get();
    if (c!=expect) {
        throw std::runtime_error("consume mismatch");
    }
}

void skip_whitespace(std::istream &in) {
  while (1) {
    int c = in.peek();
    if (!isspace(c))
      break;
    consume(in, c);
      }
}

//<multican> = <number>
//       | (<expr>)
Expr *parse_multicand(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();
    if ((c == '-') || isdigit(c))
        return parse_num(in);
    else if (c == '(') {
        consume(in, '(');
        Expr *e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')')
            throw std::runtime_error("missing close parenthesis");
        return e;
    } else {
        consume(in, c);
        throw std::runtime_error("invalid input");
    }
}
//<addend> = <multican>
//        | <multicand> * <addend>
Expr *parse_addend(std::istream &in) {
    Expr *e;
    //read in LHS
    e = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();

    //Check if mult expression
    if (c == '*') {
        //consume "*", after mult is the rhs <expr>
        consume(in, '*');
        //parse rhs
        Expr *rhs = parse_expr(in);
        //return new mult
        return new Mult(e, rhs);
    } else
        return e;
}

//<expr> = <addend>
//       | <addend> + <expr>
static Expr *parse_expr(std::istream &in) {
    Expr *e;
    //read in LHS
    e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();

    //Check if add expression
    if (c == '+') {
        //consume "+", after plus is the rhs <expr>
        consume(in, '+');
        Expr *rhs = parse_expr(in);
        return new Add(e, rhs);
    } else
        return e;
}








