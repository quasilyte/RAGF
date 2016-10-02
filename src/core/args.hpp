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
 * Mem used to express dereferenced memory location
 * at some index.
 * Index + byte count are used to produce proper displacement.
 */
struct Mem {
  //! @brief Register that contains base address
  Reg ptr;
  //! @brief Byte size of each memory cell (used for indexind)
  int byte_count;
  //! @brief Positive or negative index to be dereferenced
  int index;

  //! @brief Calculates displacement
  int disp() const { return byte_count * index; }
};

//! @brief Immutable pseudo register that holds data pointer
struct DataReg{};

//! @brief Immediate argument. Always 64 bit wide
typedef i64 Imm;
