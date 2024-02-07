#include "Expr.h"
#include "catch.h"

/**
* \file Expr.cpp
* \brief contains expression class's
*
*
* Contains parent Expression class (Expr) and it's children classes; Num, Add, Mult, and VarExpr.
* \author Melanie Prettyman
 */


// Created by Melanie Prettyman on 1/16/24.
//

 bool Expr::equals(Expr *e) {
     return false;
}

//---------------------------------------------
//                NUMS CLASS
//---------------------------------------------
/**
 * \brief Num class represents a numeric expression.
 * \param int val is the numeric value of the expression.
 */

/**
 * \brief Constructor for Num class.
 * \param int val is the initial value for the numeric expression.
 */
//CONSTRUCTOR
Num::Num(int val) {
    this->val = val;
}

/**
 * \brief Checks if the given expression is equal to the current Num instance.
 * \param Expr *e is a pointer to an expression to compare.
 * \return Returns true if equal, false otherwise.
 */
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

/**
 * \brief Returns the integer value of the expression.
 * \return Returns the numeric value of the expression as an integer.
 */
//returns an int for the value of an expression
int Num::interp() {
    return (int)this->val;
}

/**
 * \brief Checks if the expression contains any variables.
 * \return Always returns false for Num class.
 */
//returns true if the expression is a variable or contains a variable, false otherwise
//num will never be a var so return true
bool Num::has_variable() {
    return false;
}

/**
 * \brief Substitutes variables in the expression with given replacements.
 * \param const std::string &variable is the variable to substitute.
 * \param Expr *replacement is the expression to replace the variable.
 * \return Returns the original expression since Num does not contain variables.
 */
//takes two arguments: a std::string and an Expr*. The result is an Expr*.
//Everywhere that the expression (whose subst method is called) contains a variable matching the string,
// the result Expr* should have the given replacement, instead.
Expr *Num::subst(const std::string &variable, Expr *replacement) {
    return this;
}

/**
 * \brief Outputs the numeric value to the provided ostream.
 * \param std::ostream &os is the output stream.
 */
//override the << operator and use the os parameter (which represents the ostream)
// to output the desired information.
void Num::print(std::ostream &os) const{
    os <<this->val;
}

/**
 * \brief Pretty prints the numeric value to the provided ostream.
 * \param std::ostream &ostream is the output stream.
 * \param precedence_t p is the precedence level for proper formatting.
 */
void Num::pretty_print(std::ostream &ostream, precedence_t p) {
    ostream <<this->val;

}


//---------------------------------------------
//                ADD CLASS
//---------------------------------------------
/**
 * \brief Add class represents an addition expression.
 * \param Expr *lhs is the left-hand side subexpression.
 * \param Expr *rhs is the right-hand side subexpression.
 */

/**
 * \brief Constructor for Add class.
 * \param Expr *lhs is the left-hand side subexpression.
 * \param Expr *rhs is the right-hand side subexpression.
 */
//CONSTRUCTOR
Add::Add(Expr *lhs, Expr *rhs) {
this->lhs = lhs;
this->rhs = rhs;
}

/**
 * \brief Checks if the given expression is equal to the current Add instance.
 * \param Expr *e is a pointer to an expression to compare.
 * \return Returns true if equal, false otherwise.
 */
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

/**
* \brief Returns the sum of the left and right subexpression values.
* \return Returns the result of the addition as an integer.
*/
//Returns an int for the value of an expression
//The value of an addition expression is the sum of the subexpression values
int Add::interp() {
    return (this->rhs->interp() + this->lhs->interp());
}

/**
 * \brief Checks if the expression contains any variables.
 * \return Returns true if either the left or right subexpression contains a variable.
 */
//returns true if the expression is a variable or contains a variable, false otherwise
//recursively call has_variable until it results in a num or a var
bool Add::has_variable() {
    return (this->rhs->has_variable() || this->lhs->has_variable());

}

/**
* \brief Substitutes variables in the expression with given replacements.
* \param const std::string &variable is the variable to substitute.
* \param Expr *replacement is the expression to replace the variable.
* \return Returns a new Add expression with substituted variables.
*/
//takes two arguments: a std::string and an Expr*. The result is an Expr*.
//Everywhere that the expression (whose subst method is called) contains a variable matching the string,
// the result Expr* should have the given replacement, instead.
Expr *Add::subst(const std::string &variable, Expr *replacement) {
    return (new Add(this->lhs->subst(variable, replacement),this->rhs->subst(variable, replacement)));
}
/**
 * \brief Outputs the addition expression to the provided ostream.
 * \param std::ostream &os is the output stream.
 */
void Add::print(std::ostream &os) const{
    os << "(";
    (this->lhs->print(os));
    os << "+";
    (this->rhs->print(os));
    os << ")";
}

