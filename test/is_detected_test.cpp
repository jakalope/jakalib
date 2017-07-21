#include "jakalib/type_traits.h"

using namespace jakalib;

template <typename T>
using copy_assign_op = decltype(std::declval<T&>() = std::declval<const T&>());

template <typename T>
using copy_assignable = is_detected<copy_assign_op, T>;

template <typename T>
using canonically_copy_assignable = is_detected_exact<T&, copy_assign_op, T>;

struct foo {};

struct bar {
  bar& operator=(const bar&) = delete;
};

struct car {
  void operator=(const car&) {}
};

static_assert(copy_assignable<foo>::value, "foo is not copy assignable");

static_assert(!copy_assignable<bar>::value, "bar is copy assignable");

static_assert(!canonically_copy_assignable<car>::value,
              "car is canonically copy assignable");

// Inspired by:
// https://github.com/fuchsia-mirror/third_party-libcxx/blob/master/test/std/
//   experimental/utilities/meta/meta.detect/is_detected_convertible.pass.cpp

template <typename T>
using call_foo = decltype(std::declval<T&>().foo());

template <typename T>
using has_int_compatible_foo = is_detected_convertible<int, call_foo, T>;

template <typename T>
int invokeFoo(T t) {
  static_assert(has_int_compatible_foo<T>::value,
                "T must have an int-compatible member foo()");
  return t.foo();
}

struct an_int {
  int foo() {
    return 1;
  }
};

struct a_long {
  long foo() {
    return 1l;
  }
};

struct a_nullptr {
  void* foo() {
    return nullptr;
  }
};

static_assert(!has_int_compatible_foo<a_nullptr>::value,
              "void* should not be convertible to int.");

int x = invokeFoo(an_int());
int y = invokeFoo(a_long());

int main() {
  return 0;
}
