# lorem (lorelai)

[![CI](https://github.com/UltiRequiem/lorem/actions/workflows/ci.yaml/badge.svg)](https://github.com/UltiRequiem/lorem/actions/workflows/ci.yaml)
[![License](https://img.shields.io/github/license/UltiRequiem/lorem)](./LICENSE)

Lorem Ipsum text for C++. A tiny C++17 library with no dependencies, plus a `lorelai-cli` command.
A port of [ultirequiem/lorelai](https://github.com/ultirequiem/lorelai).

```cpp
#include <lorem_ipsum.hpp>
#include <iostream>

int main() {
    std::cout << lorelai::generate(10) << '\n';
    // lorem ipsum dolor sit amet consectetur adipiscing elit sed do

    for (const auto& paragraph : lorelai::generate_paragraphs(2, 10)) {
        std::cout << paragraph << "\n\n";
    }
}
```

## API

Everything is in the `lorelai` namespace, declared in [`include/lorem_ipsum.hpp`](./include/lorem_ipsum.hpp).

| Function | Returns |
|---|---|
| `std::string generate(int word_count)` | exactly `word_count` words separated by single spaces. The classic 19 words repeat when you ask for more. Zero or negative gives `""` |
| `std::vector<std::string> generate_paragraphs(int paragraph_count, int words_per_paragraph)` | that many paragraphs, each made by `generate`. Zero or negative paragraphs gives an empty vector |

The output is deterministic: it always starts with `lorem ipsum dolor sit amet`, and every paragraph is the same.

## Use it in your project

With CMake 3.14 or newer, pull it straight from GitHub:

```cmake
include(FetchContent)
FetchContent_Declare(lorelai
  GIT_REPOSITORY https://github.com/UltiRequiem/lorem.git
  GIT_TAG main)
FetchContent_MakeAvailable(lorelai)

target_link_libraries(my_app PRIVATE lorelai::lorelai)
```

Or install it once and use `find_package`:

```sh
cmake -S . -B build
cmake --build build
cmake --install build --prefix ~/.local
```

```cmake
find_package(lorelai 1.0 REQUIRED)
target_link_libraries(my_app PRIVATE lorelai::lorelai)
```

When used through `FetchContent` or `add_subdirectory` only the library is built, not the CLI or the tests.
Options: `LORELAI_BUILD_CLI`, `LORELAI_BUILD_TESTS`, `LORELAI_INSTALL`.

Without CMake, the library is two files: copy `include/lorem_ipsum.hpp` and `src/lorem_ipsum.cpp`.

## Command line

```sh
$ lorelai-cli -w 5
lorem ipsum dolor sit amet

$ lorelai-cli -p 2 4
lorem ipsum dolor sit

lorem ipsum dolor sit
```

| Option | Does |
|---|---|
| `-w <words>` | print that many words |
| `-p <paragraphs> <words>` | print paragraphs of that many words |
| `-h`, `--help` | usage |

Counts must be whole numbers from 0 to 10000000. Anything else prints a message to stderr and exits with code 1.

## Develop

```sh
cmake -S . -B build
cmake --build build
cd build && ctest --output-on-failure
```

Needs a C++17 compiler (GCC, Clang or MSVC) and CMake 3.14+. The tests also cover the CLI, including bad input.

## License

MIT, see [LICENSE](./LICENSE).
