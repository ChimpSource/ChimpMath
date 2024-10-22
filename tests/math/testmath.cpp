#include "testmath.h"
#include <iostream>
#include <fstream>

#include "src/utils/math/mathlib.h"
#include "tests/TestLib/Testmacros.h"

TestMath::TestMath() {
    std::cout << "TestMath constructor" << std::endl;

    // Initialize variables here

}

void TestMath::initTestCase() {

}

void TestMath::cleanupTestCase() {

}

void TestMath::test_all() {
    TestMath::test_evaluateFunction();
    TestMath::test_powersAndRoots();
    TestMath::test_trig();
}

void TestMath::test_evaluateFunction() {

    const std::vector<std::tuple<std::string, int32_t>> testCases = {
        { "3+4*2/(1-5)^2^3" , 3     },  // Wikipedia's example
        { "(2*3+3*4)"       , 18    },  // Report from @2kaud.
        { "(3)+(4)"         , 7     },  // Report from @kayshav.
        { "(-3)*(-2^3)"     , 24    },  // Unary '-'
    };

    for (const auto& testCase : testCases) {
        const std::string& expr = std::get<0>(testCase);
        const int32_t expected = std::get<1>(testCase);

        const int32_t result = MathLib::compute(expr);


        TEST_COMPARE(result, expected);
    }
    std::string expr = std::string("x+3");
    TEST_COMPARE(MathLib::compute(expr, 3), 3);
}

void TestMath::test_powersAndRoots() {
    // Test the powers and roots functions

    // Test the factorial function
    TEST_COMPARE(MathLib::factorial(5), 120);

    // Test the pow function
    TEST_COMPARE(MathLib::pow(2, 3), 8);

    // Test the sqrt function
    TEST_COMPARE(MathLib::sqrt(4), 2);

    // Test the cbrt function
    TEST_COMPARE(MathLib::cbrt(8), 2);

    // Test the root function
    TEST_COMPARE(MathLib::root(8, 3), 2);
}

void TestMath::test_trig() {
    // Test the trig functions
    TEST_COMPARE(MathLib::sinRadians(2*M_PI), 0);
    TEST_COMPARE(MathLib::sinRadians(M_PI), 0);
    TEST_COMPARE(MathLib::sinRadians(M_PI/2), 1);
    TEST_COMPARE(MathLib::sinRadians(0), 0);

    TEST_COMPARE(MathLib::cosRadians(2*M_PI), 1);
    TEST_COMPARE(MathLib::cosRadians(M_PI), -1);
    TEST_COMPARE(MathLib::cosRadians(M_PI/2), 0);
    TEST_COMPARE(MathLib::cosRadians(0), 1);

}
