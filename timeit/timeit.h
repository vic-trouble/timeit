#pragma once

#if defined(__clang__)
    #define TIMEIT_USING_TYPEDEF
#elif defined(__GNUC__)
    #if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)
        #error This file requires GCC 4.6 or higher
    #elif __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
        #define TIMEIT_USING_TYPEDEF
    #endif
#elif defined(_MSC_VER)
    #if _MSC_VER < 1800
        #error This file require Visual Studio 2013
    #else
        #define TIMEIT_USING_TYPEDEF
    #endif
#endif

#include <chrono>
#include <functional>

namespace timeit
{

#ifdef TIMEIT_USING_TYPEDEF
    using default_duration = std::chrono::milliseconds;
#else
    typedef std::chrono::milliseconds default_duration;
#endif

    template <typename Duration>
    struct stats
    {
        Duration min, max, average, total;
    };

    template <typename Duration = default_duration>
    stats<Duration> stat(std::function<void()> function, const unsigned iterations = 1)
    {
        if (!function)
            throw std::invalid_argument("can't measure empty function");

        using std::chrono::high_resolution_clock;

#ifdef TIMEIT_USING_TYPEDEF
        using clock_duration = high_resolution_clock::duration;
#else
        typedef high_resolution_clock::duration clock_duration;
#endif
        clock_duration min = clock_duration::max(), max = clock_duration::min();
        std::chrono::duration<double> total{};

        for (auto i = iterations; i--; )
        {
            auto before = high_resolution_clock::now();
            function();
            auto after = high_resolution_clock::now();
            auto elapsed = after - before;

            total += elapsed;
            if (elapsed < min)
                min = elapsed;
            if (elapsed > max)
                max = elapsed;
        }

        stats<Duration> s;
        s.min = std::chrono::duration_cast<Duration>(min);
        s.max = std::chrono::duration_cast<Duration>(max);
        s.average = std::chrono::duration_cast<Duration>(total / iterations);
        s.total = std::chrono::duration_cast<Duration>(total);
        return s;
    }

    template <typename Duration = default_duration>
    Duration average(std::function<void()> function, unsigned iterations = 1)
    {
        return stat<Duration>(function, iterations).average;
    }

    template <typename Duration = default_duration>
    Duration min(std::function<void()> function, unsigned iterations = 1)
    {
        return stat<Duration>(function, iterations).min;
    }

    template <typename Duration = default_duration>
    Duration max(std::function<void()> function, unsigned iterations = 1)
    {
        return stat<Duration>(function, iterations).max;
    }

    template <typename Duration = default_duration>
    Duration total(std::function<void()> function, unsigned iterations = 1)
    {
        return stat<Duration>(function, iterations).total;
    }

    template <typename Duration = default_duration>
    Duration timeit(std::function<void()> function)
    {
        return stat<Duration>(function, 1).total;
    }

}