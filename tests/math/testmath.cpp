#include "testmath.h"
#include "tests/TestLib/test.h"
#include <iostream>
#include <fstream>

#include "src/utils/math/math.h"

TestMath::TestMath() {
    std::cout << "TestMath constructor" << std::endl;

    // Initialize variables here

}

std::vector<int> TestMath::test_all() {
    std::cout << "Running all math tests" << std::endl;

    int passed = 0;
    // For all tests in this class, call the test function
    test_addition() ? passed++ : 0;
    test_subtraction() ? passed++ : 0;
    test_evaluateFunction() ? passed++ : 0;

    return {passed, 3};
}

void TestMath::initTestCase() {

}

void TestMath::cleanupTestCase() {

}

bool TestMath::test_addition() {
    std::cout << "Testing addition" << std::endl;
    int a = 1;
    int b = 2;
    return Test::compare(a+b, 3);
}

bool TestMath::test_subtraction() {
    std::cout << "Testing subtraction" << std::endl;
    return Test::compare(3-2, 1);
}

bool TestMath::test_evaluateFunction() {
    std::cout << "Testing evaluateFunction" << std::endl;
    int passed = 0;
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
            int result = Math::evaluateFunction(json["graph"]["equations"][i], point);

            if (result == expect) {
                passed++;
            } else {
                std::cout << "Test failed" << std::endl;
            }
        }

    }


    return passed == 9;
}
