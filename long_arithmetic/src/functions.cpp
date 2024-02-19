#include <long_arithmetic.h>

namespace bignum {

const BigNumber BigNumber::_abs() const {
    BigNumber result = *this;
    result._is_negative = false;
    return result;
}

const BigNumber BigNumber::_negate() const {
    BigNumber result = *this;
    result._is_negative = !result._is_negative;
    return result;
}

bool BigNumber::_is_zero() const {
    return _chunks.size() == 0;
}

const BigNumber BigNumber::_shift(int32_t exp) const {
    BigNumber result = *this;
    result._exponent += exp;
    return result;
}
}  // namespace bignum