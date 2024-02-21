#include <long_arithmetic.h>

namespace bignum {

void BigNumber::_set_chunk(const int32_t &exponent, const chunk_t &value) {
    int32_t chunk_index = exponent - _exponent;
    _chunks[chunk_index] = value;
}

const chunk_t BigNumber::_get_chunk(const int32_t &exponent) const {
    int32_t chunk_index = exponent - _exponent;
    if (chunk_index < 0 || chunk_index >= _size()) {
        return 0;
    }
    return _chunks[chunk_index];
}

BigNumber::BigNumber(const std::string &number)
    : _chunks(), _exponent(0), _is_negative(false) {
    if (number.empty()) {
        throw std::invalid_argument("Empty string");
    }
    std::string num = number;

    size_t dot = num.find('.');
    if (dot != std::string::npos) {
        size_t frac_size = num.size() - dot - 1;
        _exponent = -(frac_size / CHUNK_DIGITS + (frac_size % CHUNK_DIGITS != 0));  // ceil(frac_size / CHUNK_DIGITS)
        num.erase(dot, 1);
        num += std::string(-_exponent * CHUNK_DIGITS - frac_size, '0');  // pad with zeros
    }

    if (num[0] == '-') {
        _is_negative = true;
        num.erase(0, 1);
    }

    const size_t &chunks_count = num.size() / CHUNK_DIGITS + (num.size() % CHUNK_DIGITS != 0);
    num = std::string(chunks_count * CHUNK_DIGITS - num.size(), '0') + num;

    _chunks.resize(chunks_count);

    for (size_t i = 0; i < chunks_count; i++) {
        size_t start = num.size() - (i + 1) * CHUNK_DIGITS;
        _chunks[i] = std::stoull(num.substr(start, CHUNK_DIGITS));
    }

    _strip_zeros();
}

BigNumber::BigNumber(std::vector<const chunk_t>::iterator begin, std::vector<const chunk_t>::iterator end)
    : _chunks(0, 0),
      _is_negative(false),
      _exponent(0) {
    size_t new_size = end - begin;
    while (new_size > 0 && *begin == 0) {
        ++begin;
        --new_size;
        _exponent++;
    }
    while (new_size > 0 && *(end - 1) == 0) {
        --end;
        new_size--;
    }
    if (new_size > 0) {
        _chunks = std::vector<chunk_t>(begin, end);
    }
}

BigNumber::BigNumber(const int &other) : BigNumber(std::to_string(other)) {}
BigNumber::BigNumber(const long &other) : BigNumber(std::to_string(other)) {}
BigNumber::BigNumber(const long long &other) : BigNumber(std::to_string(other)) {}
BigNumber::BigNumber(const float &other) : BigNumber(std::to_string(other)) {}
BigNumber::BigNumber(const double &other) : BigNumber(std::to_string(other)) {}

const BigNumber operator""_bn(const char *number, size_t size) {
    return BigNumber(std::string(number, size));
}

// BigNumber::BigNumber(const BigNumber &other) : chunks(other.chunks), fractional_size(other.fractional_size), is_negative(other.is_negative) {}

void BigNumber::_strip_zeros() {
    size_t pref_zeros = 0;
    size_t suff_zeros = 0;
    for (size_t i = 0; i < _size(); ++i) {
        if (_chunks[i] == 0) {
            pref_zeros++;
        } else {
            break;
        }
    }
    for (size_t i = _size(); i > 0; --i) {
        if (_chunks[i - 1] == 0) {
            suff_zeros++;
        } else {
            break;
        }
    }

    if (pref_zeros == _size()) {  // if the number is zero
        _exponent = 0;
        _is_negative = false;
        _chunks.clear();
        return;
    }

    _exponent += pref_zeros;
    size_t new_size = _size() - pref_zeros - suff_zeros;
    if (new_size == _size()) {
        return;
    }

    _chunks.erase(_chunks.begin(), _chunks.begin() + pref_zeros);
    _chunks.resize(new_size);
}
}  // namespace bignum