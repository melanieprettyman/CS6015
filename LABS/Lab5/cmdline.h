//
// Created by Melanie Prettyman on 1/11/24.
//

#ifndef MSDSCRIPT_CMDLINE_H
#define MSDSCRIPT_CMDLINE_H


typedef enum {

    do_tests, // = 0
    do_help, // = 1
    do_interp, // = 2
    do_print, // = 3
    do_pretty_print, // = 4

} run_mode_t;

run_mode_t use_arguments(int argc, char** argv);

#endif //MSDSCRIPT_CMDLINE_H
