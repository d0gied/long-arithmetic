#pragma once

#include <inttypes.h>

#include <cmath>
#include <string>
#include <vector>

#define CHUNK_SIZE 64   // number of bits in a batch
#define CHUNK_DIGITS 9  // number of decimal digits in a batch

#if CHUNK_SIZE == 128
typedef __uint128_t chunk_t;
#elif CHUNK_SIZE == 64
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
const chunk_t MAX_CHUNK = CHUNK_BASE - 1;

namespace bignum {
class BigNumber {
   public:
    BigNumber(const std::string &number);
    BigNumber(const char *number) : BigNumber(std::string(number)) {}
    BigNumber(const int &other);
    BigNumber(const long &other);
    BigNumber(const long long &other);
    BigNumber(const float &other);
    BigNumber(const double &other);

    friend const BigNumber operator""_bn(const char *number);
    friend const BigNumber operator""_bn(const char *number, size_t size);

    // BigNumber(const BigNumber &other);

    friend bool operator==(const BigNumber &a, const BigNumber &b);
    friend bool operator!=(const BigNumber &a, const BigNumber &b);
    friend bool operator<(const BigNumber &a, const BigNumber &b);
    friend bool operator>(const BigNumber &a, const BigNumber &b);
    friend bool operator<=(const BigNumber &a, const BigNumber &b);
    friend bool operator>=(const BigNumber &a, const BigNumber &b);

    friend const BigNumber operator+(const BigNumber &a, const BigNumber &b);
    friend const BigNumber operator-(const BigNumber &a, const BigNumber &b);
    friend const BigNumber operator*(const BigNumber &a, const BigNumber &b);
    friend const BigNumber operator/(const BigNumber &a, const BigNumber &b);

    const BigNumber operator-() const;

    std::string to_string() const;

    const BigNumber with_fractional_size(size_t fractional_size) const;

   private:
    std::vector<chunk_t> _chunks;  // array of digit chunks
    int32_t _exponent;             // exponent of the number
    bool _is_negative;             // true if the number is negative

    BigNumber() : _chunks(0, 0), _exponent(0), _is_negative(false){};                          // default constructor
    BigNumber(const chunk_t &chunk) : _chunks(1, chunk), _exponent(0), _is_negative(false){};  // constructor for a single chunk

    const chunk_t _get_chunk(const int32_t &exponent) const;         // get the chunk at the given exponent
    void _set_chunk(const int32_t &exponent, const chunk_t &value);  // set the chunk at the given exponent
    void _pad_left(size_t count);                                    // pad the number with zeros on the left

    void _strip_zeros();
    bool _is_zero() const;

    const BigNumber _negate() const;
    const BigNumber _abs() const;

    const BigNumber _add(const BigNumber &other) const;
    const BigNumber _subtract(const BigNumber &other) const;
    const BigNumber _multiply(const BigNumber &other) const;
    const BigNumber _divide(const BigNumber &other) const;

    const BigNumber _shift(int32_t shift) const;

    const chunk_t _chunk_divide(const BigNumber &a, const BigNumber &b, size_t shift) const;
    const bool _is_less(const BigNumber &a, const BigNumber &b, size_t shift) const;

    const size_t _int_chunks_count() const;
    const size_t _frac_chunks_count() const;
};

}  // namespace bignum
