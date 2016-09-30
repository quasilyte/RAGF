#pragma once

#include <core/typedefs.hpp>

enum class Size {
  BYTE,
  WORD,
  DWORD,
  QWORD
};

bool fits_i8(i64) noexcept;
bool fits_i16(i64) noexcept;
bool fits_i32(i64) noexcept;
bool fits_u8(u64) noexcept;
bool fits_u16(u64) noexcept;
bool fits_u32(u64) noexcept;

Size min_width(i64) noexcept;
Size min_width(u64) noexcept;

