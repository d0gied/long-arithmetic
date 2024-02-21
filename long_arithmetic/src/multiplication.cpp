#include <long_arithmetic.h>

#define MULTIPLY_THRESHOLD 42

namespace bignum {

const BigNumber BigNumber::_multiply(const BigNumber& other) const {
    if (_is_zero() || other._is_zero()) {
        return "0";
    }
    const BigNumber& a = *this;
    const BigNumber& b = other;

    size_t a_chunks = a._size();
    size_t b_chunks = b._size();

    size_t n = std::max(a_chunks, b_chunks);

    if (a_chunks <= MULTIPLY_THRESHOLD || b_chunks <= MULTIPLY_THRESHOLD) {
        return _multiply_simple(other);
    }

    size_t m = n / 2;
    BigNumber a0_bn, a1_bn, b0_bn, b1_bn;

    if (m >= a_chunks) {
        a0_bn = "0"_bn;
        a1_bn = a;
    } else {
        a0_bn = BigNumber(a._chunks.begin() + m, a._chunks.end());
        a1_bn = BigNumber(a._chunks.begin(), a._chunks.begin() + m);
    }
    if (m >= b_chunks) {
        b0_bn = "0"_bn;
        b1_bn = a;
    } else {
        b0_bn = BigNumber(b._chunks.begin() + m, b._chunks.end());
        b1_bn = BigNumber(b._chunks.begin(), b._chunks.begin() + m);
    }

    BigNumber z0 = a0_bn._multiply(b0_bn);
    BigNumber z1 = (a0_bn + a1_bn)._multiply(b0_bn + b1_bn);
    BigNumber z2 = a1_bn._multiply(b1_bn);

    BigNumber z0_shifted = z0._shift(2 * m);
    BigNumber z1_shifted = (z1 - z0 - z2)._shift(m);

    BigNumber result = z0_shifted + z1_shifted + z2;
    result._is_negative = _is_negative != other._is_negative;
    result._exponent = _exponent + other._exponent;
    result._strip_zeros();
    return result;
}

const BigNumber BigNumber::_multiply_simple(const BigNumber& other) const {
    if (_is_zero() || other._is_zero()) {
        return "0";
    }

    const BigNumber& a = *this;
    const BigNumber& b = other;
    const size_t a_chunks = a._size();
    const size_t b_chunks = b._size();

    BigNumber c;
    c._is_negative = _is_negative != other._is_negative;
    c._exponent = _exponent + other._exponent;
    c._chunks.resize(a_chunks + b_chunks, 0);

    chunk_t carry = 0;
    for (int32_t i = 0; i < a_chunks; ++i) {
        carry = 0;
        for (int32_t j = 0; j < b_chunks; ++j) {
            mul_chunk_t a_chunk = (mul_chunk_t)_chunks[i];
            mul_chunk_t b_chunk = (mul_chunk_t)other._chunks[j];
            mul_chunk_t product = a_chunk * b_chunk + c._chunks[i + j] + carry;
            carry = product / CHUNK_BASE;
            c._chunks[i + j] = product % CHUNK_BASE;
        }
        c._chunks[i + b_chunks] = carry;
    }
    c._strip_zeros();
    return c;
}

}  // namespace bignum