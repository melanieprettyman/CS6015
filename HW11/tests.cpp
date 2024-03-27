//
// Created by Melanie Prettyman on 2/1/24.
//

#include <iostream>
#include "tests.h"
#include "val.h"


//---------------------------------------------
//             Test _let CLASS
//---------------------------------------------

TEST_CASE("Substitution and Interp in Let Expression") {
    SECTION("Simple interp in Let Expression") {
        PTR(Expr)varX = NEW(VarExpr)("x");
        PTR(Expr)num2 = NEW(Num)(2);
        PTR(Expr)letExpr = NEW(_let)("x", num2, NEW(Add)(varX, varX)); // let x = 2 in (x+x)
        CHECK(letExpr->interp()->equals(NEW(NumVal)(4)));
        // let x = 2 in x + x  => 4
    }
    SECTION("Nested Let Expression") {
        PTR(Expr)_X = NEW(VarExpr)("x");
        PTR(Expr)_Y = NEW(VarExpr)("y");
        PTR(Expr)_2 = NEW(Num)(2);
        PTR(Expr)_3 = NEW(Num)(3);

        //_let y=3 _in x + y
        PTR(Expr)inner_letExpr = NEW(_let)("y", _3, NEW(Add)(_X, _Y));
        //_let x=2 _in _let y=3 _in x + y
        PTR(Expr)outter_letExpr = NEW(_let)("x", _2, inner_letExpr);
        // outter_letExp = 5
        CHECK(outter_letExpr->interp()->equals(NEW(NumVal)(5)));

    }

    SECTION("Testing substitute"){
        //substitute non-bound rhs
        // let x = (y +1) in x
        PTR(_let) letExpr = NEW(_let)("x", NEW(Add)(NEW(VarExpr)("y"), NEW(Num)(1)), NEW(VarExpr)("x"));
        //let x = (5 + 1) in x
        PTR(Expr) substituted = letExpr->subst("y", NEW(Num)(5));
        // substitute should equal let x = (5 + 1) in x
        CHECK( substituted->equals(NEW(_let)("x", NEW(Add)(NEW(Num)(5), NEW(Num)(1)), NEW(VarExpr)("x"))) == true );

        //Check substitute does not sub bounded rhs
        // let x = 5  in (x + 3)
        PTR(_let) letExpr1 = NEW(_let)("x", NEW(Num)(5), NEW(Add)(NEW(VarExpr)("x"), NEW(Num)(3)));
        // let x = 5  in (x + 3) does not substitute to let x = 5  in (10 + 3)
        PTR(Expr) substituted1 = letExpr1->subst("x", NEW(Num)(10));
        CHECK( substituted1->equals(letExpr1) == true );

        //Substitution in body
        //let x = 5 in (y + 3)
        PTR(_let) letExpr2 = NEW(_let)("x", NEW(Num)(5), NEW(Add)(NEW(VarExpr)("y"), NEW(Num)(3)));
        //sub y in let x = 5 in (y + 3) with 2
        PTR(Expr) substituted2 = letExpr2->subst("y", NEW(Num)(2));
        //substituted2 should be x = 5 in (2 + 3)
        CHECK( substituted2->equals(NEW(_let)("x", NEW(Num)(5), NEW(Add)(NEW(Num)(2), NEW(Num)(3)))) == true );
    }


    SECTION("Pretty Print") {
        //Let nested to the left in add expression which is nested to the right within a multiplication expression
        CHECK((NEW(Mult)(NEW(Num)(5), NEW(Add)(NEW(_let)("x", NEW(Num)(5), NEW(VarExpr)("x")), NEW(Num)(1))))->to_pp_string() == "5 * ((_let x = 5\n"
                                                                                                                             "       _in  x) + 1)");
        //Let in lhs of add
        CHECK ( (NEW(Add)(NEW(_let)("x", NEW(Num)(2), NEW(Add)(NEW(VarExpr)("x"), NEW(Num)(9))), NEW(Num)(4)))->to_pp_string() == "(_let x = 2\n"
                                                                                                                              "  _in  x + 9) + 4");
        //Let in lhs of multiplication expression
        CHECK((NEW(Mult)(NEW(_let)("x", NEW(Num)(5), NEW(Add)(NEW(VarExpr)("x"), NEW(Num)(8))), NEW(Num)(3)))->to_pp_string() == "(_let x = 5\n"
                                                                                                                             "  _in  x + 8) * 3");
        //Let nest as right argument of un-parenthesized multiplication expression
        CHECK((NEW(Add) (NEW(Mult)(NEW(Num)(4), NEW(_let)("x", NEW(Num)(5), NEW(Add)(NEW(VarExpr)("x"), NEW(Num)(1)))), NEW(Num)(9)))->to_pp_string() == "4 * (_let x = 5\n"
                                                                                                                                                   "      _in  x + 1) + 9");
        //Let nested to the left within let that is nested to the left within add
        CHECK ((NEW(Add)(NEW(_let)("x", NEW(Num)(3), NEW(_let)("y", NEW(Num)(3), NEW(Add)(NEW(VarExpr)("y"), NEW(Num)(2))) ), NEW(VarExpr)("x")))->to_pp_string() == "(_let x = 3\n"
                                                                                                                                                                   "  _in  _let y = 3\n"
                                                                                                                                                                   "       _in  y + 2) + x");
        //Let nested in lhs of Add expression nested within body of let expression
        CHECK((NEW(_let)("x", NEW(Num)(5), NEW(Add)(NEW(_let)("y" , NEW(Num)(3), NEW(Add)(NEW(VarExpr)("y"), NEW(Num)(2))), NEW(VarExpr)("x"))))
                      ->to_pp_string() == "_let x = 5\n"
                                         " _in  (_let y = 3\n"
                                         "       _in  y + 2) + x");
        //Triple nested let
        CHECK( ( NEW(_let)( "x", NEW(Num)(5),
                              NEW(Add)( NEW(_let)( "y", NEW(Num)(3),
                                                    NEW(Add)( NEW(VarExpr)("y"), NEW(_let)("z",NEW(Num)(6),
                                                                                            NEW(Add)(NEW(VarExpr)("a"), NEW(Num)(8))) ) ), NEW(VarExpr)("x") ) ) )
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
        PTR(Expr) e = parse(ss);
        REQUIRE(e->to_string() == "42");

        ss.str("-15");
        ss.clear(); // Clear flags
        e = parse(ss);
        REQUIRE(e->to_string() == "-15");
    }


    SECTION("Add expression parsing") {
        std::stringstream ss("1 + 2");
        PTR(Expr) e = parse(ss);
        REQUIRE(e->to_string() == "(1+2)");

        ss.str("3 + 4 + 5");
        ss.clear(); // Clear flags
        e = parse(ss);
        REQUIRE(e->to_string() == "((3+4)+5)");
    }

    SECTION("Mult expression parsing") {
        std::stringstream ss("2 * 3");
        PTR(Expr) e = parse(ss);
        REQUIRE(e->to_string() == "(2*3)");

        ss.str("4 * 5 * 6");
        ss.clear(); // Clear flags
        e = parse(ss);
        REQUIRE(e->to_string() == "(4*(5*6))");
    }

    SECTION("Mixed expressions parsing") {
        std::stringstream ss("1 + 2 * 3");
        PTR(Expr) e = parse(ss);
        REQUIRE(e->to_string() == "(1+(2*3))");

        ss.str("(4 + 5) * 6");
        ss.clear(); // Clear flags
        e = parse(ss);
        REQUIRE(e->to_string() == "((4+5)*6)");
    }
}

// Function to parse a string into an PTR(Expr)
PTR(Expr) parse_str(const std::string &str) {
    std::istringstream iss(str);
    return parse(iss);
}

TEST_CASE("parse") {
    CHECK_THROWS_WITH( parse_str("()"), "invalid input" );

    CHECK( parse_str("(1)")->equals(NEW(Num)(1)) );
    CHECK( parse_str("(((1)))")->equals(NEW(Num)(1)) );

    CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );

    CHECK( parse_str("1")->equals(NEW(Num)(1)) );
    CHECK( parse_str("10")->equals(NEW(Num)(10)) );
    CHECK( parse_str("-3")->equals(NEW(Num)(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(NEW(Num)(5)) );
    CHECK_THROWS_WITH( parse_str("-"), "Invalid input" );
    CHECK_THROWS_WITH( parse_str(" -   5  "), "Invalid input" );

    CHECK( parse_str("x")->equals(NEW(VarExpr)("x")) );
    CHECK( parse_str("xyz")->equals(NEW(VarExpr)("xyz")) );
    CHECK( parse_str("xYz")->equals(NEW(VarExpr)("xYz")) );
    CHECK_THROWS_WITH( parse_str("x_z"), "Invalid input" );

    CHECK( parse_str("x + y")->equals(NEW(Add)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))) );

    CHECK( parse_str("x * y")->equals(NEW(Mult)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))) );

    CHECK( parse_str("z * x + y")
                   ->equals(NEW(Add)(NEW(Mult)(NEW(VarExpr)("z"), NEW(VarExpr)("x")),
                                    NEW(VarExpr)("y"))) );

    CHECK( parse_str("z * (x + y)")
                   ->equals(NEW(Mult)(NEW(VarExpr)("z"),
                                     NEW(Add)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))) ));

}
TEST_CASE("HW8: Refactor interp + Val class") {

    SECTION("testing_let_parse") {
        CHECK(parse_str(("_let x=5 _in (x+7)"))->equals(
                NEW(_let)("x", NEW(Num)(5), NEW(Add)(NEW(VarExpr)("x"), NEW(Num)(7)))));

        CHECK(parse_str(("_let x=5 _in (x+7)"))->equals(
                NEW(_let)("x", NEW(Num)(5), NEW(Add)(NEW(VarExpr)("x"), NEW(Num)(7)))));
        CHECK(parse_str(("_let x=10 _in (y+10)"))->equals(
                NEW(_let)("x", NEW(Num)(10), NEW(Add)(NEW(VarExpr)("y"), NEW(Num)(10)))));
        CHECK(parse_str(("(_let x=5 _in ((_let y=3 _in (y+2))+x))"))
                      ->equals(NEW(_let)("x", NEW(Num)(5),
                                        NEW(Add)(NEW(_let)("y", NEW(Num)(3), NEW(Add)(NEW(VarExpr)("y"), NEW(Num)(2))),
                                                NEW(VarExpr)("x")))));
        CHECK(parse_str(("(_let x=5 _in (x+7))"))->equals(
                (NEW(_let)("x", NEW(Num)(5), NEW(Add)(NEW(VarExpr)("x"), NEW(Num)(7))))));
    }

    SECTION("Num interprets to NumVal", "[NumVal]") {
        PTR(Expr)num = NEW(Num)(5);
        PTR(Val)expected = NEW(NumVal)(5);
        REQUIRE(num->interp()->equals(expected));
    }

    SECTION("Add interprets correctly", "[Add]") {
        PTR(Expr)num1 = NEW(Num)(5);
        PTR(Expr)num2 = NEW(Num)(3);
        PTR(Expr)addExpr = NEW(Add)(num1, num2);
        PTR(Val)expected = NEW(NumVal)(8);
        REQUIRE(addExpr->interp()->equals(expected));
    }
    SECTION("Mult interprets correctly", "[Mult]") {
        PTR(Expr)num1 = NEW(Num)(4);
        PTR(Expr)num2 = NEW(Num)(2);
        PTR(Expr)multExpr = NEW(Mult)(num1, num2);
        PTR(Val)expected = NEW(NumVal)(8);
        REQUIRE(multExpr->interp()->equals(expected));
    }
    SECTION("VarExpr throws exception on interp", "[VarExpr]") {
        PTR(Expr)varExpr = NEW(VarExpr)("x");
        REQUIRE_THROWS_AS(varExpr->interp(), std::runtime_error);
    }
    SECTION("NumVal equals works correctly", "[NumVal]") {
        PTR(Val)val1 = NEW(NumVal)(10);
        PTR(Val)val2 = NEW(NumVal)(10);
        PTR(Val)val3 = NEW(NumVal)(5);
        REQUIRE(val1->equals(val2));
        REQUIRE_FALSE(val1->equals(val3));
    }
}

