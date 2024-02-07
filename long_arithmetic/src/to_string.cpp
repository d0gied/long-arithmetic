#include <long_arithmetic.h>

namespace bignum {
std::string BigNumber::to_string() const {
    std::string number;
    number += std::to_string(chunks.back());
    for (size_t i = chunks.size() - 1; i > 0; --i) {
        std::string chunk_str = std::to_string(chunks[i - 1]);
        number += std::string(CHUNK_DIGITS - chunk_str.size(), '0') + chunk_str;
    }

    if (fractional_size != 0) {
        if (fractional_size + 1 > number.size()) {  // +1 for the leading zero before the dot
            number = std::string(fractional_size - number.size() + 1, '0') + number;
        }
        number.insert(number.size() - fractional_size, ".");
    }

    if (is_negative) {
        number.insert(0, "-");
    }
    return number;
}
}  // namespace bignum