#pragma once

#include <core/typedefs.hpp>

namespace priv {
  constexpr uint label(int step, Token x) {
    return (static_cast<uint>(x) << (step * 8));
  }

  template<class... ARGS>
  constexpr uint label(int step, Token x, ARGS... ys) {
    return label(step, x) + label(step + 1, ys...);
  }
}

template<class... ARGS>
constexpr uint label(ARGS... args) {
  return priv::label(0, args...);
}
