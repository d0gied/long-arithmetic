#include <long_arithmetic.h>

const size_t DIVISION_CHUNKS = 1000;

namespace bignum {

const BigNumber BigNumber::_divide(const BigNumber& other) const {
    if (other._is_zero()) {
        throw std::invalid_argument("Division by zero");
    }
    if (_is_zero()) {
        return BigNumber("0");
    }
    if (other == BigNumber("1")) {
        return *this;
    }
    if (other == *this) {
        return BigNumber("1");
    }

    BigNumber a = *this;
    BigNumber b = other;
    a._is_negative = false;
    b._is_negative = false;

    size_t a_chunks = a._size();
    size_t b_chunks = b._size();
    int32_t a_exp = a._exponent;
    int32_t b_exp = b._exponent;
    int32_t a_max_exp = a_exp + a_chunks - 1;
    int32_t b_max_exp = b_exp + b_chunks - 1;

    b._exponent += a_max_exp - b_max_exp;
    std::vector<chunk_t> result_chunks(0);
    result_chunks.reserve(DIVISION_CHUNKS);
    int32_t current_exp = a_max_exp;
    size_t i = 0;
    mul_chunk_t carry = 0;
    const mul_chunk_t b0 = b._chunks[0];
    int32_t integer_chunks = a_max_exp - b_max_exp + 1;
    while (i++ < integer_chunks + DIVISION_CHUNKS && !a._is_zero()) {
        carry *= CHUNK_BASE;
        carry += a._get_chunk(current_exp);
        if (carry < b0) {
            result_chunks.push_back(0);
        } else {
            chunk_t c = carry / b0;
            BigNumber c_bn(c);
            BigNumber b_c = b * c_bn;
            while (b_c > a) {
                --c;
                b_c = b_c - b;
            }
            result_chunks.push_back(c);
            a = a - b_c;
            carry = a._get_chunk(current_exp);
        }
        b._exponent--;
        current_exp--;
    }

    int32_t result_exp = integer_chunks - result_chunks.size();
    chunk_t* result_chunks_reversed = new chunk_t[result_chunks.size()];
    for (size_t i = 0; i < result_chunks.size(); ++i) {
        result_chunks_reversed[i] = result_chunks[result_chunks.size() - i - 1];
    }
    BigNumber result = BigNumber(result_chunks_reversed, result_chunks.size());
    result._exponent = result_exp;
    result._is_negative = _is_negative != other._is_negative;
    return result;
}

}  // namespace bignum
