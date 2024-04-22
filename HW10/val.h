//
// Created by Melanie Prettyman on 3/13/24.
//

#ifndef HW8_VAL_H
#define HW8_VAL_H


#include <string>
#include "expr.h"

class Val {
public:
    virtual ~Val() = default;
    virtual Val* add_to(Val* rhs) = 0;
    virtual Val* mult_with(Val* rhs) = 0;
    virtual bool equals(Val* rhs) = 0;
    virtual void print(std::ostream &ostream) = 0;
    virtual Expr* to_expr() = 0;
    virtual bool is_true()=0;
    virtual Val *call(Val *actual_arg) =0;

    std::string to_string() {

        std::stringstream st("");
        this->print(st);
        return st.str();
    }
};

class NumVal : public Val {
public:
    int val;
    NumVal(int val);

    Val* add_to(Val* rhs) override;
    Val* mult_with(Val* rhs) override;
    bool equals(Val* rhs) override;
    void print(std::ostream &ostream) override;
    Expr* to_expr() override;
    bool is_true() override;
    Val *call(Val *actual_arg) override;
};

class BoolVal : public Val {
public:
    bool val;
    BoolVal(bool val);

    bool is_true() override;
    Val* add_to(Val* rhs) override;
    Val* mult_with(Val* rhs) override;
    bool equals(Val* rhs) override;
    void print(std::ostream &ostream) override;
    Expr* to_expr() override;
    Val *call(Val *actual_arg) override;
};


class FunVal : public Val {
public:
    std::string formal_arg;
    Expr* body;
    FunVal(std::string formal_arg, Expr* body);
    Val* add_to(Val* rhs) override;
    Val* mult_with(Val* rhs) override;
    bool equals(Val* rhs) override;
    void print(std::ostream &ostream) override;
    Expr* to_expr() override;
    bool is_true() override;
    Val *call(Val *actual_arg) override;

};

#endif //HW8_VAL_H
