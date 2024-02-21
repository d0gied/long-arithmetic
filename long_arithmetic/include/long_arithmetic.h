#pragma once

#include <inttypes.h>

#include <cmath>
#include <string>
#include <vector>

#define CHUNK_SIZE 64    // number of bits in a batch
#define CHUNK_DIGITS 18  // number of decimal digits in a batch

#if CHUNK_SIZE == 64
typedef __uint128_t mul_chunk_t;
typedef uint64_t chunk_t;
#elif CHUNK_SIZE == 32
typedef uint64_t mul_chunk_t;
typedef uint32_t chunk_t;
#elif CHUNK_SIZE == 16
typedef uint32_t mul_chunk_t;
typedef uint16_t chunk_t;
#elif CHUNK_SIZE == 8
typedef uint16_t mul_chunk_t;
typedef uint8_t chunk_t;
#else
#error "Invalid CHUNK_SIZE"
#endif

const chunk_t CHUNK_BASE = static_cast<chunk_t>(std::pow(10, CHUNK_DIGITS));
const chunk_t MAX_CHUNK = CHUNK_BASE - 1;

namespace bignum {
void SET_DIV_PRECISION(size_t precision);

class BigNumber {
   public:
    BigNumber(const std::string &number);
    BigNumber(const char *number) : BigNumber(std::string(number)) {}
    BigNumber(const int &other);
    BigNumber(const long &other);
    BigNumber(const long long &other);
    BigNumber(const float &other);
    BigNumber(const double &other);

    // friend const BigNumber operator""_bn(const char *number, size_t size);

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
    chunk_t *_chunks;     // array of chunks
    size_t _chunks_size;  // size of the array
    int32_t _exponent;    // exponent of the number
    bool _is_negative;    // true if the number is negative

    BigNumber() : _chunks(nullptr), _chunks_size(0), _exponent(0), _is_negative(false){};                                    // default constructor
    BigNumber(const chunk_t &chunk) : _chunks(new chunk_t[1]{chunk}), _chunks_size(1), _exponent(0), _is_negative(false){};  // constructor for a single chunk
    BigNumber(chunk_t *chunks, size_t chunks_size);

    size_t _size() const { return _chunks_size; }                    // get the size of the number
    const chunk_t _get_chunk(const int32_t &exponent) const;         // get the chunk at the given exponent
    void _set_chunk(const int32_t &exponent, const chunk_t &value);  // set the chunk at the given exponent

    void _strip_zeros();
    bool _is_zero() const;

    const BigNumber _negate() const;
    const BigNumber _abs() const;

    const BigNumber _add(const BigNumber &other) const;
    const BigNumber _subtract(const BigNumber &other) const;
    const BigNumber _multiply(const BigNumber &other) const;
    const BigNumber _multiply_simple(const BigNumber &other) const;
    const BigNumber _divide(const BigNumber &other) const;

    const BigNumber _shift(int32_t shift) const;

    const size_t _int_chunks_count() const;
    const size_t _frac_chunks_count() const;
};

const BigNumber operator""_bn(const char *number, size_t size);

namespace math {

class Fraction {
   public:
    Fraction(const bignum::BigNumber &numerator, const bignum::BigNumber &denominator);
    Fraction(const bignum::BigNumber &numerator);

    const bignum::BigNumber to_decimal() const;

    friend const Fraction operator+(const Fraction &a, const Fraction &b);
    friend const Fraction operator-(const Fraction &a, const Fraction &b);
    friend const Fraction operator*(const Fraction &a, const Fraction &b);
    friend const Fraction operator/(const Fraction &a, const Fraction &b);

    friend const bool operator==(const Fraction &a, const Fraction &b);
    friend const bool operator!=(const Fraction &a, const Fraction &b);
    friend const bool operator<(const Fraction &a, const Fraction &b);
    friend const bool operator>(const Fraction &a, const Fraction &b);
    friend const bool operator<=(const Fraction &a, const Fraction &b);
    friend const bool operator>=(const Fraction &a, const Fraction &b);

    const std::string to_string() const;

    const Fraction operator-() const;

   private:
    bignum::BigNumber _numerator;
    bignum::BigNumber _denominator;
};
const Fraction operator""_fr(const char *number, size_t size);

const bignum::BigNumber sqrt(const bignum::BigNumber &number);
const bignum::BigNumber PiFast(size_t n);
}  // namespace math

}  // namespace bignum
