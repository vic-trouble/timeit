/*

// TODO: disclaimer
// TODO: CMake
// TODO: CTest
// TODO: travis

*/
#include "stdafx.h"
#include "CppUnitTest.h"

#include <thread>

#include <timeit/timeit.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
  TEST_CLASS(TimeIt)
  {
  public:

    TEST_METHOD(TotalShouldCallFunc)
    {
      bool called = false;
      auto empty = [&called](){ called = true; };

      auto elapsed = timeit::total(empty);

      Assert::IsTrue(called);
    }

    TEST_METHOD(TotalShouldReturnNotLessThan10msWhen10msFunc)
    {
      std::chrono::milliseconds delay(10);
      auto func = [delay](){ std::this_thread::sleep_for(delay); };

      auto elapsed = timeit::total(func);

      Assert::IsTrue(elapsed >= delay);
    }

    TEST_METHOD(TotalShouldReturnNotLessThan20msWhen10msFuncAnd2Iterations)
    {
      std::chrono::milliseconds delay(10);
      auto func = [delay](){ std::this_thread::sleep_for(delay); };

      auto elapsed = timeit::total(func, 2);

      Assert::IsTrue(elapsed >= 2 * delay);
    }

    TEST_METHOD(TotalShouldCallFuncExactlyNumberOfIterations)
    {
      unsigned iterations = 1000, times = 0;
      auto func = [&times](){ ++times; };

      timeit::total(func, iterations);

      Assert::AreEqual(iterations, times);
    }

    TEST_METHOD(TotalShouldReturnNotLessThan10000usWhen10msFunc)
    {
      std::chrono::milliseconds delay(10);
      std::chrono::microseconds delay_us(10 * 1000);
      auto func = [delay](){ std::this_thread::sleep_for(delay); };

      auto elapsed = timeit::total<std::chrono::microseconds>(func);

      Assert::IsTrue(elapsed >= delay_us);
    }

    TEST_METHOD(TotalShouldThrowWhenEmptyFunc)
    {
      std::function<void()> empty;

      Assert::ExpectException<std::invalid_argument>([&](){ timeit::total(empty); });
    }

    TEST_METHOD(AverageShouldReturnLessThanTotalWhenMultipleIterations)
    {
      std::chrono::milliseconds delay(10);
      auto func = [delay](){ std::this_thread::sleep_for(delay); };
      unsigned iterations = 2;

      auto total = timeit::total(func, iterations);
      auto avg = timeit::average(func, iterations);

      Assert::IsTrue(avg < total);
    }

    TEST_METHOD(AverageShouldThrowWhenEmptyFunc)
    {
      std::function<void()> empty;

      Assert::ExpectException<std::invalid_argument>([&](){ timeit::average(empty); });
    }

    TEST_METHOD(MinMaxShouldReturnMinLessThanMax)
    {
      auto delay = std::chrono::milliseconds(10);
      auto func = [&delay]{ std::this_thread::sleep_for(delay); delay *= 2; };
      unsigned iterations = 3;

      std::chrono::milliseconds min{}, max{};
      std::tie(min, max) = timeit::minmax(func, iterations);

      Assert::IsTrue(min < max);
    }

    TEST_METHOD(MinMaxShouldThrowWhenEmptyFunc)
    {
      std::function<void()> empty;

      Assert::ExpectException<std::invalid_argument>([&](){ timeit::minmax(empty); });
    }

    TEST_METHOD(MinShouldThrowWhenEmptyFunc)
    {
      std::function<void()> empty;

      Assert::ExpectException<std::invalid_argument>([&](){ timeit::min(empty); });
    }

    TEST_METHOD(MaxShouldThrowWhenEmptyFunc)
    {
      std::function<void()> empty;

      Assert::ExpectException<std::invalid_argument>([&](){ timeit::max(empty); });
    }

  };
}