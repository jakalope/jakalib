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
// invoke_result
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/types/result_of&oldid=94402

namespace detail {

template <class F, class... Args>
inline auto INVOKE(F&& f, Args&&... args)
    -> decltype(std::forward<F>(f)(std::forward<Args>(args)...));

template <class Base, class T, class Derived>
inline auto INVOKE(T Base::*pmd, Derived&& ref)
    -> decltype(std::forward<Derived>(ref).*pmd);

template <class PMD, class Pointer>
inline auto INVOKE(PMD&& pmd, Pointer&& ptr)
    -> decltype((*std::forward<Pointer>(ptr)).*pmd);

template <class Base, class T, class Derived, class... Args>
inline auto INVOKE(T Base::*pmf, Derived&& ref, Args&&... args)
    -> decltype((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...));

template <class PMF, class Pointer, class... Args>
inline auto INVOKE(PMF&& pmf, Pointer&& ptr, Args&&... args)
    -> decltype(((*std::forward<Pointer>(ptr)).*
                 pmf)(std::forward<Args>(args)...));

} // namespace detail

// Conforming C++14 implementation (is also a valid C++11 implementation):
namespace detail {
template <typename AlwaysVoid, typename, typename...>
struct invoke_result {};

template <typename F, typename... Args>
struct invoke_result<decltype(void(detail::INVOKE(std::declval<F>(),
                                                  std::declval<Args>()...))),
                     F,
                     Args...> {
  using type =
      decltype(detail::INVOKE(std::declval<F>(), std::declval<Args>()...));
};
} // namespace detail

template <class>
struct result_of;

template <class F, class... ArgTypes>
struct result_of<F(ArgTypes...)> : detail::invoke_result<void, F, ArgTypes...> {
};

template <class F, class... ArgTypes>
struct invoke_result : detail::invoke_result<void, F, ArgTypes...> {};

//
// invoke
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/utility/functional/invoke&oldid=93823

namespace detail {

template <class T>
struct is_reference_wrapper : std::false_type {};

template <class U>
struct is_reference_wrapper<std::reference_wrapper<U>> : std::true_type {};

} // namespace detail

template <class F, class... Args>
typename invoke_result<F, Args...>::type invoke(F&& f, Args&&... args) {
  return detail::INVOKE(std::forward<F>(f), std::forward<Args>(args)...);
}

// We need this version because we don't have access to
// std::is_nothrow_invocable().
template <class F, class... Args>
typename invoke_result<F, Args...>::type
invoke_noexcept(F&& f, Args&&... args) noexcept {
  return detail::INVOKE(std::forward<F>(f), std::forward<Args>(args)...);
}

//
// nonesuch
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/experimental/nonesuch&oldid=92946

struct nonesuch {
  nonesuch() = delete;
  ~nonesuch() = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};

//
// void_t
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/types/void_t&oldid=89901

template <typename... Ts>
struct make_void final {
  typedef void type;
};

template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

//
// is_detected
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/experimental/is_detected&oldid=93627

namespace detail {
template <class Default,
          class AlwaysVoid,
          template <class...> class Op,
          class... Args>
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

//
// is_invocable
//

// template <class Fn, class... ArgTypes>
// struct is_invocable
//     : public ::jakalib::bool_constant<::jakalib::is_detected<detail::INVOKE(
//           std::declval<Fn>(), std::declval<ArgTypes>()...)>::value> {};

//
// conditional_t
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/types/conditional&oldid=93742

template <bool B, class T, class F>
using conditional_t = typename std::conditional<B, T, F>::type;

//
// conjunction
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/types/conjunction&oldid=91238

template <class...>
struct conjunction : std::true_type {};

template <class B1>
struct conjunction<B1> : B1 {};

template <class B1, class... Bn>
struct conjunction<B1, Bn...>
    : conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};

//
// disjunction
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/types/disjunction&oldid=93002

template <class...>
struct disjunction : std::false_type {};

template <class B1>
struct disjunction<B1> : B1 {};

template <class B1, class... Bn>
struct disjunction<B1, Bn...>
    : conditional_t<bool(B1::value), B1, disjunction<Bn...>> {};

//
// negation
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/types/negation&oldid=92789

template <class B>
struct negation : bool_constant<!bool(B::value)> {};

//
// not_fn_t
//
// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/experimental/not_fn&oldid=84480

namespace detail {

template <class F>
struct not_fn_t {
  F f;

  template <class... Args>
  auto operator()(Args&&... args) noexcept(
      noexcept(!::jakalib::invoke(f, std::forward<Args>(args)...)))
      -> decltype(!::jakalib::invoke(f, std::forward<Args>(args)...)) {
    return !::jakalib::invoke(f, std::forward<Args>(args)...);
  }

  template <class... Args>
  auto operator()(Args&&... args) const
      noexcept(noexcept(!::jakalib::invoke(f, std::forward<Args>(args)...)))
          -> decltype(!::jakalib::invoke(f, std::forward<Args>(args)...)) {
    return !::jakalib::invoke(f, std::forward<Args>(args)...);
  }

  template <class... Args>
  auto operator()(Args&&... args) volatile noexcept(
      noexcept(!::jakalib::invoke(f, std::forward<Args>(args)...)))
      -> decltype(!::jakalib::invoke(f, std::forward<Args>(args)...)) {
    return !::jakalib::invoke(f, std::forward<Args>(args)...);
  }

  template <class... Args>
  auto operator()(Args&&... args) const volatile noexcept(
      noexcept(!::jakalib::invoke(f, std::forward<Args>(args)...)))
      -> decltype(!::jakalib::invoke(f, std::forward<Args>(args)...)) {
    return !::jakalib::invoke(f, std::forward<Args>(args)...);
  }
};

} // namespace detail

template <class F>
detail::not_fn_t<::jakalib::decay_t<F>> not_fn(F&& f) {
  return {std::forward<F>(f)};
}

} // namespace jakalib

#endif
