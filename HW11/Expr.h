//
// Created by Melanie Prettyman on 1/16/24.
//

#ifndef HW2_EXPR_H
#define HW2_EXPR_H

#include <string>
#include <sstream>
#include "pointer.h"

typedef enum {
    prec_none =0,      // = 0
    prec_add =1,       // = 1
    prec_mult =2       // = 2
} precedence_t;


class Val; // Forward declaration of Val class

CLASS(Expr){
public:
    virtual ~Expr() { };
    virtual bool equals(PTR(Expr)e) = 0;

    //Val interp function for interp
    virtual PTR(Val) interp() = 0;
    //virtual int interp() = 0;
    virtual bool has_variable()=0;

    virtual PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) = 0;

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
        this->pretty_print(ostream, prec_none, true, 0);
    }

    virtual void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos)  = 0;

};


//---------------------------------------------
//                NUM CLASS
//---------------------------------------------
class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals( PTR(Expr) e) override;
    PTR(Val) interp() override;
    //Val interp() override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;
};

//---------------------------------------------
//                ADD CLASS
//---------------------------------------------

class Add : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    Add( PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals( PTR(Expr) e ) override;
    PTR(Val) interp() override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;



};

//---------------------------------------------
//                MULT CLASS
//---------------------------------------------

class Mult : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    Mult( PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals( PTR(Expr) e) override;
    PTR(Val) interp() override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos)override;




};

//---------------------------------------------
//                VAR CLASS
//---------------------------------------------
class VarExpr : public Expr {
public:
    std::string var;
    VarExpr(std::string var);
    bool equals(PTR(Expr)e) override;
    PTR(Val) interp() override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;


};


//---------------------------------------------
//                _let CLASS
//---------------------------------------------
class _let : public Expr {
// _let<variable (string)> = <expr> _in <expression>
//      LHS                   RHS          BODY
public:
    std::string lhs;
    PTR(Expr)rhs;
    PTR(Expr)body;

    _let(std::string lhs, PTR(Expr)rhs, PTR(Expr)body);
    bool equals(PTR(Expr)e) override;
    PTR(Val) interp() override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;
};

//---------------------------------------------
//                BoolExpr CLASS
//---------------------------------------------
class BoolExpr : public Expr {
// _let<variable (string)> = <expr> _in <expression>
//      LHS                   RHS          BODY
public:
    bool val;
    BoolExpr(bool val);
    bool equals(PTR(Expr)e) override;
    PTR(Val) interp() override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;
};

//---------------------------------------------
//                IfExpr CLASS
//---------------------------------------------
class IfExpr : public Expr {
public:
    PTR(Expr) condition;
    PTR(Expr) thenBranch;
    PTR(Expr) elseBranch;


    IfExpr(PTR(Expr) condition, PTR(Expr) thenBranch, PTR(Expr) elseBranch);
    PTR(Val) interp() override;
    bool equals(PTR(Expr)e) override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;

};

//---------------------------------------------
//                EqExpr CLASS
//---------------------------------------------
class EqExpr : public Expr {
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;

    EqExpr(PTR(Expr)lhs, PTR(Expr)rhs);
    PTR(Val) interp() override;
    bool equals(PTR(Expr)e) override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;

};

//---------------------------------------------
//                FunExpr CLASS
//---------------------------------------------


class FunExpr : public Expr {
public:
    std::string formal_arg;
    PTR(Expr) body;
    FunExpr(std::string formal_arg, PTR(Expr) body);

    bool equals(PTR(Expr)e) override;
    PTR(Val) interp() override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;
};

//---------------------------------------------
//                CallExpr CLASS
//---------------------------------------------
class CallExpr : public Expr {
public:
    PTR(Expr) to_be_called;
    PTR(Expr) actual_arg;
    CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg);
    bool equals(PTR(Expr)e) override;
    PTR(Val) interp() override;
    bool has_variable() override;
    PTR(Expr) subst(const std::string& variable, PTR(Expr) replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;
};


#endif //HW2_EXPR_H
