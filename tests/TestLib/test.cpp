#include "test.h"
#include <iostream>

int passed = 0;

Test::Test() {
    std::cout << "Test constructor" << std::endl;

    std::cout << "Passed " << passed << " tests" << std::endl;
}

Test::~Test() {
    std::cout << "Test destructor" << std::endl;

    std::cout << "Passed " << passed << " tests" << std::endl;
}

bool Test::compare(int a, int b) {
    std::cout << "Comparing " << a << " and " << b << std::endl;
    bool result = a == b;
    std::cout << (result ? "\x1B[32m" : "\x1B[31m") << "Test " << (result ? "passed\033[0m\t\t" : "failed\033[0m\t\t") << std::endl;

    if (result) {
        passed++;
    }

    return result;
}
