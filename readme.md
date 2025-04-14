# cpp-lorelai

A C++ library for generating Lorem Ipsum text, ported from [ultirequiem/lorelai](https://github.com/ultirequiem/lorelai).

## Features

- Generate Lorem Ipsum text with a specified word count.
- Generate multiple paragraphs of Lorem Ipsum.

## Usage

```cpp
#include "lorem_ipsum.hpp"
#include <iostream>

int main() {
    std::cout << lorelai::generate(10) << std::endl;

    auto paragraphs = lorelai::generate_paragraphs(2, 10);

    for (const auto& paragraph : paragraphs) {
        std::cout << paragraph << "\n\n";
    }

    return 0;
}
```
