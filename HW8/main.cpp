#include <iostream>
#include "cmdline.h"
#include "Expr.h"
#include "parse.hpp"
#define CATCH_CONFIG_RUNNER
#include "catch.h"

int main(int argc, char **argv) {

        run_mode_t runType = use_arguments(argc, argv);

        //If input is --test, run tests
        if (runType == do_tests) {
            int result = Catch::Session().run(1, argv);
            if (result != 0) {
                exit(1);
            }
        }
        //If input is --help, print out flag menu
        if (runType == do_help) {
            std::cout << "Choose from the following flags:" << '\n';
            std::cout << "--test | --interp | --print | --pretty-print" << std::endl;
            exit(0);
        }
        try {
            //Parse input
            Expr *e = parse(std::cin);

            //If mode is interp, pass the parsed input to the interp and output the value
            if (runType == do_interp) {
                Val* value = e->interp();
                std::cout << value << "\n";
                exit(0);

            }
            //If mode is print, pass the parsed input to the "to_string" function and output the value
            else if (runType == do_print) {
                std::cout << e->to_string() << std::endl;
                exit(0);
            }
            //If mode is pretty print, pass the parsed input to the "to_string" pretty print function and output the value
            else if (runType == do_pretty_print) {
                std::cout << e->to_pp_string() << std::endl;
                exit(0);
            }
        }
        //Catch invalid inputs
        catch (const std::runtime_error& exn) {
            std::cerr << "Error: " << exn.what() << std::endl;

            return 1;
        }
    return 0;
}
