#pragma once

#include <inttypes.h>

#include <cmath>
#include <string>
#include <vector>

#define CHUNK_SIZE 64    // number of bits in a batch
#define CHUNK_DIGITS 16  // 18 digits + 1 for carry

#if CHUNK_SIZE == 64
typedef uint64_t chunk_t;
#elif CHUNK_SIZE == 32
typedef uint32_t chunk_t;
#elif CHUNK_SIZE == 16
typedef uint16_t chunk_t;
#elif CHUNK_SIZE == 8
typedef uint8_t chunk_t;
#else
#error "Invalid CHUNK_SIZE"
#endif

const size_t CHUNK_BASE = static_cast<size_t>(std::pow(10, CHUNK_DIGITS));

namespace bignum {

class BigNumber {
   public:
    BigNumber(const std::string &number);
    BigNumber(const std::string &number, size_t fractional_size);

    BigNumber(const char *number) : BigNumber(std::string(number)) {}
    BigNumber(const char *number, size_t fractional_size) : BigNumber(std::string(number), fractional_size) {}

    BigNumber(const int &other);
    BigNumber(const int &other, size_t fractional_size);

    BigNumber(const long &other);
    BigNumber(const long &other, size_t fractional_size);

    BigNumber(const long long &other);
    BigNumber(const long long &other, size_t fractional_size);

    BigNumber(const float &other);
    BigNumber(const float &other, size_t fractional_size);

    BigNumber(const double &other);
    BigNumber(const double &other, size_t fractional_size);

    BigNumber(const BigNumber &other);

    BigNumber copy() const;

    BigNumber operator+(const BigNumber &other) const;
    BigNumber operator-(const BigNumber &other) const;
    BigNumber operator*(const BigNumber &other) const;
    BigNumber operator/(const BigNumber &other) const;

    bool operator==(const BigNumber &other) const;
    bool operator!=(const BigNumber &other) const;
    bool operator<(const BigNumber &other) const;
    bool operator>(const BigNumber &other) const;
    bool operator<=(const BigNumber &other) const;
    bool operator>=(const BigNumber &other) const;

    BigNumber operator-() const;

    BigNumber negate() const;
    BigNumber abs() const;
    bool is_zero() const;

    std::string to_string() const;

    BigNumber with_fractional_size(size_t fractional_size) const;

   private:
    std::vector<chunk_t> chunks;  // array of digit chunks
    size_t fractional_size;       // number of digits after the decimal point
    bool is_negative;             // true if the number is negative

    void _push_to_chunks(const std::string &number, size_t shift = 0);  // push a string to the chunks array

    BigNumber() : chunks(0, 0), fractional_size(0), is_negative(false){};  // default constructor

    void remove_leading_zeros();

    const BigNumber _add(const BigNumber &other) const;
    const BigNumber _subtract(const BigNumber &other) const;
};
}  // namespace bignum
