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
        return (val == num->val && num!= nullptr);
    }
    return false;
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
//if you can cast e to type Add (it is a Add)
    if (dynamic_cast<Mult*>(e)) {
        //then cast e to Add
        Mult* expression = dynamic_cast<Mult*>(e);
        //return true if their lhs and rhs are equal
        return (lhs->equals(expression->lhs)) && (rhs->equals(expression->rhs));
    }
    return false;
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