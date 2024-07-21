#ifndef TESTMATH_H
#define TESTMATH_H

class TestMath
{
public:
    TestMath();

    void initTestCase();
    void cleanupTestCase();

    void test_all();

    void test_addition();
    void test_subtraction();
    void test_evaluateFunction();
    void test_powersAndRoots();
    void test_trig();
};

#endif // TESTMATH_H
