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

    TEST_METHOD(AllShouldCallFunc)
    {
      bool called = false;
      auto empty = [&called](){ called = true; };

      timeit::all(empty);

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

    TEST_METHOD(AllShouldCallFuncExactlyNumberOfIterations)
    {
      unsigned iterations = 1000, times = 0;
      auto func = [&times](){ ++times; };

      timeit::all(func, iterations);

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

      Assert::IsTrue(stats.average < stats.total);
    }

    TEST_METHOD(AllShouldReturnMinLessThanMax)
    {
      auto delay = std::chrono::milliseconds(10);
      auto func = [&delay]{ std::this_thread::sleep_for(delay); delay *= 2; };
      unsigned iterations = 3;

      auto stats = timeit::all(func, iterations);

      Assert::IsTrue(stats.min < stats.max);
    }

  };
}