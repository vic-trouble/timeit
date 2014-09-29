#include <iostream>
#include <functional>
#include <thread>

#include <timeit/timeit.h>

#include "assert.h"

namespace timeit
{
    namespace tests
    {
        TEST(AllShouldCallFunc)
        {
            bool called = false;
            auto empty = [&called](){ called = true; };

            timeit::all(empty);

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

        TEST(AllShouldCallFuncExactlyNumberOfIterations)
        {
            unsigned iterations = 1000, times = 0;
            auto func = [&times](){ ++times; };

            timeit::all(func, iterations);

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

        TEST(AllShouldThrowWhenEmptyFunc)
        {
            std::function<void()> empty;

            ASSERT_THROW(std::invalid_argument, [&](){ timeit::all(empty); });
        }

        TEST(AverageShouldReturnLessThanTotalWhenMultipleIterations)
        {
            std::chrono::milliseconds delay(10);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };
            unsigned iterations = 2;

            auto stats = timeit::all(func, iterations);

            ASSERT_TRUE(stats.average < stats.total);
        }

        TEST(AllShouldReturnMinLessThanMax)
        {
            auto delay = std::chrono::milliseconds(10);
            auto func = [&delay]{ std::this_thread::sleep_for(delay); delay *= 2; };
            unsigned iterations = 3;

            auto stats = timeit::all(func, iterations);

            ASSERT_TRUE(stats.min < stats.max);
        }

        TEST(MinShouldAlwaysBeNonNegative)
        {
            std::chrono::milliseconds delay(10);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };

            auto min = timeit::min(func);

            ASSERT_TRUE(min.count() >= 0);
        }
		
    }
}

int main()
{
    try
    {
        using namespace timeit::tests;
        AllShouldCallFunc();
		TotalShouldReturnNotLessThan10msWhen10msFunc();
        TotalShouldReturnNotLessThan20msWhen10msFuncAnd2Iterations();
        AllShouldCallFuncExactlyNumberOfIterations();
        TotalShouldReturnNotLessThan10000usWhen10msFunc();
        AllShouldThrowWhenEmptyFunc();
        AverageShouldReturnLessThanTotalWhenMultipleIterations();
        AllShouldReturnMinLessThanMax();
        MinShouldAlwaysBeNonNegative();
        std::cout << "All OK" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}