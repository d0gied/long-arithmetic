#include <gtest/gtest.h>
#include <long_arithmetic.h>

TEST(Division, OneByTwo) {
    bignum::BigNumber number1("-1");
    bignum::BigNumber number2("2");
    bignum::BigNumber number3 = number1 / number2;
    ASSERT_EQ(number3.to_string(), "-0.5");
}

TEST(Division, TwoByOne) {
    bignum::BigNumber number1("2");
    bignum::BigNumber number2("1");
    bignum::BigNumber number3 = number1 / number2;
    ASSERT_EQ(number3.to_string(), "2");
}

TEST(Division, OneByPointFive) {
    bignum::BigNumber number1("1");
    bignum::BigNumber number2("0.5");
    bignum::BigNumber number3 = number1 / number2;
    ASSERT_EQ(number3.to_string(), "2");
}