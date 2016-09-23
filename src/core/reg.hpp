#pragma once

#include <core/typedefs.hpp>

struct Reg {
  constexpr Reg(uint id): $id{id} {}

  constexpr operator uint() const noexcept {
    return $id;
  }

  uint $id;
};
