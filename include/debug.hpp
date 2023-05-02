#ifndef ZEN_DEBUG_HPP
#define ZEN_DEBUG_HPP

#include <cstdio>

namespace Zen::Debug {

/**
 * Dumps a structure to stdout.
 *
 * @warning This function is a nop on all compilers but clang.
 */
template <typename T> auto dump_struct(T &strct) -> void {
#if defined(__clang__)
  __builtin_dump_struct(&strct, printf);
#else
#warning "Zen::dump_struct is a nop on this compiler."
#endif
}

} // namespace Zen::Debug

#endif // ZEN_DEBUG_HPP
