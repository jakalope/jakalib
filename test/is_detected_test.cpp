// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/experimental/is_detected&oldid=93627
//

#include "../include/type_traits.h"
#include <cstddef>

template <class T>
using copy_assign_t = decltype(std::declval<T&>() = std::declval<const T&>());

struct Meow {};
struct Purr {
  void operator=(const Purr&) = delete;
};

static_assert(jakalib::is_detected<copy_assign_t, Meow>::value,
              "Meow should be copy assignable!");
static_assert(!jakalib::is_detected<copy_assign_t, Purr>::value,
              "Purr should not be copy assignable!");
static_assert(jakalib::is_detected_exact<Meow&, copy_assign_t, Meow>::value,
              "Copy assignment of Meow should return Meow&!");

template <class T>
using diff_t = typename T::difference_type;

template <class Ptr>
using difference_type = jakalib::detected_or_t<std::ptrdiff_t, diff_t, Ptr>;

struct Woof {
  using difference_type = int;
};
struct Bark {};

static_assert(std::is_same<difference_type<Woof>, int>::value,
              "Woof's difference_type should be int!");
static_assert(std::is_same<difference_type<Bark>, std::ptrdiff_t>::value,
              "Bark's difference_type should be ptrdiff_t!");

int main() {
  return 0;
}
