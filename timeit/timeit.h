#pragma once

#include <chrono>
#include <functional>

namespace timeit
{

  template <typename Duration = std::chrono::milliseconds>
  Duration total(std::function<void()> function, unsigned iterations = 1)
  {
    using std::chrono::high_resolution_clock;
    auto before = high_resolution_clock::now();

    while (iterations--)
      function();

    auto after = high_resolution_clock::now();
    auto elapsed = after - before;
    return std::chrono::duration_cast<Duration>(elapsed);
  }

}