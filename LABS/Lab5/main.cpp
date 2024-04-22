#include <iostream>
#include "cmdline.h"
#include "Expr.h"
#include "parse.hpp"
#define CATCH_CONFIG_RUNNER
#include "catch.h"

int main(int argc, char **argv) {

        run_mode_t runType = use_arguments(argc, argv);

        if (runType == do_tests) {
            int result = Catch::Session().run(1, argv);
            if (result != 0) {
                exit(1);
            }
        }
        if (runType == do_help) {
            std::cout << "Choose from the following flags:" << '\n';
            std::cout << "--test | --interp | --print | --pretty-print" << std::endl;
            exit(0);
        }
        try {
            Expr *e = parse(std::cin);

            if (runType == do_interp) {
                int value = e->interp();
                std::cout << value << "\n";
                exit(0);

            } else if (runType == do_print) {
                std::cout << e->to_string() << std::endl;
                exit(0);
            } else if (runType == do_pretty_print) {
                std::cout << e->to_pp_string() << std::endl;
                exit(0);
            }
        }
        catch (const std::runtime_error& exn) {
            std::cerr << "Error: " << exn.what() << std::endl;
            return 1;
        }
    return 0;
}