TEST_CASE("HW9 Conditionals"){
    SECTION("(1 + 2) evaluated to 3", "[NumVal]") {
        //1 + 2 -> 3
        CHECK( (NEW(Add)(NEW(Num)(1), NEW(Num)(2)))->interp()->equals(NEW(NumVal)(3)) );
    }
    SECTION("_let x = 2+3 _in x*x evaluated to 25", "[NumVal] and [_let]"){
        //_let x = 2+3
        //_in x*x
        CHECK( (NEW(_let)("x",
                            NEW(Add)(NEW(Num)(2), NEW(Num)(3)),
                            NEW(Mult)(NEW(VarExpr)("x"), NEW(VarExpr)("x"))))
                       ->interp()
                       ->equals(NEW(NumVal)(25)) );
    }
    SECTION("_if _true _then 1 _else 2 evaluated to 1", "[IfExpr] and [BoolExpr]"){
        //_if _true
        //_then 1
        //_else 2
        CHECK( (NEW(IfExpr)(NEW(BoolExpr)(true),
                           NEW(Num)(1),
                           NEW(Num)(2)))->interp()
                       ->equals(NEW(NumVal)(1)) );
    }
    SECTION("(1 == 2) + 3 throws an exception", "[Add]") {
        PTR(Expr) testExpr = NEW(Add)(NEW(EqExpr)(NEW(Num)(1), NEW(Num)(2)), NEW(Num)(3));
        CHECK_THROWS_WITH(testExpr->interp(), "Cannot add boolean values.");
    }

    SECTION("1 == 2 + 3 evaluates to _false", "[EqExpr]") {
        PTR(Expr) testExpr = NEW(EqExpr)(NEW(Num)(1), NEW(Add)(NEW(Num)(2), NEW(Num)(3)));
        PTR(Val) result = testExpr->interp();
        CHECK((result)->to_string() == "_false");
        //std::cout << "testBool: " << (NEW(BoolExpr)(true))->interp()->to_string() << std::endl;

    }

    SECTION("1 + 1 == 2 + 0 evaluates to _true", "[EqExpr]") {
        PTR(Expr) testExpr = NEW(EqExpr)(NEW(Add)(NEW(Num)(1), NEW(Num)(1)), NEW(Add)(NEW(Num)(2), NEW(Num)(0)));
        PTR(Val) result = testExpr->interp();
        CHECK((result)->to_string() == "_true");
    }
    SECTION("_let same = 1 == 2 _in _if 1 == 2 _then _false + 5 _else 88 should interp to the value 88", "[Let][IfExpr]") {
        //_let same = 1 == 2
        //_in  _if 1 == 2
        //     _then _false + 5
        //     _else 88

        // Constructing the inner equality expression 1 == 2
        PTR(Expr) equality = NEW(EqExpr)(NEW(Num)(1), NEW(Num)(2));

        // Constructing the if-expression part
        PTR(Expr) ifExpr = NEW(IfExpr)(
                NEW(EqExpr)(NEW(Num)(1), NEW(Num)(2)), // condition: 1 == 2
                NEW(Add)(NEW(BoolExpr)(false), NEW(Num)(5)), // then: _false + 5 (This is expected not to be evaluated)
                NEW(Num)(88) // else: 88
        );

        // Constructing the let-expression
        PTR(Expr) letExpr = NEW(_let)(
                "same", // variable name
                equality, // binding expression: 1 == 2
                ifExpr // body of the let-expression
        );

        // Interpreting the let-expression
        PTR(Val) result = letExpr->interp();

        // Convert the result to a NumVal to extract its value
        PTR(NumVal) numResult = CAST(NumVal)(result);

        CHECK(numResult->to_string() == "88"); // Verify the result is 88

    }
}

