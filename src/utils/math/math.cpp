#include "math.h"
#include "qdebug.h"
#include "qlogging.h"

#include <stack>
#include <bits/stdc++.h>

Math::Math() {}

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

int Math::evaluateFunction(std::string input, int x) {
    // Create an initially empty string
    std::vector<std::string> output;
    std::vector<std::string> function;

    // Replace all occurrences of 'x' with the value of x
    // But if 'x' is following a number, we will multiply them
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == 'x') {
            if (i > 0 && isdigit(input[i-1])) {
                input[i] = '*';
                input.insert(i+1, std::to_string(x));
            } else {
                input.replace(i, 1, std::to_string(x));
            }
        }
    }

    // Place spaces into input string to separate numbers and operators but maintain the numbers
    // such as numbers with more than one digit or numbers with decimal points and negative numbers
    // are treated as a single number and not separated into individual digits
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^' || input[i] == '(' || input[i] == ')') {
            input.insert(i, " ");
            input.insert(i+2, " ");
            i += 2;
        }
    }

    // Split the string into tokens using spaces as delimiters
    // This will allow us to parse the string into numbers and operators
    std::string token;
    std::stringstream ss(input);

    while (getline(ss, token, ' ')) {
        if (token[0] != ' ' && token[0] != '\0')
            function.push_back(token);
    }

    qDebug() << function;

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
                qDebug() << "here";
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

    qDebug() << output;

    qDebug() << applyOperations(output);

    return applyOperations(output);
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
