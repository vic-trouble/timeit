timeit [![Build Status](https://travis-ci.org/vic-trouble/timeit.svg?branch=master)](https://travis-ci.org/vic-trouble/timeit)
=====
Inspired by Python's `timeit`, set of simple API for performance micro-measurements in C++.

Examples
-----

```c++
#include <chrono>
#include <iostream>
#include <thread>

#include <timeit/timeit.h>

void sleep100ms()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main()
{
    std::cout << "elapsed " << timeit::min(sleep100ms).count() << " ms" << std::endl;
    return 0;
}
```