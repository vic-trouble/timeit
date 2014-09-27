/*

// TODO: API for total, average, min, max
// TODO: disclaimer
// TODO: CMake
// TODO: CTest
// TODO: travis
// TODO: const function &

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

  };
}