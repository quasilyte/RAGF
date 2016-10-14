#pragma once

#include <core/args.hpp>

const Reg R0{0};
const Reg R1{1};
const Reg R2{2};
const Reg R3{3};
const Reg R4{4};
const Reg R5{5};
const Reg R6{6};
const Reg R7{7};

const IntReg ir0{0};
const IntReg ir1{1};
const IntReg ir2{2};
const IntReg ir3{3};
const IntReg ir4{4};
const IntReg ir5{5};
const IntReg ir6{6};
const IntReg ir7{7};

const UintReg ur0{0};
const UintReg ur1{1};
const UintReg ur2{2};
const UintReg ur3{3};
const UintReg ur4{4};
const UintReg ur5{5};
const UintReg ur6{6};
const UintReg ur7{7};

inline Reg r(int id) {
  return Reg{static_cast<byte>(id)};
}

inline IntReg ir(int id) {
  return IntReg{static_cast<byte>(id)};
}

inline UintReg ur(int id) {
  return UintReg{static_cast<byte>(id)};
}
