#include <iostream>
#include "namespace.hpp"

int msd::maxFunc(int a, int b) {
    std::cout<<"inside msd work space"<<std::endl;
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

int other_space::maxFunc(int a, int b) {
    std::cout<<"inside msd other_space"<<std::endl;
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
