#include <gtest/gtest.h>
#include <long_arithmetic.h>

TEST(Multiplication, PositivePositive) {
    bignum::BigNumber number1("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    bignum::BigNumber number2("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::string number_str = (number1 * number2).to_string();
    ASSERT_EQ(number_str, "15241578753238836750495351562566681945008382873376009755225118122311263526910001524158887639079520012193273126047859425087639153757049236500533455762536198787501905199875019052100");
}

TEST(Multiplication, NegativeNegative) {
    bignum::BigNumber number1("-123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    bignum::BigNumber number2("-123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::string number_str = (number1 * number2).to_string();
    ASSERT_EQ(number_str, "15241578753238836750495351562566681945008382873376009755225118122311263526910001524158887639079520012193273126047859425087639153757049236500533455762536198787501905199875019052100");
}

TEST(Multiplication, PositiveNegative) {
    bignum::BigNumber number1("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    bignum::BigNumber number2("-123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::string number_str = (number1 * number2).to_string();
    ASSERT_EQ(number_str, "-15241578753238836750495351562566681945008382873376009755225118122311263526910001524158887639079520012193273126047859425087639153757049236500533455762536198787501905199875019052100");
}

TEST(Multiplication, NegativePositive) {
    bignum::BigNumber number1("-123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    bignum::BigNumber number2("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::string number_str = (number1 * number2).to_string();
    ASSERT_EQ(number_str, "-15241578753238836750495351562566681945008382873376009755225118122311263526910001524158887639079520012193273126047859425087639153757049236500533455762536198787501905199875019052100");
}

TEST(Multiplication, Zero) {
    bignum::BigNumber number1("0");
    bignum::BigNumber number2("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::string number_str = (number1 * number2).to_string();
    ASSERT_EQ(number_str, "0");
}

TEST(Multiplication, FloatToFloat) {
    bignum::BigNumber number1("0.5");
    bignum::BigNumber number2("0.5");
    bignum::BigNumber number3 = number1 * number2;
    std::string number_str = number3.to_string();
    ASSERT_EQ(number_str, "0.25");
}
