//
// Created by Melanie Prettyman on 1/16/24.
//

#ifndef HW2_EXPR_H
#define HW2_EXPR_H

#include <string>
#include <sstream>

typedef enum {
    prec_none =0,      // = 0
    prec_add =1,       // = 1
    prec_mult =2       // = 2
} precedence_t;

class Val; // Forward declaration

class Expr{
public:
    virtual bool equals(Expr *e) = 0;

    //Val interp function for interp
    virtual Val* interp() = 0;
    //virtual int interp() = 0;
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
    bool equals(Expr *e) override;
    Val* interp() override;
    //Val interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;
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
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;



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
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
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
    bool equals(Expr *e) override;
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
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
    Expr *rhs;
    Expr *body;

    _let(std::string lhs, Expr *rhs, Expr *body);
    bool equals(Expr *e) override;
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
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
    bool equals(Expr *e) override;
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;
};

//---------------------------------------------
//                IfExpr CLASS
//---------------------------------------------
class IfExpr : public Expr {
public:
    Expr* condition;
    Expr* thenBranch;
    Expr* elseBranch;


    IfExpr(Expr* condition, Expr* thenBranch, Expr* elseBranch);
    Val* interp() override;
    bool equals(Expr *e) override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;

};

//---------------------------------------------
//                EqExpr CLASS
//---------------------------------------------
class EqExpr : public Expr {
public:
    Expr *lhs;
    Expr *rhs;

    EqExpr(Expr *lhs, Expr *rhs);
    Val* interp() override;
    bool equals(Expr *e) override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;

};

//---------------------------------------------
//                FunExpr CLASS
//---------------------------------------------


class FunExpr : public Expr {
public:
    std::string formal_arg;
    Expr* body;
    FunExpr(std::string formal_arg, Expr* body);

    bool equals(Expr *e) override;
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;
};

//---------------------------------------------
//                CallExpr CLASS
//---------------------------------------------
class CallExpr : public Expr {
public:
    Expr* to_be_called;
    Expr* actual_arg;
    CallExpr(Expr* to_be_called, Expr* actual_arg);
    bool equals(Expr *e) override;
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(const std::string& variable, Expr* replacement) override;
    void print(std::ostream &os) const override;
    void pretty_print(std::ostream &ostream, precedence_t p, bool let_needs_parenthesis, int pos) override;
};


#endif //HW2_EXPR_H
