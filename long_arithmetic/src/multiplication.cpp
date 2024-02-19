#include <long_arithmetic.h>

#define MULTIPLY_THRESHOLD 42

namespace bignum {
BigNumber::BigNumber(chunk_t* chunks, size_t chunks_size)
    : _chunks(chunks),
      _chunks_size(chunks_size),
      _is_negative(false),
      _exponent(0) {
    size_t new_size = chunks_size;
    while (*chunks == 0 && new_size > 0) {
        ++chunks;
        --new_size;
        _exponent++;
    }
    while (new_size > 0 && chunks[new_size - 1] == 0) {
        --new_size;
    }
    _chunks = chunks;
    _chunks_size = new_size;
}

const BigNumber BigNumber::_multiply(const BigNumber& other) const {
    if (_is_zero() || other._is_zero()) {
        return "0";
    }
    const BigNumber& a = *this;
    const BigNumber& b = other;

    const size_t& a_chunks = a._size();
    const size_t& b_chunks = b._size();

    const size_t& n = std::max(a_chunks, b_chunks);

    if (n <= MULTIPLY_THRESHOLD) {
        return _multiply_simple(other);
    }

    const size_t& m = n / 2;

    BigNumber a0_bn(a._chunks + m, a_chunks - m);
    BigNumber a1_bn(a._chunks, m);
    BigNumber b0_bn(b._chunks + m, b_chunks - m);
    BigNumber b1_bn(b._chunks, m);

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
    const size_t& a_chunks = a._size();
    const size_t& b_chunks = b._size();

    BigNumber c;
    c._is_negative = _is_negative != other._is_negative;
    c._exponent = _exponent + other._exponent;
    c._chunks_size = a_chunks + b_chunks;
    c._chunks = new chunk_t[c._chunks_size]{0};

    chunk_t carry = 0;
    for (int32_t i = 0; i < a_chunks; ++i) {
        carry = 0;
        for (int32_t j = 0; j < b_chunks; ++j) {
            chunk_t a_chunk = _chunks[i];
            chunk_t b_chunk = other._chunks[j];
            chunk_t product = a_chunk * b_chunk + c._chunks[i + j] + carry;
            carry = product / CHUNK_BASE;
            c._chunks[i + j] = product % CHUNK_BASE;
        }
        c._chunks[i + b_chunks] = carry;
    }
    c._strip_zeros();
    return c;
}

}  // namespace bignum