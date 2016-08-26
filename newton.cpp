#include "common.h"

/*
 * f(x) = x^2 - n
 * f'(x) = 2x
 * x1 = x0 - f(x)/f'(x)
 */
double newton_sqrt(double n)
{
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return n;
    }
    double x0;
    double x1 = 1.0;
    do {
        x0 = x1;
        x1 = x0 / 2.0 + n / (2.0 * x0);
    } while (fabs(x1 - x0) > 1e-7);
    return x1;
}

/*
 * f(x) = x^3 - n
 * f'(x) = 3x^2
 * x1 = x0 - f(x)/f'(x)
 */
double newton_cuberoot(double n)
{
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return n;
    }
    double x0;
    double x1 = 1.0;
    do {
        x0 = x1;
        x1 = x0 * 2.0 / 3.0 + n / (3.0 * x0 * x0);
    } while (fabs(x1 - x0) > 1e-7);
    return x1;
}

/*
 * f(x) = x^m - n
 * f'(x) = mx^(m-1)
 * x1 = x0 - f(x)/f'(x)
 */
double newton_mroot(double n, int m)
{
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return n;
    }
    double x0;
    double x1 = 1.0;
    do {
        x0 = x1;
        double product = 1.0;
        for (int i = 0; i < m - 1; i++) {
            product *= x0;
        }
        x1 = x0 * (m - 1.0) / m + n / (m * product);
    } while (fabs(x1 - x0) > 1e-7);
    return x1;
}