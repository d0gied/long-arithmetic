#include <long_arithmetic.h>

namespace bignum {
const BigNumber BigNumber::_add(const BigNumber& other) const {
    if (_is_negative != other._is_negative) {
        return _subtract(other._negate());
    }

    const BigNumber& a = *this;
    const BigNumber& b = other;

    const size_t& a_chunks = a._chunks.size();
    const size_t& b_chunks = b._chunks.size();

    const int32_t& max_exp = std::max(a._exponent + a_chunks, b._exponent + b_chunks);
    const int32_t& min_exp = std::min(a._exponent, b._exponent);

    BigNumber c;
    c._is_negative = _is_negative;
    c._chunks.resize(max_exp - min_exp + 1, 0);  // +1 for carry
    c._exponent = min_exp;

    chunk_t carry = 0;
    for (size_t i = 0; i < c._chunks.size(); ++i) {
        chunk_t a_chunk = a._get_chunk(i + min_exp);
        chunk_t b_chunk = b._get_chunk(i + min_exp);
        chunk_t sum = a_chunk + b_chunk + carry;
        carry = sum / CHUNK_BASE;
        c._set_chunk(i + min_exp, sum % CHUNK_BASE);
    }
    c._strip_zeros();
    return c;
}
}  // namespace bignum