TEST_CASE("HW9-Parsing") {
    SECTION("Parsing BoolExpr") {
        CHECK(parse_str(("_true"))->equals(NEW(BoolExpr)(true)));
        CHECK(parse_str(("_false"))->equals(NEW(BoolExpr)(false)));
    }

    SECTION("Parsing _if") {
        CHECK(parse_str(("_if _true _then 1 _else 2"))->equals(
                NEW(IfExpr)(NEW(BoolExpr)(true), NEW(Num)(1), NEW(Num)(2))));
        CHECK(parse_str(("_if _false _then 1 _else 2"))->equals(
                NEW(IfExpr)(NEW(BoolExpr)(false), NEW(Num)(1), NEW(Num)(2))));
        CHECK(parse_str(("_if 1 == 2 _then 1 _else 2"))->equals(
                NEW(IfExpr)(NEW(EqExpr)(NEW(Num)(1), NEW(Num)(2)), NEW(Num)(1), NEW(Num)(2))));
    }
    SECTION("Equality parsing") {
        CHECK( parse_str("1 == 2")->interp()->equals(NEW(BoolVal)(false)) );
        CHECK((((parse_str("_if 1 == 2 _then 5 _else 6"))->interp())->to_string()) == "6");
        CHECK((parse_str("1 + 2 == 3 + 0"))->interp()->to_string() == "_true");

    }
}

