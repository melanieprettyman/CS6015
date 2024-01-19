//
// Created by Melanie Prettyman on 1/16/24.
//

#ifndef HW2_EXPR_H
#define HW2_EXPR_H

#include <string>

class Expr{
public:
    virtual bool equals(Expr *e) = 0;
};


//---------------------------------------------
//                NUM CLASS
//---------------------------------------------
class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *e) override;
};

//---------------------------------------------
//                ADD CLASS
//---------------------------------------------

class Add : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *e) override;

};

//---------------------------------------------
//                MULT CLASS
//---------------------------------------------

class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e) override;

};

//---------------------------------------------
//                VAR CLASS
//---------------------------------------------
class VarExpr : public Expr {
public:
    std::string var;
    VarExpr(std::string var);
    bool equals(Expr *e) override;
};






#endif //HW2_EXPR_H
