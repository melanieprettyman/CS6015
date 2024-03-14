#include <iostream>
#include "cmdline.h"
#define CATCH_CONFIG_RUNNER
#include "catch.h"


// Created by Melanie Prettyman on 1/11/24.

run_mode_t use_arguments(int argc, char** argv) {

    bool testFlag = false;
    run_mode_t mode;

    for (int i = 1; i < argc; i++) {

        std::string argument = argv[i];

        //--help
        if (argument.compare("--help") == 0) {
            std::cout << "Choose from the following flags:" << '\n';
            std::cout << "--test | --interp | --print | --pretty-print" << std::endl;
            exit(0);
        }

        //--test
        if (argument.compare("--test") == 0) {
            if (!testFlag) {
                if (Catch::Session().run(1, argv) != 0) {
                    exit(1);
                }
                testFlag = true;
            } else {
                std::cerr << "Error: --tests have already ran\n";
                exit(1);
            }
        }

        //--interp
        if (argument.compare("--interp") == 0) {
            mode = do_interp;
        }

        //--print
        if (argument.compare("--print") == 0) {
            mode = do_print;
        }

        if (argument.compare("--pretty_print") == 0) {
            mode = do_pretty_print;
        }

        return mode;
    }
}






