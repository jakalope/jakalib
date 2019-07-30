#include "jakalib/math.h"

using namespace jakalib;

#define assert_close(actual, expected)                                         \
  do {                                                                         \
    auto _0 = actual;                                                          \
    auto _1 = expected;                                                        \
    assert(std::abs(_0 - _1) < 1e-10);                                         \
  } while (false)

void hypotTest() {
  assert_close(hypot(0.0, 0.0, 0.0), 0.0);
  assert_close(hypot(3.0, 4.0, 0.0), 5.0);
  assert_close(hypot(0.0, -3.0, 4.0), 5.0);
  assert_close(hypot(-3.0, 0.0, 4.0), 5.0);
  assert_close(hypot(2.0, -7.0, 26.0), 27.0);
  assert_close(hypot(-0.2, 0.7, -2.6), 2.7);

  long double x =
      std::numeric_limits<long double>::max() / 2.12345678901234567890l;
  assert_close(hypot(x, 0.0l, 0.0l), x);
  assert_close(hypot(x, x, 0.0l), x * std::sqrt(2.0l));
  assert_close(hypot(x, x, x), x * std::sqrt(3.0l));
  assert_close(hypot(-x, x, x), x * std::sqrt(3.0l));
  assert_close(hypot(-x, -x, x), x * std::sqrt(3.0l));
  assert_close(hypot(-x, -x, -x), x * std::sqrt(3.0l));
  assert_close(hypot(1.0 / x, 0.0l, 0.0l), 1.0l / x);
}

int main() {
  hypotTest();
  return 0;
}
