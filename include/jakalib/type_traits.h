#ifndef JAKALIB__TYPE_TRAITS_H
#define JAKALIB__TYPE_TRAITS_H

#include <functional>
#include <type_traits>

namespace jakalib {

//
// bool_constant
//

template <bool v>
struct bool_constant {
  static constexpr bool value = v;

  typedef bool value_type;
  typedef bool_constant type;

  constexpr operator value_type() const noexcept {
    return value;
  }

  constexpr value_type operator()() const noexcept {
    return value;
  }
};

//
// decay_t
//

template <typename T>
using decay_t = typename std::decay<T>::type;

//
// Detection Idiom: void_t, is_detected
// Origin: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4502.pdf
//

struct nonesuch {
  nonesuch() = delete;
  ~nonesuch() = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};

template <typename... T>
using void_t = void;

namespace detail {
template <class Default, class, template <class...> class Op, class... Args>
struct detector final {
  using value_t = std::false_type;
  using type = Default;
};

template <class Default, template <class...> class Op, class... Args>
struct detector<Default, void_t<Op<Args...>>, Op, Args...> final {
  using value_t = std::true_type;
  using type = Op<Args...>;
};
} // namespace detail

template <template <class...> class Op, class... Args>
using is_detected =
    typename detail::detector<nonesuch, void, Op, Args...>::value_t;

template <template <class...> class Op, class... Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

template <class Default, template <class...> class Op, class... Args>
using detected_or = detail::detector<Default, void, Op, Args...>;

template <class Expected, template <class...> class Op, class... Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

template <class Default, template <class...> class Op, class... Args>
using detected_or_t = typename detected_or<Default, Op, Args...>::type;

} // namespace jakalib

#endif
