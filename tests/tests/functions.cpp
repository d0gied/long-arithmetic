#include <gtest/gtest.h>
#include <long_arithmetic.h>

TEST(Functions, Negate) {
    bignum::BigNumber number("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::string number_str = number.negate().to_string();
    ASSERT_EQ(number_str, "-123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

TEST(Functions, Abs) {
    bignum::BigNumber number("-123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::string number_str = number.abs().to_string();
    ASSERT_EQ(number_str, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");

    number = bignum::BigNumber("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    number_str = number.abs().to_string();
    ASSERT_EQ(number_str, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

TEST(Functions, IsZero) {
    bignum::BigNumber number("0");
    ASSERT_TRUE(number.is_zero());

    number = bignum::BigNumber("1");
    ASSERT_FALSE(number.is_zero());

    number = bignum::BigNumber("-1");
    ASSERT_FALSE(number.is_zero());

    number = bignum::BigNumber("-0");
    ASSERT_TRUE(number.is_zero());

    number = bignum::BigNumber("0.000");
    ASSERT_TRUE(number.is_zero());
}