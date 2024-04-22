#include "parse.hpp"

Expr *parse_num(std::istream &in) {
    
    int n = 0;
    bool negative = false;

    if(in.peek() == '-'){
        negative = true;
        consume(in, '-');
    }
    while (1) {
        int c = in.peek();

        if (isdigit(c))
        {
            consume(in, c);
            n = n*10 + (c - '0');
        }
        else
            break;
    }
    if(negative){
        n = -n;
    }
    
    return new Num(n);
}

static void consume(std::istream &in, int expect) {
    int c = in.get();
    if (c != expect)
        throw std::runtime_error("consume mismatch");
}

static void skip_whitespace(std::istream &in) {
    while (1) {
        int c = in.peek();
        if (!isspace(c))
            break;
        consume(in, c);
    }
}
Expr *parse_expr(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();
    if ((c == '-') || isdigit(c))
        return parse_num(in);
    else {
        consume(in, c);
        throw std::runtime_error("invalid input");
    }
}

//int main() {
//    while (1) {
//        Expr *e = parse_expr(std::cin);
//        e->pretty_print(std::cout);
//        std::cout << "\n";
//        skip_whitespace(std::cin);
//        if (std::cin.eof())
//            break;
//    }
//    return 0;
//}


