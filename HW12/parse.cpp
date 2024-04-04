#include <iostream>
#include "parse.hpp"



// Parses a numeric expression from the input stream, handling negative numbers and ensuring valid numeric input.
PTR(Expr)parse_num(std::istream &inn) {
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

    return NEW(Num)(n); // Return the parsed number as a Num expression
}

// Parses a variable expression from the input stream, constructing a variable name from consecutive alphabetic characters.
PTR(Expr)parse_var(std::istream &inn) {
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

    return NEW(VarExpr)(var); // Return the parsed variable as a VarExpr
}

// Parses a _let expression from the input stream, including parsing of lhs variable, rhs expression, and the body expression.
PTR(Expr)parse_let(std::istream &in) {
    skip_whitespace(in); // Skip leading whitespace
    std::string _let = "_let";
    consumeWord(in, _let); // Consume the "_let" keyword

    skip_whitespace(in);
    PTR(Expr)lhs = parse_var(in); // Parse the lhs variable

    skip_whitespace(in);
    consume(in, '='); // Consume the '=' sign

    skip_whitespace(in);
    PTR(Expr)rhs = parse_expr(in); // Parse the rhs expression

    std::string _in = "_in";
    consumeWord(in, _in); // Consume the "_in" keyword

    skip_whitespace(in);
    PTR(Expr)body = parse_expr(in); // Parse the body expression

    return NEW(class _let)(lhs->to_string(), rhs, body); // Return the parsed _let expression
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

//<if> = _if <expr> _then <expr> _else <expr>
PTR(Expr)parse_if(std::istream &inn){
    skip_whitespace(inn);
    PTR(Expr) ifPart = parse_expr(inn);

    skip_whitespace(inn);
    consumeWord(inn, "_then");
    PTR(Expr) thenPart = parse_expr(inn);

    skip_whitespace(inn);
    consumeWord(inn, "_else");

    skip_whitespace(inn);
    PTR(Expr) elsePart = parse_expr(inn);

    return NEW (IfExpr)(ifPart, thenPart, elsePart);
}

static std::string parse_keyword(std::istream & inn) {
    std::string keyword;

    while (true) {
        int letter = inn.peek();
        if (isalpha(letter)) {
            consume(inn, letter);
            char c = letter;
            keyword += c;
        }
        else
            break;
    }

    return keyword;
}

PTR(Expr)parse_fun(std::istream &in) {

    skip_whitespace(in);
    consume(in, '(');

    std::string arg = parse_var(in)->to_string(); // Assuming `parse_var` returns a VarExpr*

    consume(in, ')');
    skip_whitespace(in);

    PTR(Expr)body = parse_expr(in);
    return NEW(FunExpr)(arg, body);
}

//<inner> = <number>
        //| (<expr>)
        //| <var>
        //| _true
        //| _false
        //| _let <var> = <expr> _in <expr>
        //| _fun (<var>) <expr>
        //| _if <expr> _then <expr> _else <expr>

PTR(Expr)parse_inner(std::istream &in) {
    std::string keyword;

    skip_whitespace(in);
    int c = in.peek();
    if ((c == '-') || isdigit(c)) {
        return parse_num(in);
    }
    else if (c == '(') {
        consume(in, '(');
        PTR(Expr)e = parse_expr(in);
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
        consume(in, '_');
        keyword = parse_keyword(in);

        if(keyword == "let"){
            return parse_let(in);
        }
        else if(keyword == "if"){
            return parse_if(in);
        }
        else if(keyword == "true"){
            return NEW(BoolExpr)(true);
        }
        else if(keyword == "false"){
            return NEW(BoolExpr)(false);
        }
        else if(keyword == "fun"){
            return parse_fun(in);
        }
        else{
            throw std::runtime_error("invalid input");
        }
    }
    else {
        consume(in, c);
        throw std::runtime_error("invalid input");
    }
}

//<multicand> = <inner>
//            | <multicand>(<expr>)

PTR(Expr) parse_multicand(std::istream &in) {
    PTR(Expr) e = parse_inner(in);
    while (in.peek() == '(') {
        consume(in, '(');
        PTR(Expr) actual_arg = parse_expr(in);
        consume(in, ')');
        e = NEW(CallExpr)(e, actual_arg);
    }
    return e;
}

//<addend> = <multican>
//        | <multicand> * <addend>
PTR(Expr)parse_addend(std::istream &in) {
    PTR(Expr)e = parse_multicand(in);
    skip_whitespace(in);

    //Check if mult expression
    while (in.peek() == '*') {
        consume(in, '*');
        PTR(Expr)rhs = parse_addend(in);
        e = NEW(Mult)(e, rhs);
        skip_whitespace(in);
    }
    return e;
}


//<comparg> = <addend>
//       | <addend> + <expr>
PTR(Expr)parse_comparg(std::istream &in) {
    PTR(Expr)e = parse_addend(in);
    skip_whitespace(in);

    //Check if add expression
    while (in.peek() == '+') {
        consume(in, '+');
        PTR(Expr)rhs = parse_addend(in);
        e = NEW(Add)(e, rhs);
        skip_whitespace(in);
    }
    return e;
}



//<expr> = <comparg>
//      | <comparg> == <expr>
static PTR(Expr) parse_expr(std::istream &in) {
    PTR(Expr) e = parse_comparg(in); // Start with the next highest precedence operation
    skip_whitespace(in);
    if (in.peek() == '=') {
        consume(in, '=');
        if (in.peek() != '=') throw std::runtime_error("Expected '==' for equality check.");
        consume(in, '=');
        PTR(Expr) rhs = parse_expr(in); // Recursive call to support right associativity of equality
        e = NEW(EqExpr)(e, rhs);
    }
    return e;
}

// Parses an expression from the input stream, handling whitespace and ensuring the input stream is fully consumed.
PTR(Expr)parse(std::istream &in) {
    PTR(Expr) e;
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









