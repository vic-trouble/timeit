#pragma once

#include <chrono>
#include <functional>

namespace timeit
{

  std::chrono::milliseconds total(std::function<void()> function)
  {
    function();
    return std::chrono::milliseconds{};
  }

}