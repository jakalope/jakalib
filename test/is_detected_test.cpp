#include "jakalib/type_traits.h"

using namespace jakalib;

/**
 * Test copy assignment detection.
 *
 * Origin:
 *   http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4502.pdf
 */

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

/**
 * Test member detection.
 */

template <typename T>
using foo_member_op = decltype(std::declval<T&>().foo());

template <typename T>
using has_foo = is_detected<foo_member_op, T>;

template <typename T>
using has_int_foo = is_detected_exact<int, foo_member_op, T>;

template <typename T>
using has_int_compatible_foo = is_detected_convertible<int, foo_member_op, T>;

// Example usage.
template <typename T>
int invokeFoo(T t) {
  static_assert(has_int_compatible_foo<T>::value,
                "T must have an int-compatible member foo()");
  return t.foo();
}

struct no_foo {};

struct int_foo {
  int foo() {
    return 1;
  }
};

struct long_foo {
  long foo() {
    return 1l;
  }
};

struct pointer_foo {
  void* foo() {
    return nullptr;
  }
};

struct int_foo_with_arg {
  int foo(int x) {
    return x;
  }
};

//
// is_detected test
//

template <bool expected, typename TypeUnderTest>
constexpr bool expectedHasFoo() {
  return has_foo<TypeUnderTest>::value == expected;
}

static_assert(expectedHasFoo<false, no_foo>(), "");
static_assert(expectedHasFoo<true, int_foo>(), "");
static_assert(expectedHasFoo<true, long_foo>(), "");
static_assert(expectedHasFoo<true, pointer_foo>(), "");
static_assert(expectedHasFoo<false, int_foo_with_arg>(), "");

//
// is_detected_exact test
//

template <bool expected, typename TypeUnderTest>
constexpr bool expectedHasIntFoo() {
  return has_int_foo<TypeUnderTest>::value == expected;
}

static_assert(expectedHasIntFoo<false, no_foo>(), "");
static_assert(expectedHasIntFoo<true, int_foo>(), "");
static_assert(expectedHasIntFoo<false, long_foo>(), "");
static_assert(expectedHasIntFoo<false, pointer_foo>(), "");
static_assert(expectedHasIntFoo<false, int_foo_with_arg>(), "");

//
// is_detected_convertible test
//

template <bool expected, typename TypeUnderTest>
constexpr bool expectedHasIntCompatFoo() {
  return has_int_compatible_foo<TypeUnderTest>::value == expected;
}

static_assert(expectedHasIntCompatFoo<false, no_foo>(), "");
static_assert(expectedHasIntCompatFoo<true, int_foo>(), "");
static_assert(expectedHasIntCompatFoo<true, long_foo>(), "");
static_assert(expectedHasIntCompatFoo<false, pointer_foo>(), "");
static_assert(expectedHasIntCompatFoo<false, int_foo_with_arg>(), "");

int main() {
  return 0;
}
