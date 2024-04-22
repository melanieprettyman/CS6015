#include <iostream>
#include "Expr.h"
#include "catch.h"
#include "val.h"
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
Val* Num::interp() {
    return new NumVal(this->val);
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
Val* Add::interp() {
    Val* leftVal = lhs->interp();
    Val* rightVal = rhs->interp();
    return leftVal->add_to(rightVal);
    // return (this->rhs->interp() + this->lhs->interp());
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

    (this->lhs->pretty_print(ostream, static_cast<precedence_t>(prec_add + 1), true, pos));
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
Val* Mult::interp() {
    Val* leftVal = lhs->interp();
    Val* rightVal = rhs->interp();
    return leftVal->mult_with(rightVal);
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


//todo: explain _let expectations

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
Val* VarExpr::interp() {
    throw std::runtime_error("No value for variable");
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


Val* _let::interp() {
    //Find the value of the RHS
    Val* rhsVal = rhs->interp();

    //create a number with the value of RHS
    Expr* rhsNum = rhsVal->to_expr();

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

//---------------------------------------------
//                BoolExpr CLASS
//---------------------------------------------
//CONSTRUCTOR
BoolExpr::BoolExpr(bool val) {
    this->val = val;
}

//EQUALS IMPLEMENTATION
bool BoolExpr::equals(Expr *e){
    BoolExpr* pBoolExpr = dynamic_cast<BoolExpr*>(e);
    if (pBoolExpr == nullptr) {
        return false;
    }
    return val == pBoolExpr->val;
}

//BoolExpr interp function returns the value of the BoolVal as a BoolVal
Val* BoolExpr::interp(){
    return new BoolVal(val);
}

//BoolExpr has_variable function returns false since a boolean value cannot contain a variable
bool BoolExpr::has_variable(){
    return false;
}

// No substitution possible in a boolean expression
Expr* BoolExpr::subst(const std::string& variable, Expr* replacement){
    return this;
}

void BoolExpr::print(std::ostream &os) const{
    os<<std::to_string(val);
}
//TODO: Pretty print
void BoolExpr::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos){
    ostream << " ";
}

//---------------------------------------------
//                IfExpr CLASS
//---------------------------------------------
//IfExpr constructor
IfExpr::IfExpr(Expr *condition, Expr *thenBranch, Expr *elseBranch) {
    this->condition = condition;
    this->thenBranch =thenBranch;
    this->elseBranch = elseBranch;
}
//IfExpr equals function checks if two IfExprs are equal
bool IfExpr::equals(Expr *e) {
    IfExpr* pIfExpr = dynamic_cast<IfExpr*>(e);
    if (pIfExpr == nullptr) {
        return false;
    }
    return (condition->equals(pIfExpr->condition)) && (thenBranch->equals(pIfExpr->thenBranch)) && (elseBranch->equals(pIfExpr->elseBranch));
}

//IfExpr interp function returns the value of the then branch if the condition is true,
// and the value of the else branch if the condition is false
Val* IfExpr::interp() {
    //Find the value of the condition
    BoolVal* conditionVal = dynamic_cast<BoolVal*>(condition->interp());

    if (!conditionVal) {
        throw std::runtime_error("If condition is not boolean.");
    }
    //If the condition is true, return the value of the then branch
    if (conditionVal->is_true()) {
        return thenBranch->interp();
    } else { //If the condition is false, return the value of the else branch
        return elseBranch->interp();
    }
}
//IfExpr has_variable function returns true if the condition, then branch, or else branch has a variable, false otherwise
bool IfExpr::has_variable() {
    return this->condition->has_variable()||this->thenBranch->has_variable()||elseBranch->has_variable();
}

Expr *IfExpr::subst(const std::string &variable, Expr *replacement) {
    // Substitute in the condition part of the if expression
    Expr *newCondition = this->condition->subst(variable, replacement);

    // Substitute in the then branch of the if expression
    Expr *newThenBranch = this->thenBranch->subst(variable, replacement);

    // Substitute in the else branch of the if expression
    Expr *newElseBranch = this->elseBranch->subst(variable, replacement);

    // Return a new IfExpr with the substituted parts
    return new IfExpr(newCondition, newThenBranch, newElseBranch);
}


void IfExpr::print(std::ostream &os) const {
    os << "(_if";
    this->condition->print(os);
    os << "_then";
    this->thenBranch->print(os);
    os << "_else";
    this->elseBranch->print(os);
    os << ")";

}

void IfExpr::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) {
    if(p > prec_none && let_needs_parenthesis){
        ostream << "(";
    }

    int ifPos = ostream.tellp();
    int n = ifPos - pos;
    ostream << "_if " << this->condition;

    this->condition->pretty_print(ostream, p, let_needs_parenthesis, ifPos);
    ostream << "\n" << " ";

    int thenPos = ostream.tellp();

    while(n > 0){
        ostream << " ";
        n--;
    }
    ostream << "_then  ";
    this->thenBranch->pretty_print(ostream, prec_none, let_needs_parenthesis, thenPos);

    ostream << "\n" << " ";
    int elsePos = ostream.tellp();
    int f = elsePos - pos;

    while(f > 0){
        ostream << " ";
        f--;
    }
    ostream << "_else ";
    this->elseBranch->pretty_print(ostream, prec_none, let_needs_parenthesis, elsePos);

    if(p > prec_none && let_needs_parenthesis){
        ostream << ")";
    }
}

//---------------------------------------------
//                EqExpr CLASS
//---------------------------------------------
//EqExpr constructor
EqExpr::EqExpr(Expr* lhs, Expr* rhs){
    this->lhs=lhs;
    this->rhs=rhs;
}

//EqExpr has_variable function returns true if the lhs or rhs has a variable, false otherwise
bool EqExpr::has_variable() {
    return this->rhs->has_variable()||this->lhs->has_variable();
}

//EqExpr interp function returns true if the value of the lhs is equal to the value of the rhs, false otherwise
Val* EqExpr::interp() {
    Val* lhsVal = lhs->interp();
    Val* rhsVal = rhs->interp();
    return new BoolVal(lhsVal->equals(rhsVal));
}
//EqExpr subst function returns a new EqExpr with the lhs and rhs substituted
Expr* EqExpr::subst(const std::string &variable, Expr *replacement){
    Expr *lhsExpr = this->lhs->subst(variable, replacement);
    Expr *rhsExpr = this->rhs->subst(variable, replacement);
    return new EqExpr(lhsExpr, rhsExpr);
}

//EqExpr print function returns the EqExpr as a string
void EqExpr::print(std::ostream &os) const {
    os << "(";
    this->lhs->print(os);
    os << "==";
    this->rhs->print(os);
    os << ")";
}

//EqExpr equals function checks if two EqExprs are equal
bool EqExpr::equals(Expr *e) {
    EqExpr* pEqExpr = dynamic_cast<EqExpr*>(e);
    if (pEqExpr == nullptr) {
        return false;
    }
    return (lhs->equals(pEqExpr->lhs)) && (rhs->equals(pEqExpr->rhs));
}

void EqExpr::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) {
    lhs->pretty_print(ostream, p, false, 0);
    ostream << " == ";
    rhs->pretty_print(ostream, p, false, 0);

}

//---------------------------------------------
//                FunExpr CLASS
//---------------------------------------------

FunExpr::FunExpr(std::string formal_arg, Expr *body) {
    this->formal_arg = formal_arg;
    this->body = body;
}

bool FunExpr::has_variable() {
    return false;
}

Val* FunExpr::interp() {
    return new FunVal(this->formal_arg, this->body);
}

Expr* FunExpr::subst(const std::string &variable, Expr *replacement) {
    if (this->formal_arg == variable) {
        return this;
    }
    return new FunExpr(this->formal_arg, this->body->subst(variable, replacement));
}

void FunExpr::print(std::ostream &os) const {
    os << "(_fun ";
    os << this->formal_arg;
    os << " _body ";
    this->body->print(os);
    os << ")";
}

bool FunExpr::equals(Expr *e) {
    FunExpr* pFunExpr = dynamic_cast<FunExpr*>(e);
    if (pFunExpr == nullptr) {
        return false;
    }
    return (formal_arg == pFunExpr->formal_arg) && (body->equals(pFunExpr->body));
}

void FunExpr::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) {
//    ostream << "(_fun " << this->formal_arg << " _body ";
//    this->body->pretty_print(ostream, p, let_needs_parenthesis, pos);
//    ostream << ")";
    if(let_needs_parenthesis) {
        ostream << "(";
    }
    ostream << "_fun (" << this->formal_arg << ")\n";

    this->body->pretty_print(ostream, prec_none, let_needs_parenthesis, pos + 2); // pos + 2 to increase indentation for the body

    if(let_needs_parenthesis) {
        ostream << ")";
    }
}

//---------------------------------------------
//                CallExpr CLASS
//---------------------------------------------
CallExpr::CallExpr(Expr *to_be_called, Expr *actual_arg) {
    this->to_be_called = to_be_called;
    this->actual_arg = actual_arg;
}

bool CallExpr::equals(Expr *e) {
    CallExpr* callPtr = dynamic_cast<CallExpr*>(e);
    if (callPtr == nullptr) {
        return false;
    }
    return this->to_be_called->equals(callPtr->to_be_called) && this->actual_arg->equals(callPtr->actual_arg);
}

Val *CallExpr::interp() {
    return to_be_called->interp()->call(actual_arg->interp());
}

bool CallExpr::has_variable() {
    return false;
}

Expr *CallExpr::subst(const std::string &variable, Expr *replacement) {
    return new CallExpr(this->to_be_called->subst(variable, replacement), this->actual_arg->subst(variable, replacement));
}

void CallExpr::print(std::ostream &os) const {
    os << "(" << this->to_be_called->to_string() << ") (" << this->actual_arg->to_string() << ")";
}

void CallExpr::pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) {
    this->to_be_called->pretty_print(ostream, prec_none, false, 0);
    ostream << "(";
    this->actual_arg->pretty_print(ostream, prec_none, false, 0);
}
