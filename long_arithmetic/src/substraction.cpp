#include <long_arithmetic.h>

namespace bignum {
const BigNumber BigNumber::_subtract(const BigNumber& other) const {
    if (is_negative != other.is_negative) {
        return _add(other.negate());
    }

    const BigNumber& a = *this;
    const BigNumber& b = other;

    if (a.abs() < b.abs()) {
        return b._subtract(a).negate();
    }

    BigNumber result;
    result.is_negative = is_negative;

    const size_t& a_frac_chunks = (a.fractional_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;
    const size_t& b_frac_chunks = (b.fractional_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;
    const size_t& c_frac_chunks = std::max(a_frac_chunks, b_frac_chunks);

    const size_t& a_int_chunks = a.chunks.size() - a_frac_chunks;
    const size_t& b_int_chunks = b.chunks.size() - b_frac_chunks;
    const size_t& c_int_chunks = std::max(a_int_chunks, b_int_chunks) + 1;  // +1 for the carry

    const size_t& a_chunk_offset = c_frac_chunks - a_frac_chunks;  // 0 if a_frac_chunks >= c_frac_chunks
    const size_t& b_chunk_offset = c_frac_chunks - b_frac_chunks;  // 0 if b_frac_chunks >= c_frac_chunks

    result.chunks.resize(c_int_chunks + c_frac_chunks);

    chunk_t carry = 0;

    for (size_t i = 0; i < c_int_chunks + c_frac_chunks; ++i) {
        chunk_t a_chunk = 0;
        chunk_t b_chunk = 0;

        if (i >= a_chunk_offset && i < a_chunk_offset + a.chunks.size()) {
            a_chunk = a.chunks[i - a_chunk_offset];
        }
        if (i >= b_chunk_offset && i < b_chunk_offset + b.chunks.size()) {
            b_chunk = b.chunks[i - b_chunk_offset];
        }

        if (a_chunk < b_chunk + carry) {
            result.chunks[i] = a_chunk + CHUNK_BASE - b_chunk - carry;
            carry = 1;
        } else {
            result.chunks[i] = a_chunk - b_chunk - carry;
            carry = 0;
        }
    }

    result.remove_leading_zeros();

    if (result.is_negative && result.is_zero()) {
        result.is_negative = false;
    }

    return result;
}
}  // namespace bignum
