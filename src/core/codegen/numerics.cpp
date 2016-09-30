#include <core/codegen/numerics.hpp>

static const i64 i32_max = 0xffffffff >> 1;
static const i64 i16_max = 0xffff     >> 1;
static const i64 i8_max  = 0xff       >> 1;
static const i64 i32_min = -i32_max - 1;
static const i64 i16_min = -i16_max - 1;
static const i64 i8_min  = -i8_max  - 1;

static const u64 u32_max = 0xffffffff;
static const u64 u16_max = 0xffff;
static const u64 u8_max  = 0xff;

bool fits_i8 (i64 x) noexcept { return x > i8_min  && x < i8_max; }
bool fits_i16(i64 x) noexcept { return x > i16_min && x < i16_max; }
bool fits_i32(i64 x) noexcept { return x > i32_min && x < i32_max; }

bool fits_u8 (u64 x) noexcept { return x < u8_max; }
bool fits_u16(u64 x) noexcept { return x < u16_max; }
bool fits_u32(u64 x) noexcept { return x < u32_max; }

Size min_width(i64 x) noexcept {
  if      (x < i32_min || x > i32_max) return Size::QWORD;
  else if (x < i16_min || x > i16_max) return Size::DWORD;
  else if (x < i8_min  || x > i8_max)  return Size::WORD;
  else return Size::BYTE;
}

Size min_width(u64 x) noexcept {
  if      (x > u32_max) return Size::QWORD;
  else if (x > u16_max) return Size::DWORD;
  else if (x > u8_max ) return Size::WORD;
  else return Size::BYTE;
}
