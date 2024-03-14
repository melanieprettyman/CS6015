//
// Created by Melanie Prettyman on 3/13/24.
//

#include "val.h"
#include <sstream>

//NumVal constructor
NumVal::NumVal(int val) {
    this->val = val;
}

//NumVal add_to function adds two NumVals together
Val* NumVal::add_to(Val* rhs) {
    NumVal* rhsNum = dynamic_cast<NumVal*>(rhs);
    if (!rhsNum) throw std::runtime_error("Invalid addition between non-number values.");
    return new NumVal(val + rhsNum->val);
}

//NumVal mult_with function multiplies two NumVals together
Val* NumVal::mult_with(Val* rhs) {
    NumVal* rhsNum = dynamic_cast<NumVal*>(rhs);
    if (!rhsNum) throw std::runtime_error("Invalid multiplication between non-number values.");
    return new NumVal(val * rhsNum->val);
}

//NumVal equals function checks if two NumVals are equal
bool NumVal::equals(Val* rhs) {
    NumVal* rhsNum = dynamic_cast<NumVal*>(rhs);
    return rhsNum && val == rhsNum->val;
}

//NumVal to_string function returns the value of the NumVal as a string
std::string NumVal::to_string() {
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

//NumVal to_expr function returns the value of the NumVal as an Num Expr
Expr* NumVal::to_expr() {
    return new Num(val);
}
