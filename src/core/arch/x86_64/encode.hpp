#pragma once

/*!
 * @file
 * x86_64 instruction encoding helpers
 */

#include <core/typedefs.hpp>
#include <core/args.hpp>

//! @brief REX prefix from single value
constexpr byte rex(uint val) noexcept {
  return (0b0100 << 4) + val;
}

//! @brief REX prefix from 4 parts
constexpr byte rex(uint w, uint r, uint x, uint b) noexcept {
  return (0b0100 << 4) + ((w << 3) + (r << 2) + (x << 1) + b);
}

//! @brief MOD REG R/M encoding from 3 parts
constexpr byte mod_reg_rm(uint mod, uint reg, uint rm) noexcept {
  return (mod << 6) + (reg << 3) + rm;
}

//! @brief 1 byte opcode; index can be used for /r modifier
constexpr byte opcode(uint val, Reg index = 0) noexcept {
  return val + index;
}

//! @brief 2 byte opcode; For x86_64 1 byte is always 0x0F
constexpr u16 opcode(uint b1, uint b2) noexcept {
  return b1 + (b2 << 8);
}

