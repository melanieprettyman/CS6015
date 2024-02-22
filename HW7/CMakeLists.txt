cmake_minimum_required(VERSION 3.27)
project(HW7)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW7 main.cpp
        cmdline.cpp
        Expr.cpp
        parse.cpp
        tests.cpp
        exec.cpp
        test_msdscript.cpp
        test_msdscript.h)
