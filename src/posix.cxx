#include "impl.hpp"

#if defied(__ELF__) and __ELF__
  #define SESSION_IMPL_SECTION ".init_array"
  #define SESSION_IMPL_ELF 1
#elif defined(__MACH__) and __MACH__
  #define SESSION_IMPL_SECTION "__DATA,__mod_init_func"
  #define SESSION_IMPL_ELF 0
#endif

namespace {

char const** argv__ { };
int argc__ { };

[[gnu::section(SESSION_IMPL_SECTION)]]
auto init = +[] (int argc, char const** argv, char const**) {
  argv__ = argv;
  argc__ = argc;
  if constexpr(SESSION_IMPL_ELF) { return 0; }
};

} /* nameless namespace */

extern "C" char** environ;

namespace impl {

char const* argv (std::size_t idx) noexcept { return argv__[idx]; }
int argc () noexcept { return argc__; }

char const** envp () noexcept { return environ; }

} /* namespace impl */
