#include <gtest/gtest.h>
#include <long_arithmetic.h>

TEST(Multiplication, PositivePositive) {
    bignum::BigNumber number1("999999999999999999");
    bignum::BigNumber number2("999999999999999999");
    bignum::BigNumber number3 = number1 * number2;
    ASSERT_EQ(number3.to_string(), "999999999999999998000000000000000001");
}

TEST(Multiplication, PositiveNegative) {
    bignum::BigNumber number1("2");
    bignum::BigNumber number2("-0.5");
    bignum::BigNumber number3 = number1 * number2;

    ASSERT_EQ(number3.to_string(), "-1");
}
