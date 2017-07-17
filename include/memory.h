#ifndef JAKALIB__MEMORY_H
#define JAKALIB__MEMORY_H

#include <memory>
#include <type_traits>

namespace jakalib {

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(size_t size) {
  return std::unique_ptr<T>(new typename std::remove_extent<T>::type[size]());
}

// Does not participate when T is an array type with known bound.
template <typename T, typename... Args>
typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

} // namespace jakalib

#endif
