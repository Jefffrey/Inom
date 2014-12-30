##Inom

This library is aimed at being a proof of concept and nothing more. It's not intended for any real use and it's numerically just a mental and theoretical masturbation.

####Example

```c++
#include <iostream>
#include <inom/integer>

int main() {
    using namespace inom::literals;
    auto x = 1_int;
    auto y = 2_int;
    std::cout << (x + y); // 3
}
```
