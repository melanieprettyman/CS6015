//
// Created by Melanie Prettyman on 1/16/24.
//

#ifndef HW2_EXPR_H
#define HW2_EXPR_H

#include <string>

class Expr{
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable()=0;

    virtual Expr* subst(const std::string& variable, Expr* replacement) = 0;
};


//---------------------------------------------
//                NUM CLASS
//---------------------------------------------
class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
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
    int interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;



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
    int interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;




};

//---------------------------------------------
//                VAR CLASS
//---------------------------------------------
class VarExpr : public Expr {
public:
    std::string var;
    VarExpr(std::string var);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;



};






#endif //HW2_EXPR_H
