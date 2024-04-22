//
// Created by Melanie Prettyman on 3/13/24.
//

#ifndef HW8_VAL_H
#define HW8_VAL_H


#include <string>
#include "Expr.h"
#include "pointer.h"
#include "Env.h"


class Expr;
class Env;

CLASS(Val){
public:
    virtual ~Val() {};
    virtual PTR(Val) add_to(PTR(Val) rhs) = 0;
    virtual PTR(Val) mult_with(PTR(Val) rhs) = 0;
    virtual bool equals(PTR(Val) rhs) = 0;
    virtual void print(std::ostream &ostream) = 0;
    virtual bool is_true()=0;
    virtual PTR(Val)call(PTR(Val)actual_arg) =0;

    std::string to_string() {

        std::stringstream st("");
        this->print(st);
        return st.str();
    }
};

class NumVal : public Val {
public:
    int val;
    explicit NumVal (int val);

    PTR(Val) add_to(PTR(Val) rhs);
    PTR(Val) mult_with(PTR(Val) rhs);
    bool equals(PTR(Val) rhs);
    void print(std::ostream &ostream);
    bool is_true();
    PTR(Val)call(PTR(Val)actual_arg);
};

class BoolVal : public Val {
public:
    bool val;
    BoolVal(bool val);

    bool is_true();
    PTR(Val) add_to(PTR(Val) rhs);
    PTR(Val) mult_with(PTR(Val) rhs);
    bool equals(PTR(Val) rhs);
    void print(std::ostream &ostream);
    PTR(Val)call(PTR(Val)actual_arg) ;
};


class FunVal : public Val {
public:
    std::string formal_arg;
    PTR(Expr) body;
    PTR(Env) env;
    FunVal(std::string formal_arg, PTR(Expr) body, PTR(Env) env);
    PTR(Val) add_to(PTR(Val) rhs) ;
    PTR(Val) mult_with(PTR(Val) rhs) ;
    bool equals(PTR(Val) rhs) ;
    void print(std::ostream &ostream) ;
    bool is_true() ;
    PTR(Val)call(PTR(Val)actual_arg) ;

};

#endif //HW8_VAL_H
