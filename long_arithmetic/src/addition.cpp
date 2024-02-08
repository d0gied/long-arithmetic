#include <long_arithmetic.h>

namespace bignum {
const BigNumber BigNumber::_add(const BigNumber& other) const {
    if (_is_negative != other._is_negative) {
        return _subtract(other.negate());
    }

    const BigNumber& a = *this;
    const BigNumber& b = other;

    BigNumber result;
    result._is_negative = _is_negative;

    const size_t& a_frac_chunks = (a._fractional_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;
    const size_t& b_frac_chunks = (b._fractional_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;
    const size_t& c_frac_chunks = std::max(a_frac_chunks, b_frac_chunks);

    const size_t& a_int_chunks = a._chunks.size() - a_frac_chunks;
    const size_t& b_int_chunks = b._chunks.size() - b_frac_chunks;
    const size_t& c_int_chunks = std::max(a_int_chunks, b_int_chunks) + 1;  // +1 for the carry

    const size_t& a_chunk_offset = c_frac_chunks - a_frac_chunks;  // 0 if a_frac_chunks >= c_frac_chunks
    const size_t& b_chunk_offset = c_frac_chunks - b_frac_chunks;  // 0 if b_frac_chunks >= c_frac_chunks

    result._chunks.resize(c_int_chunks + c_frac_chunks);

    chunk_t carry = 0;

    for (size_t i = 0; i < c_int_chunks + c_frac_chunks; ++i) {
        chunk_t a_chunk = 0;
        chunk_t b_chunk = 0;

        if (i >= a_chunk_offset && i < a_chunk_offset + a._chunks.size()) {
            a_chunk = a._chunks[i - a_chunk_offset];
        }
        if (i >= b_chunk_offset && i < b_chunk_offset + b._chunks.size()) {
            b_chunk = b._chunks[i - b_chunk_offset];
        }

        chunk_t sum = a_chunk + b_chunk + carry;
        if (sum >= CHUNK_BASE) {  // faster than sum / CHUNK_BASE
            sum -= CHUNK_BASE;
            carry = 1;
        } else {
            carry = 0;
        }

        result._chunks[i] = sum;
    }

    result._remove_leading_zeros();

    if (result._is_negative && result.is_zero()) {
        result._is_negative = false;
    }

    return result;
}
}  // namespace bignum
