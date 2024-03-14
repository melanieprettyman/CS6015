#include <iostream>
#include "cmdline.h"
#include "parse.hpp"
int main(int argc, char **argv) {

    try {
        run_mode_t mode = use_arguments(argc, argv);
        Expr *e;

        switch(mode){
            case do_nothing:
                break;
            case do_print:
                e = parse(std::cin);
                std::cout << e->to_string() << "\n";
                break;
            case do_interp:
                e = parse(std::cin);
                std::cout << e->interp() << "\n" ;
                break;
            case do_pretty_print:
                e = parse(std::cin);
                std::cout << e->to_pp_string() << "\n";
                break;
        }

    }
    catch (std::runtime_error exn) {
        std::cerr << exn.what() << "\n";
        return 1;
    }
    return 0;
}
