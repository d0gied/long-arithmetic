#include <gtest/gtest.h>
#include <long_arithmetic.h>

TEST(Constructor, BigInt) {
    bignum::BigNumber number("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::string number_str = number.to_string();
    ASSERT_EQ(number_str, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

TEST(Constructor, NegativeBigInt) {
    bignum::BigNumber number("-123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::string number_str = number.to_string();
    ASSERT_EQ(number_str, "-123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

TEST(Constructor, BigIntWithFractionalSize) {
    bignum::BigNumber number("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", 10);
    std::string number_str = number.to_string();
    ASSERT_EQ(number_str, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890.0000000000");
}

TEST(Constructor, BigIntWithFractionalPart) {
    bignum::BigNumber number("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890.1234567890");
    std::string number_str = number.to_string();
    ASSERT_EQ(number_str, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890.1234567890");
}

TEST(Constructor, BigIntWithFractionalPartCut) {
    bignum::BigNumber number("123.456", 2);
    std::string number_str = number.to_string();
    ASSERT_EQ(number_str, "123.45");
}

TEST(Constructor, DirectString) {
    bignum::BigNumber number = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    std::string number_str = number.to_string();
    ASSERT_EQ(number_str, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

TEST(Constructor, DirectInt) {
    bignum::BigNumber number = 1234567890123456789;
    std::string number_str = number.to_string();
    ASSERT_EQ(number_str, "1234567890123456789");
}