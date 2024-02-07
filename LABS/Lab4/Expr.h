//
// Created by Melanie Prettyman on 1/16/24.
//

#ifndef HW2_EXPR_H
#define HW2_EXPR_H

#include <string>
#include <sstream>

/**
* \file Expr.h
* \brief Expression class
*
* Longer description goes here.
*/

typedef enum {
    prec_none =0,      // = 0
    prec_add =1,       // = 1
    prec_mult =2       // = 2
} precedence_t;  ///< Sets precedence for each expression class


class Expr{
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable()=0;

    virtual Expr* subst(const std::string& variable, Expr* replacement) = 0;

    virtual void print(std::ostream& os) const = 0;

    std::string to_pp_string(){
        std::stringstream st("");
        this->pretty_print_at(st);
        return st.str();
    }
    std::string to_string() {

        std::stringstream st("");
        this->print(st);
        return st.str();
    }

    void pretty_print_at(std::ostream &ostream){
        this->pretty_print(ostream, prec_none);
    }

    virtual void pretty_print(std::ostream &ostream, precedence_t p) = 0;

};


//---------------------------------------------
//                NUM CLASS
//---------------------------------------------
class Num : public Expr {
public:
    int val; ///< Value of a number
    Num(int val);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p) override;
};

//---------------------------------------------
//                ADD CLASS
//---------------------------------------------

class Add : public Expr {
public:
    Expr *lhs; ///< Lhs of expression
    Expr *rhs; ///< Rhs of expression
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p) override;



};

//---------------------------------------------
//                MULT CLASS
//---------------------------------------------

class Mult : public Expr {
public:
    Expr *lhs; ///< Lhs of expression
    Expr *rhs; ///< Rhs of expression
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p) override;




};

//---------------------------------------------
//                VAR CLASS
//---------------------------------------------
class VarExpr : public Expr {
public:
    std::string var; ///< String representation of variable
    VarExpr(std::string var);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p) override;


};






#endif //HW2_EXPR_H