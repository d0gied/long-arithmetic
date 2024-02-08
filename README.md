# Long Arithmetic

C++ implementation of long arithmetics.

## Table of Contents

- [Long Arithmetic](#long-arithmetic)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Task](#task)
  - [Test](#test)
    - [Help](#help)
  - [Benchmark](#benchmark)
    - [Help](#help-1)
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

### Help

```bash
./build/tests/run_tests --help
```

## Benchmark

```bash
./build/benchmark/run_benchmark
```

### Help
  
```bash
$ ./build/benchmark/run_benchmark --help
benchmark [--benchmark_list_tests={true|false}]
          [--benchmark_filter=<regex>]
          [--benchmark_min_time=`<integer>x` OR `<float>s` ]
          [--benchmark_min_warmup_time=<min_warmup_time>]
          [--benchmark_repetitions=<num_repetitions>]
          [--benchmark_enable_random_interleaving={true|false}]
          [--benchmark_report_aggregates_only={true|false}]
          [--benchmark_display_aggregates_only={true|false}]
          [--benchmark_format=<console|json|csv>]
          [--benchmark_out=<filename>]
          [--benchmark_out_format=<json|console|csv>]
          [--benchmark_color={auto|true|false}]
          [--benchmark_counters_tabular={true|false}]
          [--benchmark_context=<key>=<value>,...]
          [--benchmark_time_unit={ns|us|ms|s}]
          [--v=<verbosity>]
  ```

### Results

```cpp
-------------------------------------------------------------------------
Benchmark/digits                        Time             CPU   Iterations
-------------------------------------------------------------------------
AddLongToLong/1                     0.000 ms        0.000 ms      1776073
AddLongToLong/8                     0.000 ms        0.000 ms      1774564
AddLongToLong/64                    0.001 ms        0.001 ms      1230769
AddLongToLong/512                   0.002 ms        0.002 ms       463610
AddLongToLong/4096                  0.009 ms        0.009 ms        77641
AddLongToLong/32768                 0.070 ms        0.069 ms        10130
AddLongToLong/262144                0.557 ms        0.552 ms         1264
AddLongToLong/1048576                2.23 ms         2.21 ms          317
CreateFromString/1                  0.001 ms        0.000 ms      1395395
CreateFromString/8                  0.001 ms        0.001 ms      1379963
CreateFromString/64                 0.001 ms        0.001 ms       762477
CreateFromString/512                0.003 ms        0.003 ms       219711
CreateFromString/4096               0.022 ms        0.021 ms        32672
CreateFromString/32768              0.169 ms        0.167 ms         4189
CreateFromString/262144              1.35 ms         1.33 ms          525
CreateFromString/1048576             5.46 ms         5.37 ms          129
MultiplyLongToLong/1                0.001 ms        0.001 ms       996796
MultiplyLongToLong/8                0.001 ms        0.001 ms      1016585
MultiplyLongToLong/64               0.002 ms        0.002 ms       455987
MultiplyLongToLong/512              0.026 ms        0.026 ms        26783
MultiplyLongToLong/4096              1.49 ms         1.47 ms          476
MultiplyLongToLong/32768             93.9 ms         92.5 ms            8
MultiplyLongToLong/262144            5983 ms         5926 ms            1
MultiplyLongToLong/1048576          95835 ms        94922 ms            1
SubstractionLongToLong/1            0.001 ms        0.001 ms       508241
SubstractionLongToLong/8            0.001 ms        0.001 ms       507898
SubstractionLongToLong/64           0.002 ms        0.002 ms       363404
SubstractionLongToLong/512          0.005 ms        0.005 ms       141966
SubstractionLongToLong/4096         0.029 ms        0.029 ms        24139
SubstractionLongToLong/32768        0.223 ms        0.221 ms         3166
SubstractionLongToLong/262144        1.80 ms         1.78 ms          390
SubstractionLongToLong/1048576       7.18 ms         7.11 ms           97
```

## Plan

1. [x] Organize project repository.
2. [x] Make basic constructors of BigNumber.
3. [x] Configure CMake.
4. [x] Add google tests submodule.
5. [x] Add basic tests for BigNumber.
6. [x] Add conversion from BigNumber to string.
7. [x] Add basic comparison operations for BigNumber.
8. [x] Add addition and subtraction operations for BigNumber.
9. [x] Add multiplication operation for BigNumber. 
10. [ ] Add division operation for BigNumber.
11. [ ] Implement Pi calculation with given precision.
12. [ ] Measure time of Pi calculation.

### Optional

1. [x] Add conversion from float to BigNumber.
2. [x] Add benchmark for BigNumber.


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