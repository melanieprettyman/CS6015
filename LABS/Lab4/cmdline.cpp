#include "cmdline.h"
#include <string>
#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include "Expr.h"
#include "tests.h"

/**
* \file cmdline.cpp
* \brief contains command-line class
*
*
When running a program from the command line, you can provide arguments to the program. These arguments are passed to the program as argc and argv[] parameters in the main function.
 * \author Melanie Prettyman
 */

// Created by Melanie Prettyman on 1/11/24.
/**
* \brief Executes commands on the command-line for the program
* \param int argc represents the number of arguments passed to the program
* \param char **argv is an array of strings containing the actual arguments. The first argument, argv[0], always represents the name of the program itself.
* \return Returns void. Executes command in terminal.
*/

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






