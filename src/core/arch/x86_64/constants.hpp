#pragma once

#include <core/typedefs.hpp>

//                     ----WRXB
const byte REX     = 0b01000000;
const byte REX_W   = 0b01001000;
const byte REX_B   = 0b01000001;
const byte REX_WB  = 0b01001001;
const byte REX_WRB = 0b01001101;

struct Mod {
  static const u64 SIB = 0;
  static const u64 DISP_ONLY = 0;
  static const u64 DISP1 = 1;
  static const u64 DISP4 = 2;
  static const u64 REG = 3;
};
