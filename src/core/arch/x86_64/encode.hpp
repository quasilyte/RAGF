#pragma once

#include <core/typedefs.hpp>
#include <core/reg_index.hpp>

constexpr byte rex(uint val) noexcept {
  return (0b0100 << 4) + val;
}

constexpr byte rex(uint w, uint r, uint x, uint b) noexcept {
  return (0b0100 << 4) + ((w << 3) + (r << 2) + (x << 1) + b);
}

constexpr byte mod_reg_rm(uint mod, uint reg, uint rm) noexcept {
  return (mod << 6) + (reg << 3) + rm;
}

constexpr byte opcode(uint val, RegIndex index = 0) noexcept {
  return val + index;
}

constexpr u16 opcode(uint b1, uint b2) noexcept {
  return b1 + (b2 << 8);
}

