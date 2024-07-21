#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>

class Test {
public:
    static int totalTests;
    static int passedTests;

    static void compare(const std::string& functionName, int result, int expected) {
        totalTests++;
        if (result == expected) {
            passedTests++;
            std::cout << "\033[32m"; // Set text color to green
            std::cout << "Function \"" << "\033[33m" << functionName << "\033[32m" << "\" Passed: " << result << " == " << expected << std::endl;
            std::cout << "\033[0m"; // Reset text color
        } else {

            std::cout << "\033[31m"; // Set text color to red
            std::cout << "Function \"" << "\033[33m" << functionName << "\033[31m" << "\" Failed: " << result << " != " << expected << std::endl;
            std::cout << "\033[0m"; // Reset text color
        }
    }

    static void printSummary() {
        std::cout << "\nSummary:\n";
        std::cout << "Total tests: " << totalTests << std::endl;
        std::cout << "Passed tests: " << passedTests << std::endl;
        std::cout << "Failed tests: " << (totalTests - passedTests) << std::endl;
        std::cout << "Pass ratio: " << (static_cast<float>(passedTests) / totalTests) * 100 << "%" << std::endl;
    }
};

#endif // TEST_H
