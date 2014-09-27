/*

// TODO: API for total, average, min, max
// TODO: specify duration traits
// TODO: disclaimer
// TODO: CMake
// TODO: CTest
// TODO: travis
// TODO: inline

// TEST: throw on empty func

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

  };
}