#include <iostream>
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



void Num::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) {
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



void Add::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) {
    if(p > prec_add){
        ostream << "(";
    }

    (this->lhs->pretty_print(ostream, static_cast<precedence_t >(prec_add+1), true, pos));
    ostream << " + ";
    (this->rhs->pretty_print(ostream, prec_none, true, pos));

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



// Function to pretty print a multiplication expression
// Parameters:
//   - ostream: Reference to an output stream where the formatted expression will be written.
//   - p: The current precedence level, used to determine if parentheses are needed around the expression.
//   - let_needs_parenthesis: A boolean flag indicating if the let expressions contained within need to be enclosed in parentheses.
//   - pos: The initial position in the output stream, used for alignment but not directly utilized in this function.
void Mult::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) {

    // Add opening parenthesis if the precedence level is higher than that of multiplication,
    // indicating this expression is part of a larger expression
    if(p > prec_mult){
        let_needs_parenthesis = false;
        ostream << "(";
    }



    // Recursively pretty print the lhs of the multiplication, adjusting its precedence to ensure proper formatting.
    this->lhs->pretty_print(ostream, static_cast<precedence_t>(prec_mult + 1), let_needs_parenthesis, pos);
    ostream << " * ";
    // Recursively pretty print the rhs of the multiplication, with its original precedence.
    this->rhs->pretty_print(ostream, prec_mult, let_needs_parenthesis, pos);

    // Add closing parenthesis if necessary
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



void VarExpr::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) {
    ostream <<this->var;

}

//---------------------------------------------
//                _let CLASS
//---------------------------------------------


_let::_let(std::string lhs, Expr *rhs, Expr *body) {
    this->body = body;
    this->lhs = lhs;
    this->rhs = rhs;
}

bool _let::equals(Expr *e) {
    // If you can cast e to type _let (it is a _let)
    if (dynamic_cast<_let*>(e)) {
        // Then cast e to _let
        _let* expression = dynamic_cast<_let*>(e);
        // Return true if their values are equal
        return (lhs == expression->lhs) && (rhs->equals(expression->rhs)) && (body->equals(expression->body));
    }
    return false;
}


int _let::interp() {
    //Find the value of the RHS
    int rhsValue = rhs->interp();

    //create a number with the value of RHS
    Expr* rhsNum = new Num(rhsValue);

    //Substitute body with rhs
    Expr* substitutedBody = this->body->subst(this->lhs, rhsNum);

    //return the interpreted body
    return substitutedBody->interp();
}

bool _let::has_variable() {
    return (this->rhs->has_variable() || this->body->has_variable());
}

Expr* _let::subst(const std::string& variable, Expr* replacement){
    //If this is the
    if (this->lhs == variable) {
       return this;
    }
    //else replace the body too
    else {
        return (new _let(this->lhs, this->rhs->subst(variable, replacement), this->body->subst(variable, replacement)));
    }
}

void _let::print(std::ostream &os) const {
    os << "(";
    os << "_let ";
    os << this->lhs;
    os << "=";
    (this->rhs->print(os));
    os << " _in ";
    (this->body->print(os));
    os << ")";
}


// Function to pretty print a let expression
// Parameters:
//   - ostream: Reference to an output stream where the formatted expression will be written.
//   - p: The current precedence level, used to determine if parentheses are needed.
//   - let_needs_parenthesis: A boolean flag indicating if the let expression should be enclosed in parentheses
//   - pos: The initial position in the output stream, used for alignment purposes.
void _let::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) {
    //counts spaces
    if(p > prec_none && let_needs_parenthesis){
        ostream << "(";
    }

    int letPos = ostream.tellp();
    int n = letPos - pos;
    ostream << "_let " << this->lhs << " = " ;

    this->rhs->pretty_print(ostream, p, let_needs_parenthesis, letPos);
    ostream << "\n" << " ";
    int inPos = ostream.tellp();

    while(n > 0){
        ostream << " ";
        n--;
    }
    ostream << "_in  ";
    this->body->pretty_print(ostream, prec_none, let_needs_parenthesis, inPos);

    if(p > prec_none && let_needs_parenthesis){
        ostream << ")";
    }
}

