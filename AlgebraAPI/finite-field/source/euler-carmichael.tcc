#include <vector>

#include "mod-num.tcc"

namespace modular {
#ifndef EULER_CARMICAEL
#define EULER_CARMICAEL
template <typename T, typename floating = double>
floating
EulerFunction(T n) {
    if (n <= 0)
        throw std::logic_error("Euler totient function is not defiend on non Natural values");
    floating res = static_cast<floating>(n);
    floating one(1.0);

    for (T p = 2; p * p <= n; p += 1) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res *= (one - (one / static_cast<floating>(p)));
        }
    }

    if (n > 1)
        res -= res / static_cast<floating>(n);
    return res;
}

template <typename T, typename floating = double>
modNum<T>
eulerFunction(modNum<T> num) {
    return modNum<T>(static_cast<T>(EulerFunction(num.getValue())), num.getMod());
}

int
gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

template <typename T>
modNum<T>
CarmichaelFunction(modNum<T> num) {
    T n = num.getValue();
    if (n <= 0)
        throw std::logic_error("Carmichael function is not defiend on non Natural values");

    if (n == 1)
        return 1;

    std::vector<T> factors;
    for (T i = 2; i * i <= n; i += 2) {
        T w = 0;
        while (n % i == 0) {
            w++;
            n /= i;
        }
        if (i == 2 && w >= 3)
            factors.push_back((pow(i, w - 1) * (i - 1)) / 2);
        else if (i >= 2 && w > 0)
            factors.push_back(pow(i, w - 1) * (i - 1));
        if (i == 2)
            i--;
    }
    if (n != 1)
        factors.push_back(n - 1);

    T res = 1;
    for (auto i : factors) res *= i / gcd(res, i);
    return res;
}

#endif
}   // namespace modular