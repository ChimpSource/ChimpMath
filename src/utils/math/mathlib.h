#ifndef MATH_H
#define MATH_H

#include <string>
#include <vector>

#include "src/utils/json.hpp"

class MathLib
{
public:
    MathLib();

    static double factorial(double n);
    static double pow(double base, double exponent); // base^exponent
    static double sqrt(double n);
    static double cbrt(double n);
    static double root(double base, double n);
    static double log(double base, double n);
    static double ln(double n);

    static double sinDegrees(double degrees);
    static double sinRadians(double radians);
    static double cosDegrees(double n);
    static double cosRadians(double n);
    static double tanDegrees(double n);
    static double tanRadians(double n);
    static double asinDegrees(double n);
    static double asinRadians(double n);
    static double acosDegrees(double n);
    static double acosRadians(double n);
    static double atanDegrees(double n);
    static double atanRadians(double n);
    static double sinh(double n);
    static double cosh(double n);
    static double tanh(double n);
    static double asinh(double n);
    static double acosh(double n);
    static double atanh(double n);

    static double degToRad(double n);
    static double radToDeg(double n);

    static double abs(double n);
    static double ceil(double n);
    static double floor(double n);
    static double round(double n);
    static double trunc(double n);
    static double fmod(double n, double d);
    static double modf(double n, double* iptr);
    static double remainder(double n, double d);
    static double copysign(double n, double d);
    static double nextafter(double n, double d);
    static double fdim(double n, double d);
    static double fmax(double n, double d);
    static double fmin(double n, double d);
    static double fma(double n, double d, double e);
    static double frexp(double n, int* exp);
    static double ldexp(double n, int exp);
    static double exp(double n);
    static double exp2(double n);
    static double expm1(double n);
    static double log10(double n);
    static double log1p(double n);
    static double log2(double n);

    static double PI() { return 3.14159265358979323846; };

    static double evaluateFunctionToDouble(std::string function);
    static std::string evaluateFunctionToString(std::string function);
    static int evaluateFunction(nlohmann::json function, int x);
    static double evaluateFunction(std::string function, double x);

    static int32_t compute(const std::string& expr);
    static int32_t compute(std::string& expr, int i);

private:
    static int getPrecedence(std::string operation);
    static bool isLetterOrDigit(std::string c);
    static bool hasLeftAssociativity(std::string c);
    static int applyOperations(std::vector<std::string> PostFix);
};

#endif // MATH_H
