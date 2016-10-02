#pragma once

/*!
 * @file
 * Utility finctions to work with numerics
 */

#include <core/typedefs.hpp>

//! @brief Enum representing actual size needed to store numeric value
enum class Size {
  BYTE,  // 1 byte
  WORD,  // 2 bytes
  DWORD, // 4 bytes
  QWORD  // 8 bytes
};

bool fits_i8(i64) noexcept;
bool fits_i16(i64) noexcept;
bool fits_i32(i64) noexcept;
bool fits_u8(u64) noexcept;
bool fits_u16(u64) noexcept;
bool fits_u32(u64) noexcept;

Size min_width(i64) noexcept;
Size min_width(u64) noexcept;

