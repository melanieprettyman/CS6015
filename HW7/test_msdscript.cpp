//
// Created by Melanie Prettyman on 2/21/24.
//
#include <iostream>
#include "exec.h"
#include "test_msdscript.h"


int main(int argc, char **argv) {
    srand (clock());
    for (int i = 0; i < 10; i++) {
        std::string in = random_expr_string();
    }
    //No comparison program
    if(argc == 2) {
        const char *const interp_argv[] = {argv[1], "--interp"};
        const char *const print_argv[] = {argv[1], "--print"};
        const char *const pp_argv[] = {argv[1], "--pretty_print"};

        for (int i = 0; i < 100; i++) {
            std::string in = random_expr_string();
            ExecResult interp_result = exec_program(2, interp_argv, in);
            ExecResult print_result = exec_program(2, print_argv, in);
            ExecResult pp_result = exec_program(2, pp_argv, in);

            ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);
            if (interp_again_result.out != interp_result.out)
                throw std::runtime_error("different result for printed");
        }
    }
    //Testing with the other programs
    if(argc == 3){
        const char *const interp_MSD_argv[] = {argv[1], "--interp"};
        const char *const interp_tester_argv[] = {argv[2], "--interp"};

        const char *const print_MSD_argv[] = {argv[1], "--print"};
        const char *const print_tester_argv[] = {argv[2], "--print"};

        const char *const pp_MSD_argv[] = {argv[1], "--pretty-print"};
        const char *const pp_tester_argv[] = {argv[2], "--pretty-print"};

        for (int i = 0; i < 100; i++) {
            std::string in = random_expr_string();

            ExecResult interp_MSD_result = exec_program(2, interp_MSD_argv, in);
            ExecResult interp_tester_result = exec_program(2, interp_tester_argv, in);

            ExecResult print_MSD_result = exec_program(2, print_MSD_argv, in);
            ExecResult print_tester_result = exec_program(2, print_tester_argv, in);

            ExecResult pp_MSD_result = exec_program(2, pp_MSD_argv, in);
            ExecResult pp_tester_result = exec_program(2, pp_tester_argv, in);


            if(interp_MSD_result.out != interp_tester_result.out){
                std::cout << "msdScript INTERP results: " << interp_MSD_result.out;
                std::cout << "tester INTERP results: " << interp_tester_result.out  << "\n" << "\n";
            }

            if(print_MSD_result.out != print_tester_result.out){
                std::cout << "msdScript PRINT results: " << print_MSD_result.out;
                std::cout << "tester INTERP results: " << print_tester_result.out  << "\n" << "\n";
            }

            if(pp_MSD_result.out != pp_tester_result.out){
                std::cout << "msdScript PRETTY-PRINT results: " << pp_MSD_result.out;
                std::cout << "tester PRETTY-PRINT results: " << pp_tester_result.out  << "\n" << "\n";
            }

        }
    }
    return 0;
}

std::string rand_var(){
    std::string s = "";
    for (int i = 0; i < rand()%6;i++ ){
        s+=rand() % 26 + 'a';
    }
    return s;
}

std::string random_let_body(std::string lhs) {
    int random = rand() % 100;
    switch (random) {
        case 0 ... 33:
            return lhs + "+" + random_expr_string();
        case 34 ... 66:
            return lhs + "*" + random_expr_string();
        case 67 ... 90:
            return random_expr_string() + "+" + lhs;
        case 91 ... 100:
            return random_expr_string() + "*" + lhs;
    }
}

std::string random_expr_string() {
    if ((rand() % 10) < 6)
        return std::to_string(rand());
    else {
        int random = rand() % 100;
        switch (random) {
            case 0 ... 20:
                return "(" + random_expr_string() + ")";
            case 21 ... 32:
                return random_expr_string() + " + " + random_expr_string();
            case 33 ... 45:
                return random_expr_string() + " * " + random_expr_string();
            case 46 ... 65:
                return rand_var();
            case 66 ... 76:
                return (" _let " + rand_var() + " = " + random_expr_string() + " _in " + random_let_body(random_expr_string()));
            case 77 ... 87:
                return "-" + std::to_string(rand());
            default:
                return random_expr_string();
        }
    }
}