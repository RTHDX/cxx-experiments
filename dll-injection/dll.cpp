#include <iostream>

#include "dll.hpp"

void foo() {
    std::cout << "DLL::FOO" << std::endl;
}

void bar() {
    std::cout << "DLL::BAR" << std::endl;
}
