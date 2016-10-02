#pragma once

#include <core/typedefs.hpp>

/*!
 * @brief Untyped fixnum register
 */
struct Reg {
  constexpr Reg(byte id): $id{id} {}

  constexpr operator byte() const noexcept {
    return $id;
  }

  //! @brief Register id/index; basically (0..7)
  byte $id;
};

//! @brief Register interpreted as unsigned int type
struct UintReg: Reg {
  using Reg::Reg;
};

//! @brief Register interpreted as signed int type
struct IntReg: Reg {
  using Reg::Reg;
};
