#ifndef Q1_H
#define Q1_H

#include <cstdlib>
namespace q1{
    double gradient_descent(double init, double step, double (*func)(double));
    double calcuDerive(double value, double (*func)(double));
}

inline double q1::gradient_descent(double init, double step, double (*func)(double))
{
    double curValue = init;
    while (1) {
        if (calcuDerive(curValue, func) < 1e-6) {
            return curValue;
        }
        curValue = curValue + step ;
    }
    return EXIT_FAILURE;
}

inline double q1::calcuDerive(double value, double (*func)(double))
{
    return std::abs((func(value + 1e-4) - func(value)) / 1e-4);
}

#endif //Q1_H