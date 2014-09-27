/*

// TODO: API for total, average, min, max
// TODO: specify duration traits
// TODO: disclaimer
// TODO: specify iterations
// TODO: CMake
// TODO: CTest
// TODO: travis

// TEST: time >= 0
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

    TEST_METHOD(ShouldCallFunc)
    {
      bool called = false;
      auto empty = [&called](){ called = true; };

      auto elapsed = timeit::total(empty);

      Assert::IsTrue(called);
    }

    TEST_METHOD(ShouldReturnNotLessThan10msWhen10msFunc)
    {
      std::chrono::milliseconds delay(10);
      auto func = [delay](){ std::this_thread::sleep_for(delay); };

      auto elapsed = timeit::total(func);

      Assert::IsTrue(elapsed >= delay);
    }

  };
}