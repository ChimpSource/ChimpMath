#include "mathlib.h"
#include "qdebug.h"
#include "qlogging.h"

#include <math.h>

#include <stack>
#include <bits/stdc++.h>

#include "src/utils/json.hpp"

MathLib::MathLib() {}

double MathLib::factorial(double n) {
    if (n == 0) {
        return 0;
    }

    double ans = 1;
    for (int i = 1; i <= n; i++) {
        ans *= i;
    }
    return ans;
}

double MathLib::pow(double a, double b) {
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

double MathLib::sqrt(double n) {

    double error = 0.00001;
    double s = n;

    while ((s - n / s) > error) {
        s = (s + n / s) / 2;
    }

    return s;
}

double MathLib::cbrt(double n) {
    double error = 0.00001;
    double x = n;

    while (abs(x - n / (x * x)) > error) {
        x = (1.0 / 3) * ((2 * x) + (n / (x * x)));
    }

    return x;
}

double MathLib::root(double base, double n) {
    double error = 0.00001;
    double x = base;

    while (abs(pow(x, n) - base) > error) {
        x = (1.0 / n) * (((n - 1) * x) + (base / pow(x, n - 1)));
    }

    return x;
}

double MathLib::sinRadians(double x)
{
    // if x is in between -pi and pi no need to fmod
    x = fmodf(x + M_PI, 2.0f * M_PI) - M_PI;
    double xx = x * x * x; // x^3
    double t = x - (xx  / 6.0f); // 6 = !3
    t += (xx *= x * x) / 120.0f; // 120 = !5
    t -= (xx *= x * x) / 5040.0f; // 5040 = !7
    t += (xx * x * x)  / 362880.0f; // 362880 = !9
    return t;
}

double MathLib::cosRadians(double radians) {
    // radians = fmodf(radians + M_PI, 2.0f * M_PI) - M_PI;
    // double xx = radians * radians; // x^2
    // double t = 1.0f - (xx / 2.0f); // 2 = !2
    // qDebug() << t;
    // t += (xx *= radians * radians) / 24.0f; // 24 = !4
    // qDebug() << t;
    // t -= (xx *= radians * radians) / 720.0f; // 720 = !6
    // qDebug() << t;
    // t += (xx *= radians * radians) / 40320.0f; // 40320 = !8
    // qDebug() << t;
    // return t;
    int div = (int)(radians / M_PI);
    radians = radians - (div * M_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = radians * radians;
    for (int i = 1; i <= 6; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

double MathLib::abs(double n) {
    return n < 0 ? -n : n;
}

bool MathLib::isLetterOrDigit(std::string c) {
    if (isalnum(c[0])) {
        return true;
    } else {
        return false;
    }
}

int MathLib::getPrecedence(std::string operation) {
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

bool MathLib::hasLeftAssociativity(std::string c) {
    if (c == "+" || c == "-" || c == "/" || c == "*") {
        return true;
    } else {
        return false;
    }
}

int MathLib::evaluateFunction(nlohmann::json input, int x) {
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

int MathLib::applyOperations(std::vector<std::string> PE) {
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
