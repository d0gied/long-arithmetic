#include <long_arithmetic.h>

namespace bignum {

bool BigNumber::operator==(const BigNumber& other) const {
    if (_is_negative != other._is_negative) {
        return false;
    }
    if (_chunks.size() != other._chunks.size()) {
        return false;
    }
    for (size_t i = 0; i < _chunks.size(); ++i) {
        if (_chunks[i] != other._chunks[i]) {
            return false;
        }
    }
    return true;
}

bool BigNumber::operator!=(const BigNumber& other) const {
    return !(*this == other);
}

bool BigNumber::operator<(const BigNumber& other) const {
    BigNumber a = *this;
    BigNumber b = other;

    size_t integer_part1 = a._chunks.size() - a._fractional_size;
    size_t integer_part2 = b._chunks.size() - b._fractional_size;

    if (a._is_negative && !b._is_negative) {
        return true;
    }
    if (!a._is_negative && b._is_negative) {
        return false;
    }

    if (integer_part1 < integer_part2) {
        return !_is_negative;
    }

    if (integer_part1 > integer_part2) {
        return _is_negative;
    }

    if (a._chunks.size() > b._chunks.size()) {
        b = b.with_fractional_size(a._fractional_size);
    }
    if (a._chunks.size() < b._chunks.size()) {
        a = a.with_fractional_size(b._fractional_size);
    }

    for (size_t i = a._chunks.size(); i > 0; --i) {
        if (a._chunks[i - 1] < b._chunks[i - 1]) {
            return !_is_negative;
        }
        if (a._chunks[i - 1] > b._chunks[i - 1]) {
            return _is_negative;
        }
    }
    if (a._chunks[0] < b._chunks[0]) {
        return !_is_negative;
    }
    if (a._chunks[0] > b._chunks[0]) {
        return _is_negative;
    }
    return false;  // equal
}

bool BigNumber::operator>(const BigNumber& other) const {
    return !(*this < other || *this == other);
}

bool BigNumber::operator<=(const BigNumber& other) const {
    return *this < other || *this == other;
}

bool BigNumber::operator>=(const BigNumber& other) const {
    return *this > other || *this == other;
}

const BigNumber BigNumber::operator-() const {
    return negate();
}

const BigNumber operator+(const BigNumber& a, const BigNumber& b) {
    return a._add(b);
}

const BigNumber operator-(const BigNumber& a, const BigNumber& b) {
    return a._subtract(b);
}

}  // namespace bignum