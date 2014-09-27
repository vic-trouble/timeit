#pragma once

#include <chrono>
#include <functional>

namespace timeit
{

  using default_duration = std::chrono::milliseconds;

  template <typename Duration = default_duration>
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

  template <typename Duration = default_duration>
  Duration average(std::function<void()> function, unsigned iterations = 1)
  {
    return total<Duration>(function, iterations) / iterations;
  }

  template <typename Duration = default_duration>
  std::pair<Duration, Duration> minmax(std::function<void()> function, unsigned iterations = 1)
  {
    if (!function)
      throw std::invalid_argument("can't measure empty function");

    using std::chrono::high_resolution_clock;

    using duration_type = decltype(high_resolution_clock::now() - high_resolution_clock::now());
    duration_type min = duration_type::min(), max = duration_type::max();

    while (iterations--)
    {
      auto before = high_resolution_clock::now();
      function();
      auto after = high_resolution_clock::now();
      auto elapsed = after - before;

      if (elapsed < min)
        min = elapsed;
      if (elapsed > max)
        max = elapsed;
    }

    return make_pair(
      std::chrono::duration_cast<Duration>(min), 
      std::chrono::duration_cast<Duration>(max));
  }

}