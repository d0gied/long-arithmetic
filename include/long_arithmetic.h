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

    BigNumber(const int64_t &other);
    BigNumber(const int64_t &other, size_t fractional_size);
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

    BigNumber abs() const;

    std::string to_string() const;

    BigNumber with_fractional_size(size_t fractional_size) const;

   private:
    std::vector<chunk_t> chunks;  // array of digit chunks
    size_t fractional_size;       // number of digits after the decimal point
    bool is_negative;             // true if the number is negative

    void remove_leading_zeros();
};
}  // namespace bignum
