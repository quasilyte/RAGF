#pragma once

#include <core/typedefs.hpp>

struct RegIndex {
  constexpr RegIndex(uint val): $val{val} {}

  constexpr operator uint() const noexcept {
    return $val;
  }

  uint $val;
};
