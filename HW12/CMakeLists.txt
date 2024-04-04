cmake_minimum_required(VERSION 3.27)
project(HW12)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW12 main.cpp
        cmdline.cpp
        Expr.cpp
        parse.cpp
        Env.cpp
        val.cpp
        tests.cpp)
