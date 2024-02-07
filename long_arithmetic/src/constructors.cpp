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
        size_t start = number_copy.size() - i;
        if (start + has_sign < CHUNK_DIGITS) {
            start = has_sign;
        } else {
            start -= CHUNK_DIGITS;
        }

        size_t end = number_copy.size() - i;

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

BigNumber::BigNumber(const BigNumber &other) : chunks(other.chunks), fractional_size(other.fractional_size), is_negative(other.is_negative) {}

void BigNumber::remove_leading_zeros() {
    while (chunks.size() > 1 && chunks.back() == 0) {
        chunks.pop_back();
    }
}
}  // namespace bignum