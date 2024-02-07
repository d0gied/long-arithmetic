#include <long_arithmetic.h>

namespace bignum {
BigNumber::BigNumber(const std::string &number, size_t fractional_size)
    : chunks(0, 0), fractional_size(fractional_size), is_negative(false) {
    std::string number_copy = number;

    size_t has_sign = 0;
    if (number[0] == '-') {
        is_negative = true;
        has_sign = 1;
    } else if (number[0] == '+') {
        has_sign = 1;
    }

    size_t dot = number.find('.');
    if (dot != std::string::npos) {
        number_copy.erase(dot, 1);
        if (number_copy.size() - dot > fractional_size) {
            number_copy = number_copy.substr(0, dot + fractional_size);
        } else {
            number_copy += std::string(fractional_size - (number_copy.size() - dot), '0');
        }
    } else {
        number_copy += std::string(fractional_size, '0');
    }

    size_t chunks_count = number_copy.size() / CHUNK_DIGITS + (number_copy.size() % CHUNK_DIGITS != 0);
    chunks.reserve(chunks_count);

    // read the number from the end to the start to avoid reversing the string
    for (size_t i = 0; i < number_copy.size() - has_sign; i += CHUNK_DIGITS) {
        size_t start = number_copy.size() - has_sign - i;
        if (start < has_sign + CHUNK_DIGITS) {
            start = has_sign;
        } else {
            start -= CHUNK_DIGITS;
        }

        size_t end = number_copy.size() - has_sign - i;

        chunk_t chunk = std::stoull(number_copy.substr(start, end - start));
        chunks.push_back(chunk);
    }

    remove_leading_zeros();
}

BigNumber::BigNumber(const std::string &number) {
    size_t dot = number.find('.');
    if (dot != std::string::npos) {
        fractional_size = number.size() - dot - 1;
    } else {
        fractional_size = 0;
    }
    *this = BigNumber(number, fractional_size);
}

std::string BigNumber::to_string() const {
    std::string number;
    number += std::to_string(chunks.back());
    for (size_t i = chunks.size() - 1; i > 0; --i) {
        std::string chunk_str = std::to_string(chunks[i - 1]);
        number += std::string(CHUNK_DIGITS - chunk_str.size(), '0') + chunk_str;
    }
    if (fractional_size == 0) {
        return number;
    }
    if (fractional_size + 1 > number.size()) {  // +1 for the leading zero before the dot
        number = std::string(fractional_size - number.size() + 1, '0') + number;
    }
    number.insert(number.size() - fractional_size, ".");

    if (is_negative) {
        number.insert(0, "-");
    }
    return number;
}

void BigNumber::remove_leading_zeros() {
    while (chunks.size() > 1 && chunks.back() == 0) {
        chunks.pop_back();
    }
}

}  // namespace bignum