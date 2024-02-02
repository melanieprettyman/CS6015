#include "Expr.h"
#include "catch.h"

// Created by Melanie Prettyman on 1/16/24.
//

 bool Expr::equals(Expr *e) {
     return false;
}

//---------------------------------------------
//                NUMS CLASS
//---------------------------------------------

//CONSTRUCTOR
Num::Num(int val) {
    this->val = val;
}

//EQUALS IMPLEMENTATION
bool Num::equals(Expr *e) {
    //if you can cast e to type Num (it is a Num)
    if (dynamic_cast<Num*>(e)) {
        //then cast e to Num
        Num* num = dynamic_cast<Num*>(e);
        //return true if their values are equal
        return val == num->val;
    }
    return false;
}
//returns an int for the value of an expression
int Num::interp() {
    return (int)this->val;
}

//returns true if the expression is a variable or contains a variable, false otherwise
//num will never be a var so return true
bool Num::has_variable() {
    return false;
}
//takes two arguments: a std::string and an Expr*. The result is an Expr*.
//Everywhere that the expression (whose subst method is called) contains a variable matching the string,
// the result Expr* should have the given replacement, instead.
Expr *Num::subst(const std::string &variable, Expr *replacement) {
    return this;
}
//override the << operator and use the os parameter (which represents the ostream)
// to output the desired information.
void Num::print(std::ostream &os) const{
    os <<this->val;
}



void Num::pretty_print(std::ostream &ostream, precedence_t p) {
    ostream <<this->val;

}


//---------------------------------------------
//                ADD CLASS
//---------------------------------------------

//CONSTRUCTOR
Add::Add(Expr *lhs, Expr *rhs) {
this->lhs = lhs;
this->rhs = rhs;
}

//EQUALS IMPLEMENTATION
bool Add::equals(Expr *e) {
//if you can cast e to type Add (it is a Add)
    if (dynamic_cast<Add*>(e)) {
        //then cast e to Add
        Add* expression = dynamic_cast<Add*>(e);
        //return true if their lhs and rhs are equal
        return (lhs->equals(expression->lhs)) && (rhs->equals(expression->rhs));
    }
    return false;
}
//Returns an int for the value of an expression
//The value of an addition expression is the sum of the subexpression values
int Add::interp() {
    return (this->rhs->interp() + this->lhs->interp());
}
//returns true if the expression is a variable or contains a variable, false otherwise
//recursively call has_variable until it results in a num or a var
bool Add::has_variable() {
    return (this->rhs->has_variable() || this->lhs->has_variable());

}
//takes two arguments: a std::string and an Expr*. The result is an Expr*.
//Everywhere that the expression (whose subst method is called) contains a variable matching the string,
// the result Expr* should have the given replacement, instead.
Expr *Add::subst(const std::string &variable, Expr *replacement) {
    return (new Add(this->lhs->subst(variable, replacement),this->rhs->subst(variable, replacement)));
}

void Add::print(std::ostream &os) const{
    os << "(";
    (this->lhs->print(os));
    os << "+";
    (this->rhs->print(os));
    os << ")";
}



void Add::pretty_print(std::ostream &ostream, precedence_t p) {
    if(p > prec_add){
        ostream << "(";
    }

    (this->lhs->pretty_print(ostream, prec_add));
    ostream << " + ";
    (this->rhs->pretty_print(ostream, prec_add));

    if(p > prec_add){
        ostream << ")";
    }
}


//---------------------------------------------
//                MULT CLASS
//---------------------------------------------

//CONSTRUCTOR
Mult::Mult(Expr *lhs, Expr *rhs) {
this->lhs = lhs;
this->rhs = rhs;
}

//EQUALS IMPLEMENTATION
bool Mult::equals(Expr *e) {
//if you can cast e to type Add (it is an Add)
    if (dynamic_cast<Mult*>(e)) {
        //then cast e to Add
        Mult* expression = dynamic_cast<Mult*>(e);
        //return true if their lhs and rhs are equal
        return (lhs->equals(expression->lhs)) && (rhs->equals(expression->rhs));
    }
    return false;
}
//Returns an int for the value of an expression
//The value of a multiplication expression is the product of the subexpression values
int Mult::interp() {
    return (this->rhs->interp() * this->lhs->interp());

}
//returns true if the expression is a variable or contains a variable, false otherwise
//recursively call has_variable until it results in a num or a var
bool Mult::has_variable() {
    return (this->rhs->has_variable() || this->lhs->has_variable());
}
//takes two arguments: a std::string and an Expr*. The result is an Expr*.
//Everywhere that the expression (whose subst method is called) contains a variable matching the string,
// the result Expr* should have the given replacement, instead.
Expr *Mult::subst(const std::string &variable, Expr *replacement) {
    return (new Mult(this->lhs->subst(variable, replacement),this->rhs->subst(variable, replacement)));
}

void Mult::print(std::ostream &os) const{
    os << "(";
    (this->lhs->print(os));
    os << "*";
    (this->rhs->print(os));
    os << ")";
}



void Mult::pretty_print(std::ostream &ostream, precedence_t p) {
    if(p > prec_mult){
        ostream << "(";
    }


    (this->lhs->pretty_print(ostream, static_cast<precedence_t >(prec_mult+1)));
    ostream << " * ";
    (this->rhs->pretty_print(ostream, prec_mult));


    if(p > prec_mult){
        ostream << ")";
    }
}

//---------------------------------------------
//                VarExpr CLASS
//---------------------------------------------

//CONSTRUCTOR
VarExpr::VarExpr(std::string var) {
    this->var = var;
}

//EQUALS IMPLEMENTATION
bool VarExpr::equals(Expr *e) {
    //if you can cast e to type VarExpr (it is a VarExpr)
    if (dynamic_cast<VarExpr*>(e)) {
        //then cast e to VarExpr
        VarExpr* expression = dynamic_cast<VarExpr*>(e);
        //return true if their values are equal
        return this->var == expression->var;
    }
    return false;
}
//Returns an int for the value of an expression
//A variable has no value, so interp for a variable should throw a std::runtime_error exception
int VarExpr::interp() {
    throw std::runtime_error("No value for variable");
    return 0;
}

//return true if the expression is a variable or contains a variable, false otherwise.
//var is a var, so return true
bool VarExpr::has_variable() {
    return true;
}
//takes two arguments: a std::string and an Expr*. The result is an Expr*.
//Everywhere that the expression (whose subst method is called) contains a variable matching the string,
// the result Expr* should have the given replacement, instead.
Expr *VarExpr::subst(const std::string &variable, Expr *replacement) {
    if (this->var == variable) {
        return replacement;
    }
    return this;
}

void VarExpr::print(std::ostream &os) const{
    os <<this->var;
}



void VarExpr::pretty_print(std::ostream &ostream, precedence_t p) {
    ostream <<this->var;

}




