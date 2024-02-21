
#include "base.cpp"

using namespace bignum;
// Multiplication base test class with parameters

// Test suite for multiplication

class Division : public ArithmeticTest {};

// Test cases for multiplication
TEST_P(Division, Test) {
    bignum::SET_DIV_PRECISION(18);
    BigNumber number1(std::get<0>(GetParam()));
    BigNumber number2(std::get<1>(GetParam()));
    BigNumber expected(std::get<2>(GetParam()));
    BigNumber result = number1 / number2;

    std::cout << number1.to_string() << " / " << number2.to_string() << " = " << result.to_string() << std::endl;
    ASSERT_EQ(result, expected) << "Expected: " << expected.to_string() << " Got: " << result.to_string();
}

INSTANTIATE_TEST_SUITE_P(
    ,
    Division,
    testing::Values(
        std::make_tuple("0", "999", "0"),
        std::make_tuple("5", "2", "2.5"),
        std::make_tuple("-1", "1", "-1"),
        std::make_tuple("2", "0.5", "4"),
        std::make_tuple("0.5", "0.5", "1"),
        std::make_tuple("1", "3", "0." + std::string(18, '3'))));
