#pragma once

/*!
 * @file
 * Argument types for Ragf instructions
 */

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

/*!
 * @brief Struct representing a memory dereference
 *
 * PtrReg used to express dereferenced memory location
 * at some displacement.
 */
struct PtrReg {
  //! @brief Register that contains base address
  Reg ptr;
  //! @brief Byte size of element pointed to
  int obj_size;
  //! @brief Positive or negative displacement in bytes
  int disp;
};

//! @brief Immutable pseudo register that holds data pointer
struct DataReg{};

//! @brief Immediate argument. Always 64 bit wide
typedef i64 Imm;
