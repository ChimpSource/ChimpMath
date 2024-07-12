#include "unittests.h"
#include "tests/math/testmath.h"
#include <iostream>

UnitTests::UnitTests() {}

void UnitTests::test_main() {}

void UnitTests::test_math() {
    TestMath testMath;
    testMath.initTestCase();
    std::vector<int> passed = testMath.test_all();
    testMath.cleanupTestCase();

    std::cout << "\x1B[33m" << "Passed " << passed[0] << " out of " << passed[1] << " tests" << "\033[0m\t\t" << std::endl;
}
