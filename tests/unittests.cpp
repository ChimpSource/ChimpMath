#include "unittests.h"

#include "tests/TestLib/testmacros.h"

#include "src/utils/math/mathlib.h"
#include "tests/math/testmath.h"

UnitTests::UnitTests() {}

void UnitTests::test_main() {}

void UnitTests::test_math() {
    TEST_COMPARE(MathLib::factorial(5), 120);

    TestMath testMath;
    testMath.test_all();

    TEST_PRINT_SUMMARY();
}
