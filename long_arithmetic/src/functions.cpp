#include <long_arithmetic.h>

namespace bignum {
BigNumber BigNumber::abs() const {
    BigNumber result = *this;
    result.is_negative = false;
    return result;
}

BigNumber BigNumber::copy() const {
    return *this;
}

BigNumber BigNumber::negate() const {
    BigNumber result = *this;
    result.is_negative = !result.is_negative;
    return result;
}

BigNumber BigNumber::with_fractional_size(size_t fractional_size) const {
    std::string number = to_string();
    return BigNumber(number, fractional_size);  // TODO: optimize
}

bool BigNumber::is_zero() const {
    for (size_t i = 0; i < chunks.size(); ++i) {
        if (chunks[i] != 0) {
            return false;
        }
    }
    return true;
}
}  // namespace bignum