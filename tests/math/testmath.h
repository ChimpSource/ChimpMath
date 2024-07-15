#ifndef TESTMATH_H
#define TESTMATH_H

#include <vector>
class TestMath
{
public:
    TestMath();

    void initTestCase();
    void cleanupTestCase();
    std::vector<int> test_all();

    bool test_addition();
    bool test_subtraction();
    bool test_evaluateFunction();
    bool test_powersAndRoots();
    bool test_trig();
};

#endif // TESTMATH_H
