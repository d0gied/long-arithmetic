#include "base.cpp"

class Operators : public testing::TestWithParam<std::tuple<std::string, std::string, int>> {};

TEST_P(Operators, Test) {
    BigNumber number1(std::get<0>(GetParam()));
    BigNumber number2(std::get<1>(GetParam()));
    int expected = std::get<2>(GetParam());

    bool expected_less = expected < 0;
    bool expected_greater = expected > 0;
    bool expected_equal = expected == 0;

    bool result_less = number1 < number2;
    bool result_greater = number1 > number2;
    bool result_equal = number1 == number2;
    bool result_not_equal = number1 != number2;
    bool result_less_or_equal = number1 <= number2;
    bool result_greater_or_equal = number1 >= number2;

    std::cout << number1.to_string() << " < " << number2.to_string() << " = " << result_less << std::endl;
    ASSERT_EQ(result_less, expected_less) << "Expected: " << expected_less << " Got: " << result_less;

    std::cout << number1.to_string() << " > " << number2.to_string() << " = " << result_greater << std::endl;
    ASSERT_EQ(result_greater, expected_greater) << "Expected: " << expected_greater << " Got: " << result_greater;

    std::cout << number1.to_string() << " == " << number2.to_string() << " = " << result_equal << std::endl;
    ASSERT_EQ(result_equal, expected_equal) << "Expected: " << expected_equal << " Got: " << result_equal;

    std::cout << number1.to_string() << " != " << number2.to_string() << " = " << result_not_equal << std::endl;
    ASSERT_EQ(result_not_equal, !expected_equal) << "Expected: " << !expected_equal << " Got: " << result_not_equal;

    std::cout << number1.to_string() << " <= " << number2.to_string() << " = " << result_less_or_equal << std::endl;
    ASSERT_EQ(result_less_or_equal, expected_less || expected_equal) << "Expected: " << (expected_less || expected_equal) << " Got: " << result_less_or_equal;

    std::cout << number1.to_string() << " >= " << number2.to_string() << " = " << result_greater_or_equal << std::endl;
    ASSERT_EQ(result_greater_or_equal, expected_greater || expected_equal) << "Expected: " << (expected_greater || expected_equal) << " Got: " << result_greater_or_equal;
}

INSTANTIATE_TEST_SUITE_P(
    ,
    Operators,
    testing::Values(
        std::make_tuple("0", "0", 0),
        std::make_tuple("1", "1", 0),
        std::make_tuple("1", "-1", 1),
        std::make_tuple("0.5", "0.5", 0),
        std::make_tuple("1", "0.5", 1)));