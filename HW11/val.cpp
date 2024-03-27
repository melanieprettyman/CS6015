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
PTR(Val) NumVal::add_to(PTR(Val) rhs) {
    PTR(NumVal) rhsNum = CAST(NumVal)(rhs);
    if (!rhsNum) throw std::runtime_error("Invalid addition between non-number values.");
    return NEW(NumVal)(val + rhsNum->val);
}

//NumVal mult_with function multiplies two NumVals together
PTR(Val) NumVal::mult_with(PTR(Val) rhs) {
    PTR(NumVal) rhsNum = CAST(NumVal)(rhs);
    if (!rhsNum) throw std::runtime_error("Invalid multiplication between non-number values.");
    return NEW(NumVal)(val * rhsNum->val);
}

//NumVal equals function checks if two NumVals are equal
bool NumVal::equals(PTR(Val) rhs) {
    PTR(NumVal) rhsNum = CAST(NumVal)(rhs);

    if (!rhsNum) throw std::runtime_error("Invalid equality between non-number values.");

    return this->val == rhsNum->val;
}

void NumVal::print (std::ostream &ostream){
    ostream<<std::to_string(val);
}

//NumVal to_expr function returns the value of the NumVal as an Num Expr
PTR(Expr) NumVal::to_expr() {
    return NEW(Num)(val);
}

//NumVal is_true function returns error message since you cannot check if a number is true
bool NumVal::is_true() {
    throw std::runtime_error("Numbers cannot be booleans.");
    return false;
}

PTR(Val)NumVal::call(PTR(Val)actual_arg) {
    throw std::runtime_error("cannot call NumVal");
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
PTR(Val) BoolVal::add_to(PTR(Val) rhs) {
    throw std::runtime_error("Cannot add boolean values.");
}

//BoolVal mult_with function returns error message since you cannot multiply two boolean values
PTR(Val) BoolVal::mult_with(PTR(Val) rhs) {
    throw std::runtime_error("Cannot multiply boolean values.");
}

//BoolVal equals function checks if two BoolVals are equal
bool BoolVal::equals(PTR(Val) rhs) {
    PTR(BoolVal) rhsBool = CAST(BoolVal)(rhs);

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
PTR(Expr) BoolVal::to_expr(){
    return NEW(BoolExpr)(this->val);
}

PTR(Val)BoolVal::call(PTR(Val)actual_arg) {
    throw std::runtime_error("cannot call BoolVal");

}

//---------------------------------------------
//                FunVal CLASS
//---------------------------------------------
FunVal::FunVal(std::string formal_arg, PTR(Expr)body) {
    this->formal_arg = formal_arg;
    this->body = body;
}

PTR(Val)FunVal::add_to(PTR(Val)rhs) {
    throw std::runtime_error("Function cannot be added");
}

PTR(Val)FunVal::mult_with(PTR(Val)rhs) {
    throw std::runtime_error("Function cannot be multiplied");
}

bool FunVal::equals(PTR(Val)rhs) {
    PTR(FunVal) funPtr = CAST(FunVal)(rhs);
    if (funPtr == nullptr){
        return false;
    }
    return this->formal_arg == funPtr->formal_arg && this->body->equals(funPtr->body);
}

void FunVal::print(std::ostream &ostream) {

}

PTR(Expr)FunVal::to_expr() {
    return NEW(FunExpr)(this->formal_arg, this->body);
}

bool FunVal::is_true() {
    return false;
}

PTR(Val)FunVal::call(PTR(Val)actual_arg) {
    return body->subst(formal_arg, actual_arg->to_expr())->interp();
}
