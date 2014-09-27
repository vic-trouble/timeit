/*

// TODO: API for total, average, min, max
// TODO: specify duration traits
// TODO: disclaimer
// TODO: specify iterations
// TODO: CMake
// TODO: CTest
// TODO: travis

*/
#include "stdafx.h"
#include "CppUnitTest.h"

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

  };
}