#include "jakalib/variant.h"

static_assert(jakalib::variant_size<jakalib::variant<>>::value == 0, "");
static_assert(jakalib::variant_size<jakalib::variant<int>>::value == 1, "");
static_assert(jakalib::variant_size<jakalib::variant<int, double>>::value == 2,
              "");

bool simple_test() {
  static constexpr jakalib::variant<int, double> u = 1;
  static_assert(u.index() == 0, "");
  return jakalib::get<0>(u) == 1;
};

int main() {
  bool success = true;

  success = success && simple_test();

  if (success) {
    return 0;
  }
  return 1;
}
