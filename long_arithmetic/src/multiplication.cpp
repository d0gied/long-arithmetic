#include <long_arithmetic.h>

namespace bignum {
const BigNumber BigNumber::_multiply(const BigNumber& other) const {
    if (_is_zero() || other._is_zero()) {
        return "0";
    }

    const BigNumber& a = *this;
    const BigNumber& b = other;

    BigNumber c;
    c._is_negative = _is_negative != other._is_negative;
    c._exponent = _exponent + other._exponent;
    c._chunks.resize(_chunks.size() + other._chunks.size(), 0);

    chunk_t carry = 0;
    for (int32_t i = 0; i < _chunks.size(); ++i) {
        carry = 0;
        for (int32_t j = 0; j < other._chunks.size(); ++j) {
            chunk_t a_chunk = _chunks[i];
            chunk_t b_chunk = other._chunks[j];
            chunk_t product = a_chunk * b_chunk + c._chunks[i + j] + carry;
            carry = product / CHUNK_BASE;
            c._chunks[i + j] = product % CHUNK_BASE;
        }
        c._chunks[i + other._chunks.size()] = carry;
    }
    c._strip_zeros();
    return c;
}
}  // namespace bignum