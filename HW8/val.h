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
    virtual std::string to_string() = 0;
    virtual Expr* to_expr() = 0;
};

class NumVal : public Val {
    int val;
public:
    NumVal(int val);
    Val* add_to(Val* rhs) override;
    Val* mult_with(Val* rhs) override;
    bool equals(Val* rhs) override;
    std::string to_string() override;
    Expr* to_expr() override;
};

#endif //HW8_VAL_H
