#pragma once

#include <core/typedefs.hpp>

struct Gpr {
  constexpr Gpr(uint id): $id{id} {}

  constexpr operator uint() const noexcept {
    return $id;
  }

  uint $id;
};
