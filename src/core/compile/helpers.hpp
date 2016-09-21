#pragma once

#include <core/typedefs.hpp>

namespace priv {
  constexpr uint label(int step, Token t) {
    return (static_cast<uint>(t) << (step * 8));
  }

  template<class... ARGS>
  constexpr uint label(int step, Token head, ARGS... tail) {
    return label(step, head) + label(step + 1, tail...);
  }
}

template<class... ARGS>
constexpr uint label(ARGS... tokens) {
  return priv::label(0, tokens...);
}