/**
 * \brief Pretty prints the addition expression to the provided ostream.
 * \param std::ostream &ostream is the output stream.
 * \param precedence_t p is the precedence level for proper formatting.
 */
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
/**
 * \brief Mult class represents a multiplication expression.
 * \param Expr *lhs is the left-hand side subexpression.
 * \param Expr *rhs is the right-hand side subexpression.
 */

/**
 * \brief Constructor for Mult class.
 * \param Expr *lhs is the left-hand side subexpression.
 * \param Expr *rhs is the right-hand side subexpression.
 */
//CONSTRUCTOR
Mult::Mult(Expr *lhs, Expr *rhs) {
this->lhs = lhs;
this->rhs = rhs;
}

/**
 * \brief Checks if the given expression is equal to the current Mult instance.
 * \param Expr *e is a pointer to an expression to compare.
 * \return Returns true if equal, false otherwise.
 */
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

/**
 * \brief Returns the product of the left and right subexpression values.
 * \return Returns the result of the multiplication as an integer.
 */
//Returns an int for the value of an expression
//The value of a multiplication expression is the product of the subexpression values
int Mult::interp() {
    return (this->rhs->interp() * this->lhs->interp());

}

/**
 * \brief Checks if the expression contains any variables.
 * \return Returns true if either the left or right subexpression contains a variable.
 */
//returns true if the expression is a variable or contains a variable, false otherwise
//recursively call has_variable until it results in a num or a var
bool Mult::has_variable() {
    return (this->rhs->has_variable() || this->lhs->has_variable());
}

/**
 * \brief Substitutes variables in the expression with given replacements.
 * \param const std::string &variable is the variable to substitute.
 * \param Expr *replacement is the expression to replace the variable.
 * \return Returns a new Mult expression with substituted variables.
 */
//takes two arguments: a std::string and an Expr*. The result is an Expr*.
//Everywhere that the expression (whose subst method is called) contains a variable matching the string,
// the result Expr* should have the given replacement, instead.
Expr *Mult::subst(const std::string &variable, Expr *replacement) {
    return (new Mult(this->lhs->subst(variable, replacement),this->rhs->subst(variable, replacement)));
}

/**
 * \brief Outputs the multiplication expression to the provided ostream.
 * \param std::ostream &os is the output stream.
 */
void Mult::print(std::ostream &os) const{
    os << "(";
    (this->lhs->print(os));
    os << "*";
    (this->rhs->print(os));
    os << ")";
}

/**
* \brief Pretty prints the multiplication expression to the provided ostream.
* \param std::ostream &ostream is the output stream.
* \param precedence_t p is the precedence level for proper formatting.
*/
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
/**
 * \brief VarExpr class represents a variable expression.
 * \param std::string var is the variable name.
 */

/**
 * \brief Constructor for VarExpr class.
 * \param std::string var is the variable name.
 */
//CONSTRUCTOR
VarExpr::VarExpr(std::string var) {
    this->var = var;
}

/**
 * \brief Checks if the given expression is equal to the current VarExpr instance.
 * \param Expr *e is a pointer to an expression to compare.
 * \return Returns true if equal, false otherwise.
 */
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

/**
 * \brief Throws a std::runtime_error since variables do not have a numeric value.
 * \return Does not return as an exception is thrown.
 */
//Returns an int for the value of an expression
//A variable has no value, so interp for a variable should throw a std::runtime_error exception
int VarExpr::interp() {
    throw std::runtime_error("No value for variable");
    return 0;
}

/**
 * \brief Always returns true since VarExpr represents a variable.
 * \return Returns true.
 */
//return true if the expression is a variable or contains a variable, false otherwise.
//var is a var, so return true
bool VarExpr::has_variable() {
    return true;
}

/**
 * \brief Substitutes variables in the expression with given replacements.
 * \param const std::string &variable is the variable to substitute.
 * \param Expr *replacement is the expression to replace the variable.
 * \return Returns the original expression if variable names do not match.
 */
//takes two arguments: a std::string and an Expr*. The result is an Expr*.
//Everywhere that the expression (whose subst method is called) contains a variable matching the string,
// the result Expr* should have the given replacement, instead.
Expr *VarExpr::subst(const std::string &variable, Expr *replacement) {
    if (this->var == variable) {
        return replacement;
    }
    return this;
}

/**
 * \brief Outputs the variable name to the provided ostream.
 * \param std::ostream &os is the output stream.
 */

void VarExpr::print(std::ostream &os) const{
    os <<this->var;
}

/**
 * \brief Pretty prints the variable name to the provided ostream.
 * \param std::ostream &ostream is the output stream.
 * \param precedence_t p is the precedence level for proper formatting.
 */

void VarExpr::pretty_print(std::ostream &ostream, precedence_t p) {
    ostream <<this->var;

}




