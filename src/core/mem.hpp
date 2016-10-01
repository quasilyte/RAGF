#pragma once

#include <core/reg.hpp>

struct Mem {
  Reg ptr;
  int byte_count;
  int index;

  int disp() const { return byte_count * index; }
};
