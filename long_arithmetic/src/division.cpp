#include <long_arithmetic.h>

namespace bignum {
static size_t _DIV_PRECISION = 50;
void SET_DIV_PRECISION(size_t precision) {
    _DIV_PRECISION = precision / CHUNK_DIGITS + (precision % CHUNK_DIGITS != 0);
}

const BigNumber BigNumber::_divide(const BigNumber& other) const {
    if (other._is_zero()) {
        throw std::invalid_argument("Division by zero");
    }
    if (_is_zero()) {
        return BigNumber("0");
    }
    if (*this == "1"_bn) {
        printf("1\n");
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

    int32_t a_chunks = a._size();
    int32_t b_chunks = b._size();
    int32_t a_exp = a._exponent;
    int32_t b_exp = b._exponent;
    int32_t a_max_exp = a_exp + a_chunks - 1;
    int32_t b_max_exp = b_exp + b_chunks - 1;

    b._exponent += a_max_exp - b_max_exp;
    std::vector<chunk_t> result_chunks(0);
    int32_t div_precision = _DIV_PRECISION;
    result_chunks.reserve(div_precision);
    int32_t current_exp = a_max_exp;
    int32_t i = 0;
    mul_chunk_t carry = 0;
    const mul_chunk_t b0 = b._chunks[b._size() - 1];
    int32_t integer_chunks = std::max(a_max_exp - b_max_exp + 1, 0);
    while (i++ < integer_chunks + div_precision && !a._is_zero()) {
        carry *= CHUNK_BASE;
        carry += a._get_chunk(current_exp);
        if (carry < b0) {
            result_chunks.push_back(0);
        } else {
            chunk_t c = carry / b0;
            BigNumber c_bn(c);
            BigNumber b_c = b * c_bn;
            int32_t steps = 0;
            while (steps++ < 3 && b_c > a) {
                --c;
                b_c = b_c - b;
            }

            if (b_c > a) {
                chunk_t left = 0;
                chunk_t right = c;
                size_t start = clock();
                while (left < right) {
                    c = (left + right) / 2;
                    c_bn = BigNumber(c);
                    b_c = b * c_bn;
                    if (b_c > a) {
                        right = c;
                    } else {
                        left = c + 1;
                    }
                }
                c = left - 1;
                c_bn = BigNumber(c);
                b_c = b * c_bn;
            }

            a = a - b_c;
            result_chunks.push_back(c);
            carry = a._get_chunk(current_exp);
        }
        b._exponent--;
        current_exp--;
    }

    int32_t result_exp = a_max_exp - b_max_exp + 1 - result_chunks.size();
    chunk_t* result_chunks_reversed = new chunk_t[result_chunks.size()];
    for (size_t i = 0; i < result_chunks.size(); ++i) {
        result_chunks_reversed[i] = result_chunks[result_chunks.size() - i - 1];
    }
    BigNumber result = BigNumber(result_chunks_reversed, result_chunks.size());
    result._exponent = result_exp;
    result._is_negative = _is_negative != other._is_negative;
    return result;
}

const chunk_t _chunk_div(mul_chunk_t carry, mul_chunk_t next, mul_chunk_t divisor, chunk_t& remainder) {
    mul_chunk_t dividend = carry * CHUNK_BASE + next;
    mul_chunk_t quotient = dividend / divisor;
    remainder = dividend % divisor;
    return quotient;
}

}  // namespace bignum
