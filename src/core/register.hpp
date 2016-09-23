#pragma once

#include <core/typedefs.hpp>

struct Register {
  constexpr Register(uint id): $id{id} {}

  constexpr operator uint() const noexcept {
    return $id;
  }

  uint $id;
};
