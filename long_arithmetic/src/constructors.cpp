#include <long_arithmetic.h>

namespace bignum {

void BigNumber::_push_to_chunks(const std::string &number, size_t shift) {
    size_t length = number.size();
    size_t chunks_count = (length + shift + CHUNK_DIGITS - 1) / CHUNK_DIGITS;
    size_t old_size = _chunks.size();
    _chunks.resize(old_size + chunks_count, 0);  // fill the new chunks with zeros
    old_size += shift / CHUNK_DIGITS;            // add the shift to the old size, to skip ready chunks
    shift %= CHUNK_DIGITS;

    for (size_t i = 0; i < length; i += CHUNK_DIGITS) {
        size_t chunk_start = length - i;
        if (chunk_start + shift < CHUNK_DIGITS) {
            chunk_start = 0;
        } else {
            chunk_start -= CHUNK_DIGITS - shift;
        }
        size_t chunk_end = length - i + shift;
        chunk_t chunk = std::stoull(number.substr(chunk_start, chunk_end - chunk_start));
        if (i == 0)
            chunk *= pow(10, shift);
        _chunks[old_size + i / CHUNK_DIGITS] = chunk;
    }
}

BigNumber::BigNumber(const std::string &number, size_t fractional_size)
    : _chunks(0, 0), _fractional_size(fractional_size), _is_negative(false) {
    size_t dot = number.find('.');
    size_t shift = 0;
    if (dot != std::string::npos) {
        // if the dot is found, push the floating part to the chunks
        shift = fractional_size - (number.size() - dot - 1);                      // amount of zeros to add to the end
        shift += (CHUNK_DIGITS - fractional_size % CHUNK_DIGITS) % CHUNK_DIGITS;  // align the shift to the chunk size
        _push_to_chunks(number.substr(dot + 1), shift);
        shift = 0;
    } else {
        shift = fractional_size + (CHUNK_DIGITS - fractional_size % CHUNK_DIGITS) % CHUNK_DIGITS;  // align the shift to the chunk size
    }

    size_t integer_size = dot != std::string::npos ? dot : number.size();  // amount of digits in the integer part
    if (number[0] == '-') {
        _is_negative = true;
        integer_size--;
        _push_to_chunks(number.substr(1, integer_size), shift);
    } else {
        _push_to_chunks(number.substr(0, integer_size), shift);
    }
    _remove_leading_zeros();
    if (is_zero()) {
        _is_negative = false;  // zero is always positive
    }
}

BigNumber::BigNumber(const std::string &number) : _fractional_size(0) {
    size_t dot = number.find('.');
    if (dot != std::string::npos)
        _fractional_size = number.size() - dot - 1;

    *this = BigNumber(number, _fractional_size);
}

BigNumber::BigNumber(const int &other) : BigNumber(std::to_string(other)) {}
BigNumber::BigNumber(const long &other) : BigNumber(std::to_string(other)) {}
BigNumber::BigNumber(const long long &other) : BigNumber(std::to_string(other)) {}
BigNumber::BigNumber(const float &other) : BigNumber(std::to_string(other)) {}
BigNumber::BigNumber(const double &other) : BigNumber(std::to_string(other)) {}

BigNumber::BigNumber(const int &other, size_t fractional_size) : BigNumber(std::to_string(other), fractional_size) {}
BigNumber::BigNumber(const long &other, size_t fractional_size) : BigNumber(std::to_string(other), fractional_size) {}
BigNumber::BigNumber(const long long &other, size_t fractional_size) : BigNumber(std::to_string(other), fractional_size) {}
BigNumber::BigNumber(const float &other, size_t fractional_size) : BigNumber(std::to_string(other), fractional_size) {}
BigNumber::BigNumber(const double &other, size_t fractional_size) : BigNumber(std::to_string(other), fractional_size) {}

// BigNumber::BigNumber(const BigNumber &other) : chunks(other.chunks), fractional_size(other.fractional_size), is_negative(other.is_negative) {}

void BigNumber::_remove_leading_zeros() {
    while (_chunks.size() > 1 && _chunks.back() == 0) {
        _chunks.pop_back();
    }
}
}  // namespace bignum