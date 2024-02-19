#include <long_arithmetic.h>

namespace bignum {
std::string BigNumber::to_string() const {
    if (_is_zero())
        return "0";

    std::string number;
    if (_is_negative) {
        number.push_back('-');
    }

    const size_t& chunks = _chunks.size();
    const int32_t& exp = _exponent;
    const int32_t& max_exp = std::max(exp + static_cast<int32_t>(chunks) - 1, 0);
    const int32_t& min_exp = std::min(exp, 0);

    for (int32_t i = max_exp; i >= min_exp; --i) {
        if (i == -1) {
            number += '.';
        }
        std::string chunk = std::to_string(_get_chunk(i));
        if (i != max_exp)
            chunk = std::string(CHUNK_DIGITS - chunk.size(), '0') + chunk;
        number += chunk;
    }

    if (min_exp < 0) {
        size_t suff_zeros = 0;
        for (size_t i = number.size() - 1; i > 0; --i) {
            if (number[i] == '0') {
                ++suff_zeros;
            } else {
                break;
            }
        }
        number.erase(number.size() - suff_zeros, suff_zeros);
    }

    return number;
}
}  // namespace bignum