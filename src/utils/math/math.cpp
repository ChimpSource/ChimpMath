#include "math.h"

#include <stack>

Math::Math() {}

int Math::evaluateFunction(std::string function, int x) {
    // We will use a stack to store the numbers and the operations
    std::stack<double> numbers;
    std::stack<char> operations;

    // We will use a variable to store the number we are reading
    double number = 0;
    // We will use a variable to store the sign of the number
    int sign = 1;
    // We will use a variable to store the exponent
    int exponent = 0;
    // We will use a variable to store the decimal part
    double decimal = 0;
    // We will use a variable to store the decimal exponent
    int decimal_exponent = 0;

    // We will iterate over the function
    for (int i = 0; i < function.size(); i++) {
        char c = function[i];
        if (c == ' ') {
            continue;
        }

        if (c == '(') {
            // We push the number and the operation to the stacks
            numbers.push(number);
        }
    }

    return 0;
}
