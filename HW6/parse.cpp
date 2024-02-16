#include <iostream>
#include "parse.hpp"



// Parses a numeric expression from the input stream, handling negative numbers and ensuring valid numeric input.
Expr *parse_num(std::istream &inn) {
    int n = 0;
    bool negative = false; // Flag to track if the number is negative
    bool digitSeen = false; // Flag to ensure at least one digit is seen

    if (inn.peek() == '-') { // Check for negative sign
        negative = true;
        consume(inn, '-'); // Consume the '-' sign
    }

    while (true) { // Loop to parse the digits of the number
        int c = inn.peek();
        if (isdigit(c)) {
            consume(inn, c); // Consume the digit
            n = n * 10 + (c - '0'); // Build the number
            digitSeen = true;
        } else {
            break; // Break if no more digits are found
        }
    }

    if (negative && !digitSeen) {
        throw std::runtime_error("Invalid input"); // Throw error if '-' is not followed by any digits
    }

    if (negative) {
        n = -n; // Apply the negative sign to the number
    }

    return new Num(n); // Return the parsed number as a Num expression
}

// Parses a variable expression from the input stream, constructing a variable name from consecutive alphabetic characters.
Expr *parse_var(std::istream &inn) {
    std::string var;
    while (true) {
        int c = inn.peek();
        if (isalpha(c)) { // Check for alphabetic character
            consume(inn, c); // Consume the character
            var += static_cast<char>(c); // Append the character to the variable name
        } else {
            break; // Break if no more valid characters for variable name are found
        }
    }

    return new VarExpr(var); // Return the parsed variable as a VarExpr
}

// Parses a _let expression from the input stream, including parsing of lhs variable, rhs expression, and the body expression.
Expr *parse_let(std::istream &in) {
    skip_whitespace(in); // Skip leading whitespace
    std::string _let = "_let";
    consumeWord(in, _let); // Consume the "_let" keyword

    skip_whitespace(in);
    Expr *lhs = parse_var(in); // Parse the lhs variable

    skip_whitespace(in);
    consume(in, '='); // Consume the '=' sign

    skip_whitespace(in);
    Expr *rhs = parse_expr(in); // Parse the rhs expression

    std::string _in = "_in";
    consumeWord(in, _in); // Consume the "_in" keyword

    skip_whitespace(in);
    Expr *body = parse_expr(in); // Parse the body expression

    return new class _let(lhs->to_string(), rhs, body); // Return the parsed _let expression
}

// Consumes a specific word from the input stream, ensuring the input stream matches the expected keyword.
static void consumeWord(std::istream &in, std::string word) {
    for(char letter: word) { // Iterate through each letter of the word
        int c = in.peek();
        if (c == letter) {
            consume(in, c); // Consume the letter if it matches
        }
    }
}

// Consumes a single expected character from the input stream, throwing an error if the character does not match the expectation.
static void consume(std::istream &in, int expect) {
    int c = in.get(); // Get the next character from the stream
    if (c != expect) {
        throw std::runtime_error("consume mismatch"); // Throw error if the character does not match the expected one
    }
}

// Skips whitespace characters in the input stream to prepare for parsing the next token.
void skip_whitespace(std::istream &in) {
    while (1) {
        int c = in.peek(); // Peek the next character without consuming it
        if (!isspace(c)) // Check if it's not a whitespace character
            break; // Break the loop if no more whitespace
        consume(in, c); // Consume the whitespace character
    }
}


//<multican> = <number>
//       | (<expr>)
//       | (<var>)
//       | _let

Expr *parse_multicand(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();
    if ((c == '-') || isdigit(c)) {
        return parse_num(in);
    }
    else if (c == '(') {
        consume(in, '(');
        Expr *e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')') {
            throw std::runtime_error("missing close parenthesis");
        }
        return e;

    }
    else if(isalpha(c)){
        return parse_var(in);
    }
    else if (c == '_') {
        return parse_let(in);
    }
    else {
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
        skip_whitespace(in) ;
        //parse rhs
        Expr *rhs = parse_addend(in);
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
    } else{
        return e;

    }
}




Expr *parse(std::istream &in) {
    Expr* e;
    // Attempt to parse an expression from the input stream.
    e = parse_expr(in);
    skip_whitespace(in);
    // Check if the end of the file (input stream) has not been reached.
    if ( !in.eof() ) {
        // Throw an error for any remaining non-whitespace character.
        throw std::runtime_error("Invalid input");
    }
    // Return the pointer to the parsed expression.
    return e;
}











