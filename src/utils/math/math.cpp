#include "math.h"
#include "qdebug.h"
#include "qlogging.h"

#include <math.h>

#include <stack>
#include <bits/stdc++.h>

#include "src/utils/json.hpp"

Math::Math() {}

double Math::factorial(double n) {
    if (n == 0) {
        return 0;
    }

    double ans = 1;
    for (int i = 1; i <= n; i++) {
        ans *= i;
    }
    return ans;
}

double Math::pow(double a, double b) {
    if (b == 0) {
        return 1;
    }

    if (b == 1) {
        return a;
    }

    if (b == -1) {
        return 1 / a;
    }

    if (b < 0) {
        return 1 / pow(a, -b);
    }

    double result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

double Math::sqrt(double n) {
    double ans = 0;
    double low = 0;
    double high = n;
    double mid = 0;
    double epsilon = 0.00001;

    while (high - low > epsilon) {
        mid = (low + high) / 2;
        if (mid * mid < n) {
            low = mid;
        } else {
            high = mid;
        }
    }

    ans = (
        (low + high) / 2
    );

    return ans;
}

double Math::cbrt(double n) {
    double ans = 0;

    if (n < 0) {
        ans = -cbrt(-n);
    } else {
        double low = 0;
        double high = n;
        double mid = 0;
        double epsilon = 0.00001;

        while (high - low > epsilon) {
            mid = (low + high) / 2;
            if (mid * mid * mid < n) {
                low = mid;
            } else {
                high = mid;
            }
        }

        ans = (
            (low + high) / 2
        );
    }

    return ans;
}

double Math::root(double base, double n) {
    double ans = 0;

    if (n == 0) {
        return 1;
    }

    if (n == 1) {
        return base;
    }

    if (n < 0) {
        return 1 / root(base, -n);
    }

    double low = 0;
    double high = base;
    double mid = 0;
    double epsilon = 0.00001;

    while (high - low > epsilon) {
        mid = (low + high) / 2;
        if (pow(mid, n) < base) {
            low = mid;
        } else {
            high = mid;
        }
    }

    ans = (
        (low + high) / 2
    );

    return ans;
}

bool Math::isLetterOrDigit(std::string c) {
    if (isalnum(c[0])) {
        return true;
    } else {
        return false;
    }
}

int Math::getPrecedence(std::string operation) {
    if (operation == "^") {
        return 3;
    } else  if (operation == "/" || operation == "*") {
        return 2;
    } else if (operation == "+" || operation == "-") {
        return 1;
    } else {
        return -1;
    }
}

bool Math::hasLeftAssociativity(std::string c) {
    if (c == "+" || c == "-" || c == "/" || c == "*") {
        return true;
    } else {
        return false;
    }
}

int Math::evaluateFunction(nlohmann::json input, int x) {
    // Create an initially empty string
    std::vector<std::string> output;
    std::vector<std::string> function = input["equation"];

    // Replace all occurrences of 'x' with the value of x
    // But if 'x' is following a number, we will multiply them
    // for (int i = 0; i < input.size(); i++) {
    //     if (input[i] == 'x') {
    //         if (i > 0 && isdigit(input[i-1])) {
    //             input[i] = '*';
    //             input.insert(i+1, std::to_string(x));
    //         } else {
    //             input.replace(i, 1, std::to_string(x));
    //         }
    //     }
    // }
    for (int i = 0; i < function.size(); i++) {
        if (function[i] == "x") {
            if (i > 0 && isLetterOrDigit(function[i-1])) {
                function[i] = "*";
                function.insert(function.begin()+i+1, std::to_string(x));
            } else {
                function[i] = std::to_string(x);
            }
        }
    }

    // Place spaces into input string to separate numbers and operators but maintain the numbers
    // such as numbers with more than one digit or numbers with decimal points and negative numbers
    // are treated as a single number and not separated into individual digits
    // for (int i = 0; i < input.size(); i++) {
    //     if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^' || input[i] == '(' || input[i] == ')') {
    //         input.insert(i, " ");
    //         input.insert(i+2, " ");
    //         i += 2;
    //     }
    // }

    // Split the string into tokens using spaces as delimiters
    // This will allow us to parse the string into numbers and operators
    // std::string token;
    // std::stringstream ss(input);

    // while (getline(ss, token, ' ')) {
    //     if (token[0] != ' ' && token[0] != '\0')
    //         function.push_back(token);
    // }

    // We will use a variable to store the result
    std::stack<std::string> stack;


    for (std::string c : function) {
        // If c is a letter or digit append to output
        if (isLetterOrDigit(c)) {
            output.push_back(c);
        }

        else if (c == "(") {
            stack.push(c);
        }

        else if (c == ")") {
            while (!stack.empty() && stack.top() != "(") {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        }

        else {
            while (!stack.empty() && getPrecedence(c) <= getPrecedence(stack.top()) && hasLeftAssociativity(c)) {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(c);
        }

    }

    while (!stack.empty()) {
        if (stack.top() == "(") {
            qDebug() << "Error: Unbalanced parentheses";
        }
        output.push_back(stack.top());
        stack.pop();
    }

    int ans = applyOperations(output);

    return ans;
}

int Math::applyOperations(std::vector<std::string> PE) {
    std::stack<int> stack;

    for (std::string c : PE) {
        if (isLetterOrDigit(c)) {
            stack.push(std::stoi(c));
        } else {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();

            if (c == "+") {
                stack.push(b + a);
            } else if (c == "-") {
                stack.push(b - a);
            } else if (c == "*") {
                stack.push(b * a);
            } else if (c == "/") {
                stack.push(b / a);
            } else if (c == "^") {
                stack.push(pow(b, a));
            }
        }
    }

    return stack.top();
}
