#include <long_arithmetic.h>

namespace bignum {
std::string BigNumber::to_string() const {
    std::string number;
    size_t fractional_chunks = (_fractional_size + CHUNK_DIGITS - 1) / CHUNK_DIGITS;
    size_t last_chunk_size = _fractional_size % CHUNK_DIGITS;
    if (last_chunk_size == 0) {
        last_chunk_size = CHUNK_DIGITS;
    }

    if (_is_negative) {
        number += '-';
    }

    if (fractional_chunks >= _chunks.size()) {
        number += "0.";
        for (size_t i = 0; i < fractional_chunks - _chunks.size(); ++i) {
            number += std::string(CHUNK_DIGITS, '0');
        }
        for (size_t i = _chunks.size(); i > 0; --i) {
            std::string chunk = std::to_string(_chunks[i - 1]);
            chunk = std::string(CHUNK_DIGITS - chunk.size(), '0') + chunk;
            if (i == 1)
                number += chunk.substr(0, last_chunk_size);
            else
                number += chunk;
        }
    } else {
        for (size_t i = _chunks.size(); i > 0; --i) {
            std::string chunk = std::to_string(_chunks[i - 1]);
            if (i != _chunks.size()) {
                chunk = std::string(CHUNK_DIGITS - chunk.size(), '0') + chunk;
            }
            if (i == fractional_chunks) {
                number += '.';  // add the dot before the first fractional chunk
            }
            if (i == 1)
                number += chunk.substr(0, last_chunk_size);
            else
                number += chunk;
        }
    }
    return number;
}
}  // namespace bignum