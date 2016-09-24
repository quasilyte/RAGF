#pragma once

#include <core/typedefs.hpp>
#include <core/arch/x86_64/gpr.hpp>

//                     ----WRXB     hex
const byte REX     = 0b01000000; // 40
const byte REX_W   = 0b01001000; // 48
const byte REX_B   = 0b01000001; // 41
const byte REX_WB  = 0b01001001; // 49
const byte REX_WRB = 0b01001101; // 4d
const byte REX_WR  = 0b01001100; // 4c

const Gpr rax{0};
const Gpr rcx{1};
const Gpr rdx{2};
const Gpr rbx{3};
const Gpr rsp{4};
const Gpr rbp{5};
const Gpr rsi{6}; // Used to pass code
const Gpr rdi{7}; // Used to pass data

struct Mod {
  static const u64 SIB = 0;
  static const u64 DISP_ONLY = 0;
  static const u64 DISP1 = 1;
  static const u64 DISP4 = 2;
  static const u64 REG = 3;
};
