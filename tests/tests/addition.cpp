#include "base.cpp"

class Addition : public ArithmeticTest {};

TEST_P(Addition, Test) {
    BigNumber number1(std::get<0>(GetParam()));
    BigNumber number2(std::get<1>(GetParam()));
    BigNumber expected(std::get<2>(GetParam()));
    BigNumber result = number1 + number2;

    std::cout << number1.to_string() << " + " << number2.to_string() << " = " << result.to_string() << std::endl;
    ASSERT_EQ(result, expected) << "Expected: " << expected.to_string() << " Got: " << result.to_string();
}

INSTANTIATE_TEST_SUITE_P(,
                         Addition,
                         testing::Values(
                             std::make_tuple("0", "0", "0"),
                             std::make_tuple("1", "1", "2"),
                             std::make_tuple("1", "-1", "0"),
                             std::make_tuple("99", "1", "100"),
                             std::make_tuple("0.5", "0.5", "1"),
                             std::make_tuple("1", "0.5", "1.5")));