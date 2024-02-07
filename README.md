# Long Arithmetic

C++ implementation of long arithmetics.

## Table of Contents

- [Long Arithmetic](#long-arithmetic)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Task](#task)
  - [Test](#test)
  - [Benchmark](#benchmark)
    - [Results](#results)
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

## Test

```bash
./build/tests/run_tests
```

## Benchmark

```bash
./build/benchmark/run_benchmark
```

### Results

```cpp
--------------------------------------------------------------------
Benchmark                          Time             CPU   Iterations
--------------------------------------------------------------------
CompareLongToLong/1              401 ns          400 ns      1745383
CompareLongToLong/8              407 ns          406 ns      1752616
CompareLongToLong/64             406 ns          404 ns      1729655
CompareLongToLong/512            402 ns          401 ns      1752028
CompareLongToLong/4096           405 ns          404 ns      1752581
CompareLongToLong/32768          403 ns          402 ns      1747418
CompareLongToLong/262144         399 ns          397 ns      1743336
CompareLongToLong/1048576        399 ns          398 ns      1781497
CreateFromString/1               725 ns          723 ns       955892
CreateFromString/8               735 ns          732 ns       947983
CreateFromString/64             1154 ns         1151 ns       595831
CreateFromString/512            3578 ns         3564 ns       196872
CreateFromString/4096          22557 ns        22444 ns        31013
CreateFromString/32768        174056 ns       173658 ns         4029
CreateFromString/262144      1398363 ns      1391958 ns          505
CreateFromString/1048576     5676835 ns      5656935 ns          123
```

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