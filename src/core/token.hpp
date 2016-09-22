#pragma once

#include <core/typedefs.hpp>

enum class Token: byte {
  //// Top level tokens
  // Special token
  END,

  // Operations
  RETURN,
  ADD,
  SUB,
  ASSIGN,
  SWAP,
  NEG,
  WHILE,
  IF,
  IF_ELSE,

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

  // Relation (binary) conditions
  EQ,
  NEQ,
  LT,
  LTE,
  GT,
  GTE,
};
