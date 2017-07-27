#ifndef JAKALIB__TYPE_TRAITS_H
#define JAKALIB__TYPE_TRAITS_H

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

/* Detection Idiom: void_t, nonesuch, is_detected
 *
 * Origin:
 *   http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4502.pdf
 *   https://gist.github.com/remyroez/6a6ac795452f8ec32b6d617bd6c8d946
 *
 * Example usage
 *
 * template <typename T>
 * using copy_assign_op =
 *     decltype(std::declval<T &>() = std::declval<const T &>());
 *
 * template <typename T>
 * using copy_assignable = is_detected<copy_assign_op, T>;
 *
 * struct foo {};
 * struct bar { bar &operator =(const bar &) = delete; };
 *
 * int main()
 * {
 *   static_assert( copy_assignable<foo>::value, "foo is not copy assignable");
 *   static_assert(!copy_assignable<bar>::value, "bar is copy assignable");
 *   return 0;
 * }
 */

#if (__cplusplus > 201402L)

using std::void_t;

#else

template <typename... Ts>
struct void_sink {
  using type = void;
};

template <typename... Ts>
using void_t = typename void_sink<Ts...>::type;

#endif

template <class, template <class> class, class = void_t<>>
struct detect : std::false_type {};

template <class T, template <class> class Op>
struct detect<T, Op, void_t<Op<T>>> : std::true_type {};

template <class T, class Void, template <class...> class Op, class... Args>
struct detector {
  using value_t = std::false_type;
  using type = T;
};

template <class T, template <class...> class Op, class... Args>
struct detector<T, void_t<Op<Args...>>, Op, Args...> {
  using value_t = std::true_type;
  using type = Op<Args...>;
};

struct nonesuch final {
  nonesuch() = delete;
  ~nonesuch() = delete;
  nonesuch(const nonesuch&) = delete;
  void operator=(const nonesuch&) = delete;
};

template <class T, template <class...> class Op, class... Args>
using detected_or = detector<T, void, Op, Args...>;

template <class T, template <class...> class Op, class... Args>
using detected_or_t = typename detected_or<T, Op, Args...>::type;

template <template <class...> class Op, class... Args>
using detected = detected_or<nonesuch, Op, Args...>;

template <template <class...> class Op, class... Args>
using detected_t = typename detected<Op, Args...>::type;

template <template <class...> class Op, class... Args>
using is_detected = typename detected<Op, Args...>::value_t;

template <class Result, template <class...> class Op, class... Args>
using is_detected_exact = std::is_same<Result, detected_t<Op, Args...>>;

template <class Result, template <class...> class Op, class... Args>
using is_detected_convertible =
    std::is_convertible<detected_t<Op, Args...>, Result>;

} // namespace jakalib

#endif
