#include <long_arithmetic.h>

namespace bignum {
const BigNumber BigNumber::_add(const BigNumber& other) const {
    if (_is_negative != other._is_negative) {
        return _subtract(other._negate());
    }

    const BigNumber& a = *this;
    const BigNumber& b = other;

    const size_t& a_chunks = a._size();
    const size_t& b_chunks = b._size();

    const int32_t& max_exp = std::max(a._exponent + a_chunks, b._exponent + b_chunks);
    const int32_t& min_exp = std::min(a._exponent, b._exponent);

    BigNumber c;
    c._is_negative = _is_negative;
    size_t c_size = max_exp - min_exp + 1;
    c._chunks = new chunk_t[c_size]{0};
    c._chunks_size = c_size;
    c._exponent = min_exp;

    chunk_t carry = 0;
    for (size_t i = 0; i < c_size; ++i) {
        chunk_t a_chunk = a._get_chunk(i + min_exp);
        chunk_t b_chunk = b._get_chunk(i + min_exp);
        chunk_t sum = a_chunk + b_chunk + carry;
        carry = sum / CHUNK_BASE;
        c._chunks[i] = sum % CHUNK_BASE;
    }
    c._strip_zeros();
    return c;
}
}  // namespace bignum
