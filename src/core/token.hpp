#pragma once

#include <core/typedefs.hpp>

enum class Token: byte {
  //// Top level tokens
  // Special token
  END_OF_INPUT,

  // Operations
  ADD,
  RETURN,
  ASSIGN,
  SWAP,
  NEG,

  //// Context tokens
  NIL,

  // Operand types
  REG,
  MEM,
  I64,
  I32,
  I8,
  U64,
  U32,
  U8,

  // Loops
  WHILE,
  END_WHILE,

  // Relation (binary) conditions
  EQ,
  NEQ,
  LT,
  LTE,
  GT,
  GTE,
};
