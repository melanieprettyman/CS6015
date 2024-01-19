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

    CHECK(num1.equals(&num2) == true);
    CHECK(num1.equals(&num3) == false);
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

    CHECK(add1.equals(&add2) == true);
    CHECK(add1.equals(&add3) == false);
}

TEST_CASE("Mult Class") {
    Num num1(5);
    Num num2(10);
    Mult mult1(&num1, &num2);
    Mult mult2(&num1, &num2);
    Mult mult3(&num1, &num1);

    CHECK(mult1.equals(&mult2) == true);
    CHECK(mult1.equals(&mult3) == false);
}

TEST_CASE("VarExpr Class") {
    VarExpr var1("x");
    VarExpr var2("x");
    VarExpr var3("y");

    CHECK(var1.equals(&var2) == true);
    CHECK(var1.equals(&var3) == false);
}

TEST_CASE("Mixed Expressions") {
    Num num1(5);
    VarExpr var1("x");
    Add add1(&num1, &var1);
    Mult mult1(&var1, &num1);

    CHECK(add1.equals(&mult1) == false);
    CHECK(var1.equals(&mult1) == false);
}