#include <core/compile/numerics.hpp>

ImmWidth min_width(i64 x) {
  const i64 i32_max = 0xffffffff >> 1;
  const i64 i16_max = 0xffff     >> 1;
  const i64 i8_max  = 0xff       >> 1;
  const i64 i32_min = -i32_max - 1;
  const i64 i16_min = -i16_max - 1;
  const i64 i8_min  = -i8_max  - 1;

  if      (x < i32_min || x > i32_max) return ImmWidth::QWORD;
  else if (x < i16_min || x > i16_max) return ImmWidth::DWORD;
  else if (x < i8_min  || x > i8_max ) return ImmWidth::WORD;
  else return ImmWidth::BYTE;
}

ImmWidth min_width(u64 x) {
  const u64 u32_max = 0xffffffff;
  const u64 u16_max = 0xffff;
  const u64 u8_max  = 0xff;

  if      (x > u32_max) return ImmWidth::QWORD;
  else if (x > u16_max) return ImmWidth::DWORD;
  else if (x > u8_max ) return ImmWidth::WORD;
  else return ImmWidth::BYTE;
}
