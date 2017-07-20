#include "jakalib/type_traits.h"

using namespace jakalib;

template <typename T>
using copy_assign_op = decltype(std::declval<T&>() = std::declval<const T&>());

template <typename T>
using copy_assignable = is_detected<copy_assign_op, T>;

template <typename T>
using canonically_copy_assignable = is_detected_exact<T&, copy_assign_op, T>;

// template <typename T, typename... Args>
// using binary_op =
// decltype(std::declval<T>.operator()(std::declval<Args>()...));

// template <typename T>
// using is_binary_op = is_detected_convertible<bool, binary_op, T>;

struct foo {};

struct bar {
  bar& operator=(const bar&) = delete;
};

struct car {
  void operator=(const car&) {}
};

struct BinaryFunctor {
  bool operator()() {
    return true;
  }
};

int main() {
  static_assert(copy_assignable<foo>::value, "foo is not copy assignable");

  static_assert(!copy_assignable<bar>::value, "bar is copy assignable");

  static_assert(!canonically_copy_assignable<car>::value,
                "car is canonically copy assignable");
  // static_assert(is_binary_op<BinaryFunctor>::value,
  //               "BinaryFunctor isn't a binary operator");
  return 0;
}
