#ifndef JAKALIB_MATH_H
#define JAKALIB_MATH_H

#include <algorithm>
#include <cmath>

namespace jakalib {
namespace detail {
template <typename T>
T sqr(T x) {
  return x * x;
}

template <typename T>
T hypot3(T x, T y, T z) {
  x = std::abs(x);
  y = std::abs(y);
  z = std::abs(z);

  T m = std::max(std::max(x, y), z);
  if (m == T(0)) {
    return T(0);
  }
  T m_inv = T(1.0) / m;
  return m * std::sqrt(sqr(x * m_inv) + sqr(y * m_inv) + sqr(z * m_inv));
}
}  // namespace detail

// Computes the square root of the sum of the squares of x, y and z, without
// undue overflow or underflow at intermediate stages of the computation.
inline float hypot(float x, float y, float z) {
  return detail::hypot3<float>(x, y, z);
}

inline double hypot(double x, double y, double z) {
  return detail::hypot3<double>(x, y, z);
}

inline long double hypot(long double x, long double y, long double z) {
  return detail::hypot3<long double>(x, y, z);
}
}  // namespace jakalib
#endif