TEST_CASE("FunExpr") {

    SECTION("Parsing FunExpr"){
        CHECK((parse_str("_let f = _fun (x) x+1"
                         "_in f(10)"))->interp()->to_string() == "11");
    }

    SECTION("Parsing FunExpr"){
        CHECK((parse_str("_let f = _fun (x) x+1"
                         "_in f(10)"))->interp()->to_string() == "11");
        CHECK((parse_str("_let f = _fun (x) x*x"
                         "_in f(2)"))->interp()->to_string() == "4");
        CHECK((parse_str("_let y = 8"
                         "_in _let f = _fun (x) x*y"
                         "_in f(2)"))->interp()->to_string() == "16");
        CHECK((parse_str("_let x = 8"
                         "_in _let f = _fun (x) x*x"
                         "_in f(2)"))->interp()->to_string() == "4");
        CHECK((parse_str("_let factrl = _fun (factrl)"
                         "_fun (x)"
                         "_if x ==1"
                         "_then 1"
                         "_else x * factrl(factrl)(x + -1)"
                         "_in factrl(factrl)(10)"))->interp()->to_string() == "3628800");
    }
    SECTION("Parsing CallExpr"){
        CHECK((parse_str("(_fun (x) x+1 (10))"))->interp()->to_string() == "11");
        CHECK((parse_str("(_fun (x) x+x (1))"))->interp()->to_string() == "2");
    }
}




