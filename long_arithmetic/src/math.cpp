#include <long_arithmetic.h>

#include <tuple>

namespace bignum {
namespace math {

const Fraction operator""_fr(const char* str, size_t) {
    std::string s(str);
    size_t pos = s.find('/');
    if (pos == std::string::npos) {
        return Fraction(BigNumber(s));
    }
    return Fraction(BigNumber(s.substr(0, pos)), BigNumber(s.substr(pos + 1)));
}

Fraction::Fraction(const BigNumber& numerator, const BigNumber& denominator) : _numerator(numerator), _denominator(denominator) {
    if (_denominator == "0"_bn) {
        // printf(to_string().c_str());
        throw std::invalid_argument("Fraction: division by zero");
    }
}

Fraction::Fraction(const BigNumber& number) : _numerator(number), _denominator("1"_bn) {}

const Fraction operator+(const Fraction& a, const Fraction& b) {
    return Fraction(a._numerator * b._denominator + b._numerator * a._denominator, a._denominator * b._denominator);
}

const Fraction operator-(const Fraction& a, const Fraction& b) {
    return Fraction(a._numerator * b._denominator - b._numerator * a._denominator, a._denominator * b._denominator);
}

const Fraction operator*(const Fraction& a, const Fraction& b) {
    return Fraction(a._numerator * b._numerator, a._denominator * b._denominator);
}

const Fraction operator/(const Fraction& a, const Fraction& b) {
    return Fraction(a._numerator * b._denominator, a._denominator * b._numerator);
}

const Fraction Fraction::operator-() const {
    return Fraction(-_numerator, _denominator);
}

const bool operator==(const Fraction& a, const Fraction& b) {
    return a._numerator * b._denominator == b._numerator * a._denominator;
}

const bool operator!=(const Fraction& a, const Fraction& b) {
    return !(a == b);
}

const bool operator<(const Fraction& a, const Fraction& b) {
    return a._numerator * b._denominator < b._numerator * a._denominator;
}

const bool operator>(const Fraction& a, const Fraction& b) {
    return !(a < b) && a != b;
}

const bool operator<=(const Fraction& a, const Fraction& b) {
    return a < b || a == b;
}

const bool operator>=(const Fraction& a, const Fraction& b) {
    return a > b || a == b;
}

const std::string Fraction::to_string() const {
    return _numerator.to_string() + "/" + _denominator.to_string();
}

const BigNumber Fraction::to_decimal() const {
    return _numerator / _denominator;
}

const bignum::BigNumber sqrt(const bignum::BigNumber& number) {
    if (number < "0"_bn)
        throw std::invalid_argument("sqrt: negative number");

    if (number == "0"_bn || number == "1"_bn)
        return number;

    bignum::BigNumber left = "0"_bn;
    bignum::BigNumber right = number;

    for (int i = 0; i < 1000; i++) {
        bignum::BigNumber mid = (left + right) / "2"_bn;
        bignum::BigNumber mid_squared = mid * mid;
        if (mid_squared > number) {
            right = mid;
        } else if (mid_squared == number) {
            return mid;
        } else {
            left = mid;
        }
    }
    return right;
}

const bignum::BigNumber PiFast(size_t n) {
    Fraction pi = "13591409"_fr;
    Fraction ak = "1"_fr;
    Fraction sqrt_10005(bignum::math::sqrt("10005"_bn));
    for (int32_t k = 1; k < n; k++) {
        BigNumber k_bn(k);
        ak = -ak * Fraction(("6"_bn * k_bn - "5"_bn) * ("2"_bn * k_bn - "1"_bn) * ("6"_bn * k_bn - "1"_bn),
                            (k_bn * k_bn * k_bn * "26680"_bn * "640320"_bn * "640320"_bn));
        Fraction val = ak * ("13591409"_fr + "545140134"_fr * Fraction(k_bn));
        pi = pi + val;
        // if (k % 10 == 0) {
        //     pi = pi.to_decimal();
    }

    pi = pi * sqrt_10005;
    pi = "4270934400"_fr / pi;
    // printf(pi.to_string().c_str());
    // printf("\n");
    return pi.to_decimal();
}

}  // namespace math
}  // namespace bignum