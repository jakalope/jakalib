#include "jakalib/span.h"


bool simple_test() {
  int nums[3] = {0, 1, 2};
  jakalib::span<int> sp(nums, 3);
  return sp.size() == 3;
};

int main() {
  bool success = true;

  success = success && simple_test();

  if (success) {
    return 0;
  }
  return 1;
}
