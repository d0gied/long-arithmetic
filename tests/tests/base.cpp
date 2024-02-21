#include <gtest/gtest.h>
#include <long_arithmetic.h>

#include <tuple>
using namespace bignum;

class ArithmeticTest : public testing::TestWithParam<std::tuple<std::string, std::string, std::string>> {};