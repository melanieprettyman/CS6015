#include "cmdline.h"
#include <string>
#include <iostream>
#include "Expr.h"
#include "tests.h"


// Created by Melanie Prettyman on 1/11/24.

run_mode_t use_arguments(int argc, char** argv){
    //Bool testSeen set to false
    bool testSeen = false;

    //extract argument from argV
    for (int i = 1; i < argc; i++) {
        std::string argument = argv[i];

        //If argument is --help, print help menu and exit
        if (argument.compare("--help") == 0) {
            return do_help;

        }
        //If argument is --test and test has not been seen
        //print 'test passed' and set testSeen to true
        else if (argument.compare("--test") == 0) {
            if (!testSeen) {
                testSeen = true;
                return do_tests;
            }
        }
        else if (argument == "--interp") {
            return do_interp;
        } else if (argument == "--print") {
            return do_print;
        } else if (argument == "--pretty-print") {
            return do_pretty_print;
        } else {
            std::cerr << "Unknown argument: " << argument << std::endl;
            exit(1);
        }
    }

}






