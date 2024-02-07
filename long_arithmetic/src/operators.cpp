#include <long_arithmetic.h>

namespace bignum {
bool BigNumber::operator==(const BigNumber& other) const {
    if (is_negative != other.is_negative) {
        return false;
    }
    if (chunks.size() != other.chunks.size()) {
        return false;
    }
    for (size_t i = 0; i < chunks.size(); ++i) {
        if (chunks[i] != other.chunks[i]) {
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

    size_t integer_part1 = a.chunks.size() - a.fractional_size;
    size_t integer_part2 = b.chunks.size() - b.fractional_size;

    if (a.is_negative && !b.is_negative) {
        return true;
    }
    if (!a.is_negative && b.is_negative) {
        return false;
    }

    if (integer_part1 < integer_part2) {
        return !is_negative;
    }

    if (integer_part1 > integer_part2) {
        return is_negative;
    }

    if (a.chunks.size() > b.chunks.size()) {
        b = b.with_fractional_size(a.fractional_size);
    }
    if (a.chunks.size() < b.chunks.size()) {
        a = a.with_fractional_size(b.fractional_size);
    }

    for (size_t i = a.chunks.size(); i > 0; --i) {
        if (a.chunks[i - 1] < b.chunks[i - 1]) {
            return !is_negative;
        }
        if (a.chunks[i - 1] > b.chunks[i - 1]) {
            return is_negative;
        }
    }
    if (a.chunks[0] < b.chunks[0]) {
        return !is_negative;
    }
    if (a.chunks[0] > b.chunks[0]) {
        return is_negative;
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

BigNumber BigNumber::operator-() const {
    return negate();
}

}  // namespace bignum