#include <long_arithmetic.h>

namespace bignum {
const BigNumber BigNumber::_multiply(const BigNumber& other) const {
    if (is_zero() || other.is_zero()) {
        return BigNumber("0");
    }

    BigNumber result;
    result._is_negative = _is_negative != other._is_negative;

    const BigNumber& a = *this;
    const BigNumber& b = other;

    const size_t& a_chunks = a._chunks.size();
    const size_t& b_chunks = b._chunks.size();

    const size_t& a_frac_size = a._fractional_size;
    const size_t& b_frac_size = b._fractional_size;

    const size_t& a_frac_chunks = (a_frac_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;
    const size_t& b_frac_chunks = (b_frac_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;

    result._chunks.resize(a_chunks + b_chunks, 0);
    result._fractional_size = a_frac_size + b_frac_size;

    const size_t& result_frac_chunks = (result._fractional_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;
    const size_t& diff_frac_chunks = a_frac_chunks + b_frac_chunks - result_frac_chunks;

    for (size_t i = 0; i < a_chunks; ++i) {
        chunk_t carry = 0;
        for (size_t j = 0; j < b_chunks; ++j) {
            chunk_t product = a._chunks[i] * b._chunks[j] + result._chunks[i + j] + carry;
            result._chunks[i + j] = product % CHUNK_BASE;
            carry = product / CHUNK_BASE;
        }
        result._chunks[i + b_chunks] = carry;
    }

    result._chunks = std::vector<chunk_t>(result._chunks.begin() + diff_frac_chunks, result._chunks.end());
    result._remove_leading_zeros();

    return result;
}

}  // namespace bignum