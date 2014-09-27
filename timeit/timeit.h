#pragma once

#include <chrono>
#include <functional>

namespace timeit
{

  std::chrono::milliseconds total(std::function<void()> function)
  {
    using std::chrono::high_resolution_clock;
    auto before = high_resolution_clock::now();

    function();

    auto after = high_resolution_clock::now();
    auto elapsed = after - before;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
  }

}