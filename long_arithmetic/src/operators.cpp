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

    const size_t& a_frac_chunks = (a._fractional_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;
    const size_t& b_frac_chunks = (b._fractional_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;

    const size_t& a_int_chunks = a._chunks.size() >= a_frac_chunks ? a._chunks.size() - a_frac_chunks : 0;
    const size_t& b_int_chunks = b._chunks.size() >= b_frac_chunks ? b._chunks.size() - b_frac_chunks : 0;

    const size_t& max_frac_chunks = std::max(a_frac_chunks, b_frac_chunks);
    const size_t& max_int_chunks = std::max(a_int_chunks, b_int_chunks);

    const size_t& a_chunk_offset = max_frac_chunks - a_frac_chunks;
    const size_t& b_chunk_offset = max_frac_chunks - b_frac_chunks;

    if (a._is_negative && !b._is_negative) {
        return true;
    }
    if (!a._is_negative && b._is_negative) {
        return false;
    }

    if (a_int_chunks < b_int_chunks) {
        return !_is_negative;
    }

    if (a_int_chunks > b_int_chunks) {
        return _is_negative;
    }

    for (size_t i = max_int_chunks + max_frac_chunks; i > 0; --i) {
        chunk_t a_chunk = 0;
        chunk_t b_chunk = 0;

        if (i > a_chunk_offset && i <= a_chunk_offset + a._chunks.size()) {
            a_chunk = a._chunks[i - a_chunk_offset - 1];
        }
        if (i > b_chunk_offset && i <= b_chunk_offset + b._chunks.size()) {
            b_chunk = b._chunks[i - b_chunk_offset - 1];
        }

        if (a_chunk < b_chunk) {
            return !_is_negative;
        }
        if (a_chunk > b_chunk) {
            return _is_negative;
        }
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

const BigNumber operator*(const BigNumber& a, const BigNumber& b) {
    return a._multiply(b);
}

}  // namespace bignum