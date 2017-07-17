#ifndef JAKALOPE__TYPE_TRAITS_H
#define JAKALOPE__TYPE_TRAITS_H

#include <type_traits>

namespace jakalope {

// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/experimental/nonesuch&oldid=92946

struct nonesuch {
  nonesuch() = delete;
  ~nonesuch() = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};

// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/types/void_t&oldid=89901

template <typename... Ts>
struct make_void {
  typedef void type;
};

template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/experimental/is_detected&oldid=93627

namespace detail {
template <class Default,
          class AlwaysVoid,
          template <class...> class Op,
          class... Args>
struct detector {
  using value_t = std::false_type;
  using type = Default;
};

template <class Default, template <class...> class Op, class... Args>
struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
  // Note that std::void_t is a C++17 feature
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

} // namespace jakalope

#endif
