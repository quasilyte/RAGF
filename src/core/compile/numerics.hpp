#pragma once

#include <core/typedefs.hpp>

enum class ImmWidth {
  BYTE,
  WORD,
  DWORD,
  QWORD
};

ImmWidth min_width(i64);
ImmWidth min_width(u64);
