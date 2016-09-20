#pragma once

#include <core/typedefs.hpp>

enum class Token: byte {
  //// Top level tokens
  // Special token
  END_OF_INPUT,

  // Operations
  RETURN,
  ASSIGN,
  ADD,
  SWAP,
  NEG,

  //// Context tokens
  // Operand types
  REG,
  MEM,
  I64,
  I32,
  I8,
  U64,
  U32,
  U8,
};
