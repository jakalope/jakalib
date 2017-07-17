# Jakalib
## A C++11 Implementation of nice-to-have C++14/17/TS libraries

I really like a lot of the new features coming out in C++ and many of them can be enabled without additional core language features. This library is just a collection of (mostly other people's) implementations of the features I want.

I do my best to cite sources for implementations, which I do by commenting above it with something like:

```cpp
// Origin:
// https://cppreference.com/wiki/the_thing.html

class TheThing {};
```

## Hypothetically FAQ

I take it I'll get very few questions as a result of not bringing any attention to myself. Thus, a true FAQ would be very short.

### Why not just use Boost?

In many cases, Boost has similar implementations. However, since a lot of those implementations were earlier incarnations of what eventually became C++ TSes, their interfaces differ slightly from what eventually becomes ISO. They (rightly) don't want to change the interfaces their own users already use.
