#pragma once

#include <core/reg.hpp>

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
