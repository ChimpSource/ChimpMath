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
    // Test the evaluateFunction function
    nlohmann::json json;
    std::ifstream f("data/data.json");
    json = nlohmann::json::parse(f);

    std::vector<std::vector<int>> points = { {1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    std::vector<std::vector<int>> expected = { {-2, -1, 0}, {1, 2, 3} , {-594, -297, 0} };

    for (int i = 0; i < json["graph"]["equations"].size(); i++) {
        for (int j = 0; j < points.size(); j++) {
            int point = points[i][j];
            int expect = expected[i][j];

            TEST_COMPARE(MathLib::evaluateFunction(json["graph"]["equations"][i], point), expect);
        }

    }
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
}
