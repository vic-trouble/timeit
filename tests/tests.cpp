#include <iostream>
#include <functional>
#include <thread>

#include <timeit/timeit.h>

#include "assert.h"

namespace timeit
{
    namespace tests
    {
        TEST(StatShouldCallFunc)
        {
            bool called = false;
            auto empty = [&called](){ called = true; };

            timeit::stat(empty);

            ASSERT_TRUE(called);
        }

        TEST(TotalShouldReturnNotLessThan10msWhen10msFunc)
        {
            std::chrono::milliseconds delay(10);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };

            auto elapsed = timeit::total(func);

            ASSERT_TRUE(elapsed >= delay);
        }

        TEST(TotalShouldReturnNotLessThan20msWhen10msFuncAnd2Iterations)
        {
            std::chrono::milliseconds delay(10);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };

            auto elapsed = timeit::total(func, 2);

            ASSERT_TRUE(elapsed >= 2 * delay);
        }

        TEST(StatShouldCallFuncExactlyNumberOfIterations)
        {
            unsigned iterations = 1000, times = 0;
            auto func = [&times](){ ++times; };

            timeit::stat(func, iterations);

            ASSERT_EQUAL(iterations, times);
        }

        TEST(TotalShouldReturnNotLessThan10000usWhen10msFunc)
        {
            std::chrono::milliseconds delay(10);
            std::chrono::microseconds delay_us(10 * 1000);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };

            auto elapsed = timeit::total<std::chrono::microseconds>(func);

            ASSERT_TRUE(elapsed >= delay_us);
        }

        TEST(StatShouldThrowWhenEmptyFunc)
        {
            std::function<void()> empty;

            ASSERT_THROW(std::invalid_argument, [&](){ timeit::stat(empty); });
        }

        TEST(AverageShouldReturnLessThanTotalWhenMultipleIterations)
        {
            std::chrono::milliseconds delay(10);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };
            unsigned iterations = 2;

            auto stats = timeit::stat(func, iterations);

            ASSERT_TRUE(stats.average < stats.total);
        }

        TEST(StatShouldReturnMinLessThanMax)
        {
            auto delay = std::chrono::milliseconds(10);
            auto func = [&delay]{ std::this_thread::sleep_for(delay); delay *= 2; };
            unsigned iterations = 3;

            auto stats = timeit::stat(func, iterations);

            ASSERT_TRUE(stats.min < stats.max);
        }

        TEST(MinShouldAlwaysBeNonNegative)
        {
            std::chrono::milliseconds delay(10);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };

            auto min = timeit::min(func);

            ASSERT_TRUE(min.count() >= 0);
        }

        TEST(HighPrecisionAverage)
        {
            int i = 0;
            auto super_fast = [&i](){ ++i; };
            auto iterations = 10000000;

            timeit::stats<std::chrono::nanoseconds> stats = timeit::stat<std::chrono::nanoseconds>(super_fast, iterations);

            const auto &total = stats.total;
            std::cerr << total.count() << std::endl << iterations << std::endl << (total / iterations).count() << std::endl << (total.count() / iterations) << std::endl;

            ASSERT_TRUE(stats.total.count() > iterations);  // if that fails, try increasing iterations
            ASSERT_TRUE(stats.average.count() > 0);
        }
		
    }
}

int main()
{
    try
    {
        using namespace timeit::tests;
        auto test_cases = {
            StatShouldCallFunc,
            TotalShouldReturnNotLessThan10msWhen10msFunc,
            TotalShouldReturnNotLessThan20msWhen10msFuncAnd2Iterations,
            StatShouldCallFuncExactlyNumberOfIterations,
            TotalShouldReturnNotLessThan10000usWhen10msFunc,
            StatShouldThrowWhenEmptyFunc,
            AverageShouldReturnLessThanTotalWhenMultipleIterations,
            StatShouldReturnMinLessThanMax,
            MinShouldAlwaysBeNonNegative,
            HighPrecisionAverage
            };

        for (auto &test: test_cases)
            test();

        std::cout << "All OK" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}