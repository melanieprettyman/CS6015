//
// Created by Melanie Prettyman on 2/1/24.
//

#include <iostream>
#include "tests.h"
#include "val.h"

////----------------------------------
////            TESTS
////----------------------------------
//
//
//TEST_CASE("Prof. Nabil Tests"){
//    CHECK( (new VarExpr("x"))->equals(new VarExpr("x")) == true );
//    CHECK( (new VarExpr("x"))->equals(new VarExpr("y")) == false );
//    CHECK( (new Num(1))->equals(new VarExpr("x")) == false );
//    CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(2),new Num(3)))==true );
//    CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(2)))==false );
//}
//
//TEST_CASE("Num Class") {
//    Num num1(5);
//    Num num2(5);
//    Num num3(10);
//    Num num4(5);
//    Num num5(5);
//
//    CHECK(num1.equals(&num2) == true);
//    CHECK(num1.equals(&num3) == false);
//    CHECK(num4.equals(&num5) == true);
//    CHECK(num4.equals(&num3) == false);
//    CHECK(num2.equals(&num3) == false);
//
//}
//
///**
//Num num1(5);
//Num num2(5);
//CHECK(num1.equals(&num2) == true);
//
//is the same as
//
//Num* num1 = new Num(5);
//Num* num2 = new Num(5);
//CHECK(num1->equals(num2) == true);
//
// * */
//
//TEST_CASE("Add Class") {
//    Num num1(5);
//    Num num2(10);
//    Add add1(&num1, &num2);
//    Add add2(&num1, &num2);
//    Add add3(&num1, &num1);
//    Num num3(5);
//    Num num4(10);
//    Add add4(&num3, &num4);
//
//    CHECK(add1.equals(&add2) == true);
//    CHECK(add1.equals(&add3) == false);
//    CHECK(add3.equals(&add4) == false);
//    CHECK(add1.equals(&add3) == false);
//    CHECK(add4.equals(&add4) == true);
//}
//
//TEST_CASE("Mult Class") {
//    Num num1(5);
//    Num num2(10);
//    Mult mult1(&num1, &num2);
//    Mult mult2(&num1, &num2);
//    Mult mult3(&num1, &num1);
//    Num num3(5);
//    Num num4(10);
//    Mult mult4(&num3, &num4);
//
//    CHECK(mult1.equals(&mult2) == true);
//    CHECK(mult1.equals(&mult3) == false);
//    CHECK(mult3.equals(&mult4) == false);
//    CHECK(mult1.equals(&mult3) == false);
//    CHECK(mult4.equals(&mult4) == true);
//}
//
//TEST_CASE("VarExpr Class") {
//    VarExpr var1("x");
//    VarExpr var2("x");
//    VarExpr var3("y");
//    VarExpr var4("z");
//    VarExpr var5("z");
//
//    CHECK(var1.equals(&var2) == true);
//    CHECK(var1.equals(&var3) == false);
//    CHECK(var4.equals(&var5) == true);
//    CHECK(var4.equals(&var3) == false);
//    CHECK(var2.equals(&var3) == false);
//}
//
//TEST_CASE("Mixed Expressions") {
//    Num num1(5);
//    VarExpr var1("x");
//    Add add1(&num1, &var1);
//    Mult mult1(&var1, &num1);
//
//    CHECK(add1.equals(&mult1) == false);
//    CHECK(var1.equals(&mult1) == false);
//}
//TEST_CASE("Prof. Nabil Tests for interp and subst") {
//    //interp
//    CHECK_THROWS_WITH((new VarExpr("x"))->interp(), "No value for variable");
//    CHECK( (new Mult(new Num(3), new Num(2)))->interp()==6 );
//    CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))->interp()==65);
//    //subst
//    CHECK( (new Add(new VarExpr("x"), new Num(7)))->subst("x", new VarExpr("y"))->equals(new Add(new VarExpr("y"), new Num(7))) );
//    CHECK( (new VarExpr("x"))->subst("x", new Add(new VarExpr("y"),new Num(7)))->equals(new Add(new VarExpr("y"),new Num(7))) );
//}
//
//TEST_CASE("has_variable tests") {
//    CHECK( (new Add(new Add(new Num(10), new VarExpr("x")),new Add(new Num(20),new Num(20))))->has_variable()==true);
//    CHECK( (new Add(new Add(new Num(10), new Num(10)),new Add(new Num(20),new Num(20))))->has_variable()==false);
//
//}
//
//
//TEST_CASE("NUM CLASS - interp, has_variable, subst") {
//    Num num(5);
//
//    // interp should return the value of the Num
//    CHECK(num.interp() == 5);
//
//    // Num will never have a variable
//    CHECK(num.has_variable() == false);
//
//    // subst should return the same Num object
//    Expr* substitutedNum = num.subst("x", new VarExpr("y"));
//    CHECK(substitutedNum->equals(&num) == true);
//}
//TEST_CASE("ADD CLASS - interp, has_variable, subst") {
//    Num num1(5);
//    Num num2(10);
//    Add add(&num1, &num2);
//
//    // interp should return the sum of the subexpressions
//    CHECK(add.interp() == 15);
//
//    // Add has a variable if any of its subexpressions has a variable
//    CHECK(add.has_variable() == false); // Both subexpressions are Num
//
//    // subst should replace variables in both subexpressions
//    Expr* substitutedAdd = add.subst("x", new VarExpr("y"));
//    CHECK(substitutedAdd->equals(&add) == true);
//
//    // Add with one Num and one VarExpr
//    VarExpr var("z");
//    Add addVar(&num1, &var);
//    CHECK(addVar.has_variable() == true);
//}
//
//TEST_CASE("MULT CLASS - interp, has_variable, subst") {
//    Num num1(5);
//    Num num2(10);
//    Mult mult(&num1, &num2);
//
//    // interp should return the product of the subexpressions
//    CHECK(mult.interp() == 50);
//
//    // Mult has a variable if any of its subexpressions has a variable
//    CHECK(mult.has_variable() == false); // Both subexpressions are Num
//
//    // subst should replace variables in both subexpressions
//    Expr* substitutedMult = mult.subst("x", new VarExpr("y"));
//    CHECK(substitutedMult->equals(&mult) == true);
//
//    // Mult with one Num and one VarExpr
//    VarExpr var("z");
//    Mult multVar(&num1, &var);
//    CHECK(multVar.has_variable() == true);
//}
//TEST_CASE("VAR-EXPR CLASS - interp, has_variable, subst") {
//    VarExpr var("x");
//
//    // interp should throw a std::runtime_error for VarExpr
//    CHECK_THROWS_AS(var.interp(), std::runtime_error);
//
//    // VarExpr is always a variable
//    CHECK(var.has_variable() == true);
//
//    // subst should replace the variable if it matches
//    Expr* substitutedVar = var.subst("x", new Num(5));
//    CHECK(substitutedVar->equals(new Num(5)) == true);
//
//    // subst should not replace if the variable doesn't match
//    substitutedVar = var.subst("y", new Num(5));
//    CHECK(substitutedVar->equals(&var) == true);
//}
//
////----------------------------------
////            HW4 TESTS
////----------------------------------
//TEST_CASE("Professor Nabil's Tests") {
//
//
//    CHECK((new Mult(new Add(new Num(2), new Num(3)), new Mult(new Num(4), new Num(6))))->to_pp_string() == "(2 + 3) * 4 * 6");
//    CHECK ( (new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pp_string() ==  "1 * (2 + 3)" );
//    CHECK ( (new Mult(new Mult(new Num(8), new Num(1)), new VarExpr("y")))->to_pp_string() ==  "(8 * 1) * y" );
//    CHECK ( (new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pp_string() ==  "(3 + 5) * 6 * 1" );
//    CHECK ( (new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))) )->to_pp_string() ==  "(7 * 7) * (9 + 2)" );
//
//}
//TEST_CASE("Add Print & pretty-print") {
//    SECTION("Print: Add functionality"){
//        Add *addPrintExp = new Add(new Num(1), new Add(new Num(2), new Num(3)));
//        std::string exp = "(1+(2+3))";
//        Add *addPrintExp2 = new Add(new Add(new Num(2), new Num(3)), new Add(new Num(2), new Num(3)));
//        std::string exp2 = "((2+3)+(2+3))";
//        //printExp->prettyPrint(std::cout);
//        CHECK( (new Num(10))->to_string() == "10" );
//        CHECK( addPrintExp->to_string() == exp );
//        CHECK( addPrintExp2->to_string() == exp2 );
//
//    }
//    SECTION("Print: Add with negative numbers"){
//        Add *addPrintExp = new Add(new Num(-1), new Add(new Num(-2), new Num(-3)));
//        std::string exp = "(-1+(-2+-3))";
//        CHECK( addPrintExp->to_string() == exp );
//
//        Add *addPrintExp2 = new Add(new Add(new Num(-2), new Num(-3)), new Add(new Num(-2), new Num(-3)));
//        std::string exp2 = "((-2+-3)+(-2+-3))";
//        CHECK( addPrintExp2->to_string() == exp2 );
//    }
//
//    SECTION("Pretty print: Add functionality"){
//        Add *addPrintExp = new Add(new Num(1), new Add(new Num(2), new Num(3)));
//        std::string exp = "1 + 2 + 3";
//        Add *addPrintExp2 = new Add(new Add(new Num(2), new Num(3)), new Add(new Num(2), new Num(3)));
//        std::string exp2 = "2 + 3 + 2 + 3";
//        //printExp->prettyPrint(std::cout);
//        CHECK( addPrintExp->to_pp_string() == exp );
//        CHECK( addPrintExp2->to_pp_string() == exp2 );
//    }
//    SECTION("Pretty print: Add with Negative Numbers"){
//        Add *addPrintExp = new Add(new Num(-1), new Add(new Num(-2), new Num(-3)));
//        std::string exp = "-1 + -2 + -3";
//        Add *addPrintExp2 = new Add(new Add(new Num(-2), new Num(-3)), new Add(new Num(-2), new Num(-3)));
//        std::string exp2 = "-2 + -3 + -2 + -3";
//        //printExp->prettyPrint(std::cout);
//        CHECK( addPrintExp->to_pp_string() == exp );
//        CHECK( addPrintExp2->to_pp_string() == exp2 );
//    }
//}
//TEST_CASE("Mult Print & pretty-print") {
//    SECTION("Print: Mult functionality"){
//        Mult *multPrintExp = new Mult(new Num(2), new Mult(new Num(3), new Num(4)));
//        std::string exp = "(2*(3*4))";
//        Mult *multPrintExp2 = new Mult(new Mult(new Num(2), new Num(3)), new Mult(new Num(4), new Num(5)));
//        std::string exp2 = "((2*3)*(4*5))";
//        CHECK( multPrintExp->to_string() == exp );
//        CHECK( multPrintExp2->to_string() == exp2 );
//    }
//
//    SECTION("Print: Mult with negative numbers"){
//        Mult *multPrintExp = new Mult(new Num(-2), new Mult(new Num(-3), new Num(-4)));
//        std::string exp = "(-2*(-3*-4))";
//        CHECK( multPrintExp->to_string() == exp );
//
//        Mult *multPrintExp2 = new Mult(new Mult(new Num(-2), new Num(-3)), new Mult(new Num(-4), new Num(-5)));
//        std::string exp2 = "((-2*-3)*(-4*-5))";
//        CHECK( multPrintExp2->to_string() == exp2 );
//    }
//
//    SECTION("Pretty print: Mult functionality"){
//        Mult *multPrintExp = new Mult(new Num(2), new Mult(new Num(3), new Num(4)));
//        std::string exp = "2 * 3 * 4";
//        Mult *multPrintExp2 = new Mult(new Mult(new Num(2), new Num(3)), new Mult(new Num(4), new Num(5)));
//        std::string exp2 = "(2 * 3) * 4 * 5";
//        CHECK( multPrintExp->to_pp_string() == exp );
//        CHECK( multPrintExp2->to_pp_string() == exp2 );
//    }
//
//    SECTION("Pretty print: Mult with Negative Numbers"){
//        Mult *multPrintExp = new Mult(new Num(-2), new Mult(new Num(-3), new Num(-4)));
//        std::string exp = "-2 * -3 * -4";
//        Mult *multPrintExp2 = new Mult(new Mult(new Num(-2), new Num(-3)), new Mult(new Num(-4), new Num(-5)));
//        std::string exp2 = "(-2 * -3) * -4 * -5";
//        CHECK( multPrintExp->to_pp_string() == exp );
//        CHECK( multPrintExp2->to_pp_string() == exp2 );
//    }
//}
//TEST_CASE("VarExpr Print & pretty-print") {
//    SECTION("Print: VarExpr functionality") {
//        VarExpr *varPrintExp = new VarExpr("x");
//        std::string exp = "x";
//        CHECK(varPrintExp->to_string() == exp);
//
//        VarExpr *varPrintExp2 = new VarExpr("y");
//        std::string exp2 = "y";
//        CHECK(varPrintExp2->to_string() == exp2);
//    }
//
//    SECTION("Pretty print: VarExpr functionality") {
//        VarExpr *varPrintExp = new VarExpr("x");
//        std::string exp = "x";
//        CHECK(varPrintExp->to_pp_string() == exp);
//
//        VarExpr *varPrintExp2 = new VarExpr("y");
//        std::string exp2 = "y";
//        CHECK(varPrintExp2->to_pp_string() == exp2);
//    }
//}

//---------------------------------------------
//             Test _let CLASS
//---------------------------------------------

TEST_CASE("Substitution and Interp in Let Expression") {
    SECTION("Simple interp in Let Expression") {
        Expr *varX = new VarExpr("x");
        Expr *num2 = new Num(2);
        Expr *letExpr = new _let("x", num2, new Add(varX, varX)); // let x = 2 in (x+x)
        CHECK(letExpr->interp()->equals(new NumVal(4)));
        // let x = 2 in x + x  => 4
    }
    SECTION("Nested Let Expression") {
        Expr *_X = new VarExpr("x");
        Expr *_Y = new VarExpr("y");
        Expr *_2 = new Num(2);
        Expr *_3 = new Num(3);

        //_let y=3 _in x + y
        Expr *inner_letExpr = new _let("y", _3, new Add(_X, _Y));
        //_let x=2 _in _let y=3 _in x + y
        Expr *outter_letExpr = new _let("x", _2, inner_letExpr);
        // outter_letExp = 5
        CHECK(outter_letExpr->interp()->equals(new NumVal(5)));

    }

    SECTION("Testing substitute"){
        //substitute non-bound rhs
        // let x = (y +1) in x
        _let* letExpr = new _let("x", new Add(new VarExpr("y"), new Num(1)), new VarExpr("x"));
        //let x = (5 + 1) in x
        Expr* substituted = letExpr->subst("y", new Num(5));
        // substitute should equal let x = (5 + 1) in x
        CHECK( substituted->equals(new _let("x", new Add(new Num(5), new Num(1)), new VarExpr("x"))) == true );

        //Check substitute does not sub bounded rhs
        // let x = 5  in (x + 3)
        _let* letExpr1 = new _let("x", new Num(5), new Add(new VarExpr("x"), new Num(3)));
        // let x = 5  in (x + 3) does not substitute to let x = 5  in (10 + 3)
        Expr* substituted1 = letExpr1->subst("x", new Num(10));
        CHECK( substituted1->equals(letExpr1) == true );

        //Substitution in body
        //let x = 5 in (y + 3)
        _let* letExpr2 = new _let("x", new Num(5), new Add(new VarExpr("y"), new Num(3)));
        //sub y in let x = 5 in (y + 3) with 2
        Expr* substituted2 = letExpr2->subst("y", new Num(2));
        //substituted2 should be x = 5 in (2 + 3)
        CHECK( substituted2->equals(new _let("x", new Num(5), new Add(new Num(2), new Num(3)))) == true );
    }


    SECTION("Pretty Print") {
        //Let nested to the left in add expression which is nested to the right within a multiplication expression
        CHECK((new Mult(new Num(5), new Add(new _let("x", new Num(5), new VarExpr("x")), new Num(1))))->to_pp_string() == "5 * ((_let x = 5\n"
                                                                                                                             "       _in  x) + 1)");
        //Let in lhs of add
        CHECK ( (new Add(new _let("x", new Num(2), new Add(new VarExpr("x"), new Num(9))), new Num(4)))->to_pp_string() == "(_let x = 2\n"
                                                                                                                              "  _in  x + 9) + 4");
        //Let in lhs of multiplication expression
        CHECK((new Mult(new _let("x", new Num(5), new Add(new VarExpr("x"), new Num(8))), new Num(3)))->to_pp_string() == "(_let x = 5\n"
                                                                                                                             "  _in  x + 8) * 3");
        //Let nest as right argument of un-parenthesized multiplication expression
        CHECK((new Add (new Mult(new Num(4), new _let("x", new Num(5), new Add(new VarExpr("x"), new Num(1)))), new Num(9)))->to_pp_string() == "4 * (_let x = 5\n"
                                                                                                                                                   "      _in  x + 1) + 9");
        //Let nested to the left within let that is nested to the left within add
        CHECK ((new Add(new _let("x", new Num(3), new _let("y", new Num(3), new Add(new VarExpr("y"), new Num(2))) ), new VarExpr("x")))->to_pp_string() == "(_let x = 3\n"
                                                                                                                                                                   "  _in  _let y = 3\n"
                                                                                                                                                                   "       _in  y + 2) + x");
        //Let nested in lhs of Add expression nested within body of let expression
        CHECK((new _let("x", new Num(5), new Add(new _let("y" , new Num(3), new Add(new VarExpr("y"), new Num(2))), new VarExpr("x"))))
                      ->to_pp_string() == "_let x = 5\n"
                                         " _in  (_let y = 3\n"
                                         "       _in  y + 2) + x");
        //Triple nested let
        CHECK( ( new _let( "x", new Num(5),
                              new Add( new _let( "y", new Num(3),
                                                    new Add( new VarExpr("y"), new _let("z",new Num(6),
                                                                                            new Add(new VarExpr("a"), new Num(8))) ) ), new VarExpr("x") ) ) )
                       ->to_pp_string()== "_let x = 5\n"
                                         " _in  (_let y = 3\n"
                                         "       _in  y + _let z = 6\n"
                                         "                _in  a + 8) + x" );
    }

}

//---------------------------------------------
//             Test parse CLASS
//---------------------------------------------

TEST_CASE("Class: Parse tests") {

    SECTION("Number parsing") {

        std::stringstream ss("42");
        Expr* e = parse(ss);
        REQUIRE(e->to_string() == "42");

        ss.str("-15");
        ss.clear(); // Clear flags
        e = parse(ss);
        REQUIRE(e->to_string() == "-15");
    }


    SECTION("Add expression parsing") {
        std::stringstream ss("1 + 2");
        Expr* e = parse(ss);
        REQUIRE(e->to_string() == "(1+2)");

        ss.str("3 + 4 + 5");
        ss.clear(); // Clear flags
        e = parse(ss);
        REQUIRE(e->to_string() == "((3+4)+5)");
    }

    SECTION("Mult expression parsing") {
        std::stringstream ss("2 * 3");
        Expr* e = parse(ss);
        REQUIRE(e->to_string() == "(2*3)");

        ss.str("4 * 5 * 6");
        ss.clear(); // Clear flags
        e = parse(ss);
        REQUIRE(e->to_string() == "(4*(5*6))");
    }

    SECTION("Mixed expressions parsing") {
        std::stringstream ss("1 + 2 * 3");
        Expr* e = parse(ss);
        REQUIRE(e->to_string() == "(1+(2*3))");

        ss.str("(4 + 5) * 6");
        ss.clear(); // Clear flags
        e = parse(ss);
        REQUIRE(e->to_string() == "((4+5)*6)");
    }
}

// Function to parse a string into an Expr*
Expr* parse_str(const std::string &str) {
    std::istringstream iss(str);
    return parse(iss);
}

TEST_CASE("parse") {
    CHECK_THROWS_WITH( parse_str("()"), "invalid input" );

    CHECK( parse_str("(1)")->equals(new Num(1)) );
    CHECK( parse_str("(((1)))")->equals(new Num(1)) );

    CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );

    CHECK( parse_str("1")->equals(new Num(1)) );
    CHECK( parse_str("10")->equals(new Num(10)) );
    CHECK( parse_str("-3")->equals(new Num(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(new Num(5)) );
    CHECK_THROWS_WITH( parse_str("-"), "Invalid input" );
    CHECK_THROWS_WITH( parse_str(" -   5  "), "Invalid input" );

    CHECK( parse_str("x")->equals(new VarExpr("x")) );
    CHECK( parse_str("xyz")->equals(new VarExpr("xyz")) );
    CHECK( parse_str("xYz")->equals(new VarExpr("xYz")) );
    CHECK_THROWS_WITH( parse_str("x_z"), "Invalid input" );

    CHECK( parse_str("x + y")->equals(new Add(new VarExpr("x"), new VarExpr("y"))) );

    CHECK( parse_str("x * y")->equals(new Mult(new VarExpr("x"), new VarExpr("y"))) );

    CHECK( parse_str("z * x + y")
                   ->equals(new Add(new Mult(new VarExpr("z"), new VarExpr("x")),
                                    new VarExpr("y"))) );

    CHECK( parse_str("z * (x + y)")
                   ->equals(new Mult(new VarExpr("z"),
                                     new Add(new VarExpr("x"), new VarExpr("y"))) ));

}
TEST_CASE("HW8: Refactor interp + Val class") {

    SECTION("testing_let_parse") {
        CHECK(parse_str(("_let x=5 _in (x+7)"))->equals(
                new _let("x", new Num(5), new Add(new VarExpr("x"), new Num(7)))));

        CHECK(parse_str(("_let x=5 _in (x+7)"))->equals(
                new _let("x", new Num(5), new Add(new VarExpr("x"), new Num(7)))));
        CHECK(parse_str(("_let x=10 _in (y+10)"))->equals(
                new _let("x", new Num(10), new Add(new VarExpr("y"), new Num(10)))));
        CHECK(parse_str(("(_let x=5 _in ((_let y=3 _in (y+2))+x))"))
                      ->equals(new _let("x", new Num(5),
                                        new Add(new _let("y", new Num(3), new Add(new VarExpr("y"), new Num(2))),
                                                new VarExpr("x")))));
        CHECK(parse_str(("(_let x=5 _in (x+7))"))->equals(
                (new _let("x", new Num(5), new Add(new VarExpr("x"), new Num(7))))));
    }

    SECTION("Num interprets to NumVal", "[NumVal]") {
        Expr *num = new Num(5);
        Val *expected = new NumVal(5);
        REQUIRE(num->interp()->equals(expected));
    }

    SECTION("Add interprets correctly", "[Add]") {
        Expr *num1 = new Num(5);
        Expr *num2 = new Num(3);
        Expr *addExpr = new Add(num1, num2);
        Val *expected = new NumVal(8);
        REQUIRE(addExpr->interp()->equals(expected));
    }
    SECTION("Mult interprets correctly", "[Mult]") {
        Expr *num1 = new Num(4);
        Expr *num2 = new Num(2);
        Expr *multExpr = new Mult(num1, num2);
        Val *expected = new NumVal(8);
        REQUIRE(multExpr->interp()->equals(expected));
    }
    SECTION("VarExpr throws exception on interp", "[VarExpr]") {
        Expr *varExpr = new VarExpr("x");
        REQUIRE_THROWS_AS(varExpr->interp(), std::runtime_error);
    }
    SECTION("NumVal equals works correctly", "[NumVal]") {
        Val *val1 = new NumVal(10);
        Val *val2 = new NumVal(10);
        Val *val3 = new NumVal(5);
        REQUIRE(val1->equals(val2));
        REQUIRE_FALSE(val1->equals(val3));
    }
}

TEST_CASE("HW9 Conditionals"){
    SECTION("(1 + 2) evaluated to 3", "[NumVal]") {
        //1 + 2 -> 3
        CHECK( (new Add(new Num(1), new Num(2)))->interp()->equals(new NumVal(3)) );
    }
    SECTION("_let x = 2+3 _in x*x evaluated to 25", "[NumVal] and [_let]"){
        //_let x = 2+3
        //_in x*x
        CHECK( (new _let("x",
                            new Add(new Num(2), new Num(3)),
                            new Mult(new VarExpr("x"), new VarExpr("x"))))
                       ->interp()
                       ->equals(new NumVal(25)) );
    }
    SECTION("_if _true _then 1 _else 2 evaluated to 1", "[IfExpr] and [BoolExpr]"){
        //_if _true
        //_then 1
        //_else 2
        CHECK( (new IfExpr(new BoolExpr(true),
                           new Num(1),
                           new Num(2)))->interp()
                       ->equals(new NumVal(1)) );
    }
    SECTION("(1 == 2) + 3 throws an exception", "[Add]") {
        Expr* testExpr = new Add(new EqExpr(new Num(1), new Num(2)), new Num(3));
        CHECK_THROWS_WITH(testExpr->interp(), "Cannot add boolean values.");
    }

    SECTION("1 == 2 + 3 evaluates to _false", "[EqExpr]") {
        Expr* testExpr = new EqExpr(new Num(1), new Add(new Num(2), new Num(3)));
        Val* result = testExpr->interp();
        CHECK((result)->to_string() == "_false");
        //std::cout << "testBool: " << (new BoolExpr(true))->interp()->to_string() << std::endl;

    }

    SECTION("1 + 1 == 2 + 0 evaluates to _true", "[EqExpr]") {
        Expr* testExpr = new EqExpr(new Add(new Num(1), new Num(1)), new Add(new Num(2), new Num(0)));
        Val* result = testExpr->interp();
        CHECK((result)->to_string() == "_true");
    }
    SECTION("_let same = 1 == 2 _in _if 1 == 2 _then _false + 5 _else 88 should interp to the value 88", "[Let][IfExpr]") {
        //_let same = 1 == 2
        //_in  _if 1 == 2
        //     _then _false + 5
        //     _else 88

        // Constructing the inner equality expression 1 == 2
        Expr* equality = new EqExpr(new Num(1), new Num(2));

        // Constructing the if-expression part
        Expr* ifExpr = new IfExpr(
                new EqExpr(new Num(1), new Num(2)), // condition: 1 == 2
                new Add(new BoolExpr(false), new Num(5)), // then: _false + 5 (This is expected not to be evaluated)
                new Num(88) // else: 88
        );

        // Constructing the let-expression
        Expr* letExpr = new _let(
                "same", // variable name
                equality, // binding expression: 1 == 2
                ifExpr // body of the let-expression
        );

        // Interpreting the let-expression
        Val* result = letExpr->interp();

        // Convert the result to a NumVal to extract its value
        NumVal* numResult = dynamic_cast<NumVal*>(result);

        CHECK(numResult->to_string() == "88"); // Verify the result is 88

    }
}

TEST_CASE("HW9-Parsing") {
    SECTION("Parsing BoolExpr") {
        CHECK(parse_str(("_true"))->equals(new BoolExpr(true)));
        CHECK(parse_str(("_false"))->equals(new BoolExpr(false)));
    }

    SECTION("Parsing _if") {
        CHECK(parse_str(("_if _true _then 1 _else 2"))->equals(
                new IfExpr(new BoolExpr(true), new Num(1), new Num(2))));
        CHECK(parse_str(("_if _false _then 1 _else 2"))->equals(
                new IfExpr(new BoolExpr(false), new Num(1), new Num(2))));
        CHECK(parse_str(("_if 1 == 2 _then 1 _else 2"))->equals(
                new IfExpr(new EqExpr(new Num(1), new Num(2)), new Num(1), new Num(2))));
    }
    SECTION("Equality parsing") {
        CHECK( parse_str("1 == 2")->interp()->equals(new BoolVal(false)) );
        CHECK((((parse_str("_if 1 == 2 _then 5 _else 6"))->interp())->to_string()) == "6");
        CHECK((parse_str("1 + 2 == 3 + 0"))->interp()->to_string() == "_true");

    }
}




