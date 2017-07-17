#ifndef JAKALIB__STRING_H
#define JAKALIB__STRING_H

#include <string>

namespace jakalib {

// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/experimental/basic_string/erase&oldid=79325

template <class charT, class traits, class A, class U>
void erase(std::basic_string<charT, traits, A>& c, const U& value) {
  c.erase(std::remove(c.begin(), c.end(), value), c.end());
}

// Origin:
// http://en.cppreference.com/mwiki/
//     index.php?title=cpp/experimental/basic_string/erase_if&oldid=79336

template <class CharT, class Traits, class Alloc, class Predicate>
void erase_if(std::basic_string<CharT, Traits, Alloc>& c, Predicate pred) {
  c.erase(std::remove_if(c.begin(), c.end(), pred), c.end());
}

} // namespace jakalib

#endif
