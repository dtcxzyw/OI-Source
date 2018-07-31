#include <cmath>
#include <iostream>
#include <random>
typedef double FT;
namespace Taylor {
constexpr auto maxp = 16384;
FT sin(FT x) {
    FT res = 0.0, base = x, x2 = x * x;
    for (int i = 0; i <= maxp; ++i) {
        res += base;
        base *= -x2 / ((2 * i + 2) * (2 * i + 3));
    }
    return res;
}
FT cos(FT x) {
    FT res = 0.0, base = 1.0, x2 = x * x;
    for (int i = 0; i <= maxp; ++i) {
        res += base;
        base *= -x2 / ((2 * i + 1) * (2 * i + 2));
    }
    return res;
}
FT ln(FT x) {
    if (x <= 2.0) {
        x -= 1.0;
        FT res = 0.0, fac = x;
        for (int i = 1; i <= maxp; ++i) {
            res += fac / i;
            fac *= -x;
        }
        return res;
    }
    return -ln(1.0 / x);
}
FT exp(FT x) {
    FT res = 0.0, base = 1.0;
    for (int i = 0; i <= maxp; ++i) {
        res += base;
        base *= x / (i + 1);
    }
    return res;
}
FT pow(FT a, FT b) {
    return exp(ln(a) * b);
}
}
void output() {
    std::cout << std::endl;
}
template <typename First, typename... T>
void output(First first, T... input) {
    std::cout << first << " ";
    output(input...);
}
template <typename Func, typename... T>
FT compare(const char *name, Func stdf, Func test, FT eps, T... input) {
    FT v1 = stdf(input...);
    FT v2 = test(input...);
    FT absDelta = fabs(v1 - v2);
    FT relDelta = fabs(absDelta / v1);
    if (relDelta > eps || absDelta > eps) {
        std::cout << "Test failed" << std::endl
                  << "Function:" << name << std::endl
                  << "Input" << std::endl;
        output(input...);
        std::cout << "std:" << v1 << " myfunc:" << v2 << std::endl
                  << "absError:" << absDelta << " relError:" << relDelta << std::endl;
        throw;
    }
    return relDelta;
}
int main() {
    std::random_device gen;
    std::uniform_real_distribution<FT> d1(-5.0, 5.0);
    std::uniform_real_distribution<FT> d2(0.1, 5.0);
    constexpr auto testNum = 1024;
    FT relError[5] = {};
    for (int i = 0; i < testNum; ++i)
        relError[0] += compare("sin", sin, Taylor::sin, 1e-4, d1(gen));
    for (int i = 0; i < testNum; ++i)
        relError[1] += compare("cos", cos, Taylor::cos, 1e-4, d1(gen));
    for (int i = 0; i < testNum; ++i)
        relError[2] += compare("ln", log, Taylor::ln, 1e-4, d2(gen));
    for (int i = 0; i < testNum; ++i)
        relError[3] += compare("exp", exp, Taylor::exp, 1e-3, d1(gen));
    for (int i = 0; i < testNum; ++i)
        relError[4] += compare("pow", pow, Taylor::pow, 1e-2, d2(gen), d1(gen));
    for (int i = 0; i < 5; ++i)
        std::cout << "error:" << relError[i] / testNum << std::endl;
    std::cin.get();
    std::cin.get();
    return 0;
}
