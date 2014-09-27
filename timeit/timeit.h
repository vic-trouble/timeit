#pragma once

#include <chrono>
#include <functional>

namespace timeit
{

  template <typename Duration = std::chrono::milliseconds>
  Duration total(std::function<void()> function, unsigned iterations = 1)
  {
    if (!function)
      throw std::invalid_argument("can't measure empty function");

    using std::chrono::high_resolution_clock;
    auto before = high_resolution_clock::now();

    while (iterations--)
      function();

    auto after = high_resolution_clock::now();
    auto elapsed = after - before;
    return std::chrono::duration_cast<Duration>(elapsed);
  }

  template <typename Duration = std::chrono::milliseconds>
  Duration average(std::function<void()> function, unsigned iterations = 1)
  {
    return total<Duration>(function, iterations) / iterations;
  }

}