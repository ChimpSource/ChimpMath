#ifndef TESTMACROS_H
#define TESTMACROS_H

#include "test.h"

#define TEST_COMPARE(func, expected) \
    Test::compare(#func, func, expected)

#define TEST_PRINT_SUMMARY() \
    Test::printSummary()

#endif // TESTMACROS_H
