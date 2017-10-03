#include "jakalib/type_traits.h"

#include <cassert>
#include <array>
#include <vector>

using namespace jakalib;

/**
 * Test for STL container size.
 */

static_assert(size(std::array<int, 3>{1, 2, 3}) == 3,
              "Size of STL container is not correct");
static_assert(size(std::array<int, 0>()) == 0,
              "Size of empty STL container is not correct");

void vectorSizeTest() {
  assert(size(std::array<int, 3>{1, 2, 3}) == 3);
  assert(size(std::array<int, 0>()) == 0);
}

/**
 * Test for array size.
 */

static int array[3];
static_assert(size(array) == 3,
              "Size of native array is not correct");

int main() {
  vectorSizeTest();

  return 0;
}
