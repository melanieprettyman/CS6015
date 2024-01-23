#include "cmdline.h"
#include <string>
#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include "Expr.h"

// Created by Melanie Prettyman on 1/11/24.

void use_arguments(int argc, char **argv) {
    //Bool testSeen set to false
    bool testSeen = false;

    //extract argument from argV
    for (int i = 1; i < argc; i++) {
        std::string argument = argv[i];

        //If argument is --help, print help menu and exit
        if (argument.compare("--help") == 0) {
            std::cout << "Choose from the following flags:" << '\n';
            std::cout << "--test" << '\n';
            std::cout << "--interp" << '\n';
            exit(0);
        }
        //If argument is --test and test has not been seen
        //print 'test passed' and set testSeen to true
        if (argument.compare("--test") == 0) {
            if (!testSeen) {
                testSeen = true;
                int result = Catch::Session().run(1, argv);
                if (result != 0) {
                    exit(1);
                }
            } else {
                std::cerr << "Error: '--test' argument already seen." << '\n';
                exit(1);
            }
        }
        else {
            std::cerr << "Error: bad flag." << '\n';
            exit(1);
        }
    }
}



//----------------------------------
//            TESTS
//----------------------------------


TEST_CASE("Prof. Nabil Tests"){
    CHECK( (new VarExpr("x"))->equals(new VarExpr("x")) == true );
    CHECK( (new VarExpr("x"))->equals(new VarExpr("y")) == false );
    CHECK( (new Num(1))->equals(new VarExpr("x")) == false );
    CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(2),new Num(3)))==true );
    CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(2)))==false );
}

TEST_CASE("Num Class") {
    Num num1(5);
    Num num2(5);
    Num num3(10);
    Num num4(5);
    Num num5(5);

    CHECK(num1.equals(&num2) == true);
    CHECK(num1.equals(&num3) == false);
    CHECK(num4.equals(&num5) == true);
    CHECK(num4.equals(&num3) == false);
    CHECK(num2.equals(&num3) == false);

}

/**
Num num1(5);
Num num2(5);
CHECK(num1.equals(&num2) == true);

is the same as

Num* num1 = new Num(5);
Num* num2 = new Num(5);
CHECK(num1->equals(num2) == true);

 * */

TEST_CASE("Add Class") {
    Num num1(5);
    Num num2(10);
    Add add1(&num1, &num2);
    Add add2(&num1, &num2);
    Add add3(&num1, &num1);
    Num num3(5);
    Num num4(10);
    Add add4(&num3, &num4);

    CHECK(add1.equals(&add2) == true);
    CHECK(add1.equals(&add3) == false);
    CHECK(add3.equals(&add4) == false);
    CHECK(add1.equals(&add3) == false);
    CHECK(add4.equals(&add4) == true);
}

TEST_CASE("Mult Class") {
    Num num1(5);
    Num num2(10);
    Mult mult1(&num1, &num2);
    Mult mult2(&num1, &num2);
    Mult mult3(&num1, &num1);
    Num num3(5);
    Num num4(10);
    Mult mult4(&num3, &num4);

    CHECK(mult1.equals(&mult2) == true);
    CHECK(mult1.equals(&mult3) == false);
    CHECK(mult3.equals(&mult4) == false);
    CHECK(mult1.equals(&mult3) == false);
    CHECK(mult4.equals(&mult4) == true);
}

TEST_CASE("VarExpr Class") {
    VarExpr var1("x");
    VarExpr var2("x");
    VarExpr var3("y");
    VarExpr var4("z");
    VarExpr var5("z");

    CHECK(var1.equals(&var2) == true);
    CHECK(var1.equals(&var3) == false);
    CHECK(var4.equals(&var5) == true);
    CHECK(var4.equals(&var3) == false);
    CHECK(var2.equals(&var3) == false);
}

TEST_CASE("Mixed Expressions") {
    Num num1(5);
    VarExpr var1("x");
    Add add1(&num1, &var1);
    Mult mult1(&var1, &num1);

    CHECK(add1.equals(&mult1) == false);
    CHECK(var1.equals(&mult1) == false);
}
TEST_CASE("Prof. Nabil Tests for interp and subst") {
    //interp
    CHECK_THROWS_WITH((new VarExpr("x"))->interp(), "No value for variable");
    CHECK( (new Mult(new Num(3), new Num(2)))->interp()==6 );
    CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))->interp()==65);
    //subst
    CHECK( (new Add(new VarExpr("x"), new Num(7)))->subst("x", new VarExpr("y"))->equals(new Add(new VarExpr("y"), new Num(7))) );
    CHECK( (new VarExpr("x"))->subst("x", new Add(new VarExpr("y"),new Num(7)))->equals(new Add(new VarExpr("y"),new Num(7))) );
}

TEST_CASE("has_variable tests") {
    CHECK( (new Add(new Add(new Num(10), new VarExpr("x")),new Add(new Num(20),new Num(20))))->has_variable()==true);
    CHECK( (new Add(new Add(new Num(10), new Num(10)),new Add(new Num(20),new Num(20))))->has_variable()==false);

}


TEST_CASE("NUM CLASS - interp, has_variable, subst") {
    Num num(5);

    // interp should return the value of the Num
    CHECK(num.interp() == 5);

    // Num will never have a variable
    CHECK(num.has_variable() == false);

    // subst should return the same Num object
    Expr* substitutedNum = num.subst("x", new VarExpr("y"));
    CHECK(substitutedNum->equals(&num) == true);
}
TEST_CASE("ADD CLASS - interp, has_variable, subst") {
    Num num1(5);
    Num num2(10);
    Add add(&num1, &num2);

    // interp should return the sum of the subexpressions
    CHECK(add.interp() == 15);

    // Add has a variable if any of its subexpressions has a variable
    CHECK(add.has_variable() == false); // Both subexpressions are Num

    // subst should replace variables in both subexpressions
    Expr* substitutedAdd = add.subst("x", new VarExpr("y"));
    CHECK(substitutedAdd->equals(&add) == true);

    // Add with one Num and one VarExpr
    VarExpr var("z");
    Add addVar(&num1, &var);
    CHECK(addVar.has_variable() == true);
}

TEST_CASE("MULT CLASS - interp, has_variable, subst") {
    Num num1(5);
    Num num2(10);
    Mult mult(&num1, &num2);

    // interp should return the product of the subexpressions
    CHECK(mult.interp() == 50);

    // Mult has a variable if any of its subexpressions has a variable
    CHECK(mult.has_variable() == false); // Both subexpressions are Num

    // subst should replace variables in both subexpressions
    Expr* substitutedMult = mult.subst("x", new VarExpr("y"));
    CHECK(substitutedMult->equals(&mult) == true);

    // Mult with one Num and one VarExpr
    VarExpr var("z");
    Mult multVar(&num1, &var);
    CHECK(multVar.has_variable() == true);
}
TEST_CASE("VAR-EXPR CLASS - interp, has_variable, subst") {
    VarExpr var("x");

    // interp should throw a std::runtime_error for VarExpr
    CHECK_THROWS_AS(var.interp(), std::runtime_error);

    // VarExpr is always a variable
    CHECK(var.has_variable() == true);

    // subst should replace the variable if it matches
    Expr* substitutedVar = var.subst("x", new Num(5));
    CHECK(substitutedVar->equals(new Num(5)) == true);

    // subst should not replace if the variable doesn't match
    substitutedVar = var.subst("y", new Num(5));
    CHECK(substitutedVar->equals(&var) == true);
}




