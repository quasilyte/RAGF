#pragma once

#include <core/typedefs.hpp>

struct Reg {
  constexpr Reg(byte id): $id{id} {}

  constexpr operator byte() const noexcept {
    return $id;
  }

  byte $id;
};

struct UintReg: Reg {
  using Reg::Reg;
};

struct IntReg: Reg {
  using Reg::Reg;
};
