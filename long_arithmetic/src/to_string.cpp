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

    for (size_t i = _chunks.size(); i > 1; --i) {  // process last chunk separately
        std::string chunk = std::to_string(_chunks[i - 1]);
        if (i != _chunks.size()) {
            chunk = std::string(CHUNK_DIGITS - chunk.size(), '0') + chunk;
        }
        if (i == fractional_chunks) {
            number += '.';  // add the dot before the first fractional chunk
        }
        number += chunk;
    }
    if (fractional_chunks == 1) {
        number += '.';  // add the dot if there are no fractional chunks
    }
    std::string chunk = std::to_string(_chunks[0]);
    if (_chunks.size() > 1)
        chunk = std::string(CHUNK_DIGITS - chunk.size(), '0') + chunk;
    number += chunk.substr(0, last_chunk_size);  // add only the necessary part of the last chunk
    return number;
}
}  // namespace bignum