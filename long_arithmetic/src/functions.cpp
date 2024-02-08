#include <long_arithmetic.h>

namespace bignum {
const BigNumber BigNumber::abs() const {
    BigNumber result = *this;
    result._is_negative = false;
    return result;
}

const BigNumber BigNumber::negate() const {
    BigNumber result = *this;
    result._is_negative = !result._is_negative;
    return result;
}

const BigNumber BigNumber::with_fractional_size(size_t fractional_size) const {
    std::string number = to_string();
    return BigNumber(number, fractional_size);  // TODO: optimize
}

bool BigNumber::is_zero() const {
    for (size_t i = 0; i < _chunks.size(); ++i) {
        if (_chunks[i] != 0) {
            return false;
        }
    }
    return true;
}
}  // namespace bignum