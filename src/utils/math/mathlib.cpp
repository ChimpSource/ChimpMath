#include "mathlib.h"
#include "qdebug.h"
#include "qlogging.h"

#include <math.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <tuple>
#include <stdio.h>
#include <math.h>
#include <cstdint>


#include "src/utils/json.hpp"

static const char* reportFmt = "|%-5s|%-32s|%17s| %s\n";

class Token {
public:
    enum class Type {
        Unknown,
        Number,
        Operator,
        LeftParen,
        RightParen,
    };

    Token(Type type,
          const std::string& s,
          int precedence = -1,
          bool rightAssociative = false,
          bool unary = false
          )
        : type { type }
        , str ( s )
        , precedence { precedence }
        , rightAssociative { rightAssociative }
        , unary { unary }
    {}

    const Type type;
    const std::string str;
    const int precedence;
    const bool rightAssociative;
    const bool unary;
};


std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.str;
    return os;
}

// Debug output
template<class T, class U>
void debugReport(
    const Token& token
    , const T& queue
    , const U& stack
    , const std::string& comment = ""
    ) {
    std::ostringstream ossQueue;
    for(const auto& t : queue) {
        ossQueue << " " << t;
    }

    std::ostringstream ossStack;
    for(const auto& t : stack) {
        ossStack << " " << t;
    }

    printf(reportFmt
           , token.str.c_str()
           , ossQueue.str().c_str()
           , ossStack.str().c_str()
           , comment.c_str()
           );
}

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

std::deque<Token> exprToTokens(const std::string& expr) {
    std::deque<Token> tokens;

    for(const auto* p = expr.c_str(); *p; ++p) {
        if(isblank(*p)) {
            // do nothing
        } else if(isdigit(*p)) {
            const auto* b = p;
            while(isdigit(*p)) {
                ++p;
            }
            const auto s = std::string(b, p);
            tokens.push_back(Token { Token::Type::Number, s });
            --p;
        } else {
            Token::Type t = Token::Type::Unknown;
            int precedence = -1;
            bool rightAssociative = false;
            bool unary = false;
            char c = *p;
            switch(c) {
            default:                                    break;
            case '(':   t = Token::Type::LeftParen;     break;
            case ')':   t = Token::Type::RightParen;    break;
            case '^':   t = Token::Type::Operator;      precedence = 4; rightAssociative = true;  break;
            case '*':   t = Token::Type::Operator;      precedence = 3; break;
            case '/':   t = Token::Type::Operator;      precedence = 3; break;
            case '+':   t = Token::Type::Operator;      precedence = 2; break;
            case '-':
                // If current token is '-'
                // and if it is the first token, or preceded by another operator, or left-paren,
                if(   tokens.empty()
                    || tokens.back().type == Token::Type::Operator
                    || tokens.back().type == Token::Type::LeftParen
                    ) {
                    // it's unary '-'
                    // note#1 : 'm' is a special operator name for unary '-'
                    // note#2 : It has highest precedence than any of the infix operators
                    unary = true;
                    c = 'm';
                    t = Token::Type::Operator;
                    precedence = 5;
                } else {
                    // otherwise, it's binary '-'
                    t = Token::Type::Operator;
                    precedence = 2;
                }
                break;
            }
            const auto s = std::string(1, c);
            tokens.push_back(Token { t, s, precedence, rightAssociative, unary });
        }
    }

    return tokens;
}


std::deque<Token> shuntingYard(const std::deque<Token>& tokens) {
    std::deque<Token> queue;
    std::vector<Token> stack;

    // While there are tokens to be read:
    for(auto token : tokens) {
        // Read a token
        switch(token.type) {
        case Token::Type::Number:
            // If the token is a number, then add it to the output queue
            queue.push_back(token);
            break;

        case Token::Type::Operator:
        {
            // If the token is operator, o1, then:
            const auto o1 = token;

            // while there is an operator token,
            while(!stack.empty()) {
                // o2, at the top of stack, and
                const auto o2 = stack.back();

                // either o1 is left-associative and its precedence is
                // *less than or equal* to that of o2,
                // or o1 if right associative, and has precedence
                // *less than* that of o2,
                if(
                    (! o1.rightAssociative && o1.precedence <= o2.precedence)
                    ||  (  o1.rightAssociative && o1.precedence <  o2.precedence)
                    ) {
                    // then pop o2 off the stack,
                    stack.pop_back();
                    // onto the output queue;
                    queue.push_back(o2);

                    continue;
                }

                // @@ otherwise, exit.
                break;
            }

            // push o1 onto the stack.
            stack.push_back(o1);
        }
        break;

        case Token::Type::LeftParen:
            // If token is left parenthesis, then push it onto the stack
            stack.push_back(token);
            break;

        case Token::Type::RightParen:
            // If token is right parenthesis:
            {
                bool match = false;

                // Until the token at the top of the stack
                // is a left parenthesis,
                while(! stack.empty() && stack.back().type != Token::Type::LeftParen) {
                    // pop operators off the stack
                    // onto the output queue.
                    queue.push_back(stack.back());
                    stack.pop_back();
                    match = true;
                }

                if(!match && stack.empty()) {
                    // If the stack runs out without finding a left parenthesis,
                    // then there are mismatched parentheses.
                    printf("RightParen error (%s)\n", token.str.c_str());
                    return {};
                }

                // Pop the left parenthesis from the stack,
                // but not onto the output queue.
                stack.pop_back();
            }
            break;

        default:
            printf("error (%s)\n", token.str.c_str());
            return {};
        }

        debugReport(token, queue, stack);
    }

    // When there are no more tokens to read:
    //   While there are still operator tokens in the stack:
    while(! stack.empty()) {
        // If the operator token on the top of the stack is a parenthesis,
        // then there are mismatched parentheses.
        if(stack.back().type == Token::Type::LeftParen) {
            printf("Mismatched parentheses error\n");
            return {};
        }

        // Pop the operator onto the output queue.
        queue.push_back(std::move(stack.back()));
        stack.pop_back();
    }

    debugReport(Token { Token::Type::Unknown, "End" }, queue, stack);

    //Exit.
    return queue;
}

void replaceVariable(std::string& expr, int num) {
    for (int i = 0; i < expr.size(); i++) {
        if (expr[i] == 'x') {
            expr = expr.substr(0, i) + '(' + std::to_string(num) + ')' + expr.substr(i + 2);
            i += 3;
        }
    }
    std::cout << expr << std::endl;
}
int32_t MathLib::compute(const std::string& expr) {
    printf("Tokenize\n");
    printf(reportFmt, "Token", "Queue", "Stack", "");

    const auto tokens = exprToTokens(expr);
    auto queue = shuntingYard(tokens);
    std::vector<int> stack;

    printf("\nCalculation\n");
    printf(reportFmt, "Token", "Queue", "Stack", "");

    while(! queue.empty()) {
        std::string op;

        const auto token = queue.front();
        queue.pop_front();
        switch(token.type) {
        case Token::Type::Number:
            stack.push_back(std::stoi(token.str));
            op = "Push " + token.str;
            break;

        case Token::Type::Operator:
        {
            if(token.unary) {
                // unray operators
                const auto rhs = stack.back();
                stack.pop_back();
                switch(token.str[0]) {
                default:
                    printf("Operator error [%s]\n", token.str.c_str());
                    exit(0);
                    break;
                case 'm':                   // Special operator name for unary '-'
                    stack.push_back(-rhs);
                    break;
                }
                op = "Push (unary) " + token.str + " " + std::to_string(rhs);
            } else {
                // binary operators
                const auto rhs = stack.back();
                stack.pop_back();
                const auto lhs = stack.back();
                stack.pop_back();

                switch(token.str[0]) {
                default:
                    printf("Operator error [%s]\n", token.str.c_str());
                    exit(0);
                    break;
                case '^':
                    stack.push_back(static_cast<int>(pow(lhs, rhs)));
                    break;
                case '*':
                    stack.push_back(lhs * rhs);
                    break;
                case '/':
                    stack.push_back(lhs / rhs);
                    break;
                case '+':
                    stack.push_back(lhs + rhs);
                    break;
                case '-':
                    stack.push_back(lhs - rhs);
                    break;
                }
                op = "Push " + std::to_string(lhs) + " " + token.str + " " + std::to_string(rhs);
            }
        }
        break;

        default:
            printf("Token error\n");
            exit(0);
        }
        debugReport(token, queue, stack, op);
    }

    return stack.back();
}


int32_t MathLib::compute(std::string& expr, int i) {
    printf("Tokenize\n");
    printf(reportFmt, "Token", "Queue", "Stack", "");

    replaceVariable(expr, i);

    const auto tokens = exprToTokens(expr);
    auto queue = shuntingYard(tokens);
    std::vector<int> stack;

    printf("\nCalculation\n");
    printf(reportFmt, "Token", "Queue", "Stack", "");

    while(! queue.empty()) {
        std::string op;

        const auto token = queue.front();
        queue.pop_front();
        switch(token.type) {
        case Token::Type::Number:
            stack.push_back(std::stoi(token.str));
            op = "Push " + token.str;
            break;

        case Token::Type::Operator:
        {
            if(token.unary) {
                // unray operators
                const auto rhs = stack.back();
                stack.pop_back();
                switch(token.str[0]) {
                default:
                    printf("Operator error [%s]\n", token.str.c_str());
                    exit(0);
                    break;
                case 'm':                   // Special operator name for unary '-'
                    stack.push_back(-rhs);
                    break;
                }
                op = "Push (unary) " + token.str + " " + std::to_string(rhs);
            } else {
                // binary operators
                const auto rhs = stack.back();
                stack.pop_back();
                const auto lhs = stack.back();
                stack.pop_back();

                switch(token.str[0]) {
                default:
                    printf("Operator error [%s]\n", token.str.c_str());
                    exit(0);
                    break;
                case '^':
                    stack.push_back(static_cast<int>(pow(lhs, rhs)));
                    break;
                case '*':
                    stack.push_back(lhs * rhs);
                    break;
                case '/':
                    stack.push_back(lhs / rhs);
                    break;
                case '+':
                    stack.push_back(lhs + rhs);
                    break;
                case '-':
                    stack.push_back(lhs - rhs);
                    break;
                }
                op = "Push " + std::to_string(lhs) + " " + token.str + " " + std::to_string(rhs);
            }
        }
        break;

        default:
            printf("Token error\n");
            exit(0);
        }
        debugReport(token, queue, stack, op);
    }

    return stack.back();
}
