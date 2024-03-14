//
// Created by Melanie Prettyman on 3/13/24.
//

#include "val.h"
#include <sstream>

//---------------------------------------------
//                NumVal CLASS
//---------------------------------------------
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

    if (!rhsNum) throw std::runtime_error("Invalid equality between non-number values.");

    return this->val == rhsNum->val;
}

void NumVal::print (std::ostream &ostream){
    ostream<<std::to_string(val);
}

//NumVal to_expr function returns the value of the NumVal as an Num Expr
Expr* NumVal::to_expr() {
    return new Num(val);
}

//NumVal is_true function returns error message since you cannot check if a number is true
bool NumVal::is_true() {
    throw std::runtime_error("Numbers cannot be booleans.");
    return false;
}

//---------------------------------------------
//                BoolVal CLASS
//---------------------------------------------

//BoolVal constructor
// val = true or false
BoolVal::BoolVal(bool val) {
    this->val = val;
}

//BoolVal is_true function returns true if the value of the BoolVal is true, and false if the value of the BoolVal is false
bool BoolVal::is_true() {
    return val;
}

//BoolVal add_to function returns error message since you cannot add two boolean values
Val* BoolVal::add_to(Val* rhs) {
    throw std::runtime_error("Cannot add boolean values.");
}

//BoolVal mult_with function returns error message since you cannot multiply two boolean values
Val* BoolVal::mult_with(Val* rhs) {
    throw std::runtime_error("Cannot multiply boolean values.");
}

//BoolVal equals function checks if two BoolVals are equal
bool BoolVal::equals(Val* rhs) {
    BoolVal* rhsBool = dynamic_cast<BoolVal*>(rhs);

    if (!rhsBool) throw std::runtime_error("Invalid equality between values.");

    if(val == rhsBool->val){
        return true;
    } else {
        return false;
    }
}

//BoolVal print function returns "_true" if the value of the BoolVal is true, and "_false" if the value of the BoolVal is false
void BoolVal::print(std::ostream &ostream){
    ostream << (val ? "_true" : "_false");
}

//BoolVal to_expr function returns the value of the BoolVal as a Bool Expr
Expr* BoolVal::to_expr(){
    return new BoolExpr(this->val);
}