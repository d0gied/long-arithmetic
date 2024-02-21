#include <long_arithmetic.h>

namespace bignum {

bool operator==(const BigNumber& a, const BigNumber& b) {
    if (a._is_negative != b._is_negative)
        return false;

    const size_t& a_chunks = a._size();
    const size_t& b_chunks = b._size();
    if (a_chunks != b_chunks)
        return false;

    const int32_t& a_exp = a._exponent;
    const int32_t& b_exp = b._exponent;
    if (a_exp != b_exp)
        return false;

    for (size_t i = 0; i < a_chunks; ++i) {
        if (a._chunks[i] != b._chunks[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const BigNumber& a, const BigNumber& b) {
    return !(a == b);
}

bool operator<(const BigNumber& a, const BigNumber& b) {
    if (a._is_negative && !b._is_negative) {
        return true;
    }
    if (!a._is_negative && b._is_negative) {
        return false;
    }

    const size_t& a_chunks = a._size();
    const size_t& b_chunks = b._size();
    const int32_t& a_exp = a._exponent;
    const int32_t& b_exp = b._exponent;
    const int32_t a_max_exp = a_exp + a_chunks;
    const int32_t b_max_exp = b_exp + b_chunks;

    if (a_max_exp < b_max_exp)
        return !a._is_negative;
    if (a_max_exp > b_max_exp)
        return a._is_negative;

    const int32_t& min_exp = std::min(a_exp, b_exp);

    for (int32_t i = a_max_exp; i >= min_exp; --i) {
        chunk_t a_chunk = a._get_chunk(i);
        chunk_t b_chunk = b._get_chunk(i);
        if (a_chunk < b_chunk)
            return !a._is_negative;
        if (a_chunk > b_chunk)
            return a._is_negative;
    }
    return false;  // a == b
}

bool operator>(const BigNumber& a, const BigNumber& b) {
    return b < a;
}

bool operator<=(const BigNumber& a, const BigNumber& b) {
    return a < b || a == b;
}

bool operator>=(const BigNumber& a, const BigNumber& b) {
    return a > b || a == b;
}

const BigNumber operator+(const BigNumber& a, const BigNumber& b) {
    return a._add(b);
}

const BigNumber operator-(const BigNumber& a, const BigNumber& b) {
    return a._subtract(b);
}

const BigNumber operator*(const BigNumber& a, const BigNumber& b) {
    return a._multiply(b);
}

const BigNumber operator/(const BigNumber& a, const BigNumber& b) {
    return a._divide(b);
}

const BigNumber BigNumber::operator-() const {
    return _negate();
}

}  // namespace bignum