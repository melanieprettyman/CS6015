//
// Created by Aiden Pratt on 1/16/24.
//

#ifndef msdscript_EXPR_H
#define msdscript_EXPR_H


#include <string>
#include <sstream>

typedef enum {
    prec_none = 0,      // = 0
    prec_add = 1,       // = 1
    prec_mult = 2       // = 2
} precedence_t;


class expr {
public:
    virtual bool equals(expr *e) = 0;//each subclass must override
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual expr* subst(std::string string , expr *e) = 0;
    virtual void print(std::ostream&) = 0;

    std::string to_string(){
        std::stringstream st("");
        this->print(st);
        return st.str();
    }

    std::string to_pp_string(){
        std::stringstream st("");
        this->pretty_print_at(st);
        return st.str();
    }

    void pretty_print_at(std::ostream &ostream){
       this->pretty_print(ostream, prec_none);
    }

    virtual void pretty_print(std::ostream &ostream, precedence_t p) = 0;
};

//-----------NUM----------//
class Num : public expr {
public:
    int val;
    explicit Num(int val);
    bool equals(expr *e) override;
    int interp() override;
    bool has_variable() override;
    expr* subst(std::string string , expr *e) override;
    void print(std::ostream &ostream) override;
    void pretty_print(std::ostream &override, precedence_t p) override;

};

//----------ADD-----------//
class Add : public expr{
public:
    expr *lhs;
    expr *rhs;
    Add(expr *lhs, expr *rhs);
    bool equals(expr *e) override;
    int interp() override;
    bool has_variable() override;
    expr* subst(std::string string , expr *e) override;
    void print(std::ostream &ostream) override;
    void pretty_print(std::ostream &ostream, precedence_t p) override;
};

//-----------MULT-------//
class Mult : public expr {
public:
    expr *lhs;
    expr *rhs;
    Mult(expr *lhs, expr *rhs);
    bool equals(expr *e) override;
    int interp() override;
    bool has_variable() override;
    expr* subst(std::string string , expr *e) override;
    void print(std::ostream &ostream) override;
    void pretty_print(std::ostream &ostream, precedence_t p) override;
};

//------------VAR----------//
class Var : public expr{
public:
    std::string var;
    Var(std::string var);
    bool equals(expr *e) override;
    int interp() override;
    bool has_variable() override;
    expr* subst(std::string string , expr *e) override;
    void print(std::ostream &ostream) override;
    void pretty_print(std::ostream &ostream, precedence_t p) override;
};


#endif //ASSIGNMENT2_EXPR_H
