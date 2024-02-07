# Long Arithmetic

C++ implementation of long arithmetics.

## Table of Contents

- [Long Arithmetic](#long-arithmetic)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Task](#task)
  - [Plan](#plan)
    - [Optional](#optional)
  - [Development](#development)
  
## Installation

```bash
git clone https://github.com/d0gied/long-arithmetic.git
cd long-arithmetic
git submodule update --init --recursive
mkdir build
cd build
cmake ..
cmake --install .
```

## Usage

```cpp
#include <iostream>
#include "long_arithmetic.h"

int main() {
  bignum::BigNumber a = 123;
  bignum::BigNumber b = "123456789012345678901234567890";
  std::cout << a + b << std::endl;
  return 0;
}
```

## [Task](task.md)

## Plan

1. [x] Organize project repository.
2. [x] Make basic constructors of BigNumber.
3. [x] Configure CMake.
4. [x] Add google tests submodule.
5. [x] Add basic tests for BigNumber.
6. [x] Add conversion from BigNumber to string.
7. [ ] Add basic comparison operations for BigNumber.
8. [ ] Add addition and subtraction operations for BigNumber.
9. [ ] Add multiplication and division operations for BigNumber.
10. [ ] Realize Pi calculation with given precision.
11. [ ] Measure time of Pi calculation.

### Optional

1. [ ] Add conversion from float to BigNumber.


## Development

```bash
git clone https://github.com/d0gied/long-arithmetic.git
cd long-arithmetic
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```