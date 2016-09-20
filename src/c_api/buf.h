#pragma once

#include <stdint.h>

struct Buf {
  const uint8_t* data;
  int64_t size;
};
