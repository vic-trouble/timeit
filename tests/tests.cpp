#include <iostream>
#include <functional>
#include <thread>

#include <timeit/timeit.h>

// ref
#define TEST_METHOD(X) void X()
#define ASSERT_TRUE(x) if (!(x)) throw Assert::assert_failed("assertion failed: " #x);
#define ASSERT_EQUAL(x, y) if (!((x) == (y))) throw Assert::assert_failed("assertion failed: " #x " == " #y);

namespace Assert
{
    class assert_failed: public std::runtime_error
    {
    public:
        explicit assert_failed(const char *what = "")
        : std::runtime_error(what)
        {
        }
    };

    template <typename Exception>
    void ExpectException(std::function<void ()> func, const char *message="assertion failed")
    {
        try
        {
            func();
            throw assert_failed(message);
        }
        catch (const Exception &)
        {
            return;
        }
        catch (...)
        {
            throw assert_failed(message);
        }
    }
}

// ^ref

namespace timeit
{
    namespace tests
    {
        TEST_METHOD(AllShouldCallFunc)
        {
            bool called = false;
            auto empty = [&called](){ called = true; };

            timeit::all(empty);

            ASSERT_TRUE(called);
        }

        TEST_METHOD(TotalShouldReturnNotLessThan10msWhen10msFunc)
        {
            std::chrono::milliseconds delay(10);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };

            auto elapsed = timeit::total(func);

            ASSERT_TRUE(elapsed >= delay);
        }

        TEST_METHOD(TotalShouldReturnNotLessThan20msWhen10msFuncAnd2Iterations)
        {
            std::chrono::milliseconds delay(10);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };

            auto elapsed = timeit::total(func, 2);

            ASSERT_TRUE(elapsed >= 2 * delay);
        }

        TEST_METHOD(AllShouldCallFuncExactlyNumberOfIterations)
        {
            unsigned iterations = 1000, times = 0;
            auto func = [&times](){ ++times; };

            timeit::all(func, iterations);

            ASSERT_EQUAL(iterations, times);
        }

        TEST_METHOD(TotalShouldReturnNotLessThan10000usWhen10msFunc)
        {
            std::chrono::milliseconds delay(10);
            std::chrono::microseconds delay_us(10 * 1000);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };

            auto elapsed = timeit::total<std::chrono::microseconds>(func);

            ASSERT_TRUE(elapsed >= delay_us);
        }

        TEST_METHOD(AllShouldThrowWhenEmptyFunc)
        {
            std::function<void()> empty;

            Assert::ExpectException<std::invalid_argument>([&](){ timeit::all(empty); });
        }

        TEST_METHOD(AverageShouldReturnLessThanTotalWhenMultipleIterations)
        {
            std::chrono::milliseconds delay(10);
            auto func = [delay](){ std::this_thread::sleep_for(delay); };
            unsigned iterations = 2;

            auto stats = timeit::all(func, iterations);

            ASSERT_TRUE(stats.average < stats.total);
        }

        TEST_METHOD(AllShouldReturnMinLessThanMax)
        {
            auto delay = std::chrono::milliseconds(10);
            auto func = [&delay]{ std::this_thread::sleep_for(delay); delay *= 2; };
            unsigned iterations = 3;

            auto stats = timeit::all(func, iterations);

            ASSERT_TRUE(stats.min < stats.max);
        }

        TEST_METHOD(MinShouldAlwaysBeNonNegative)
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