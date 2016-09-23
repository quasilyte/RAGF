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
  MUL,
  DIV,
  MOD,
  BIT_AND,
  BIT_OR,
  SHIFT_LEFT,
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
  INT_REG,
  UINT_REG,
  MEM,
  INT64,
  INT32,
  INT8,
  UINT64,
  UINT32,
  UINT8,

  // Relation (binary) conditions
  EQ,
  NEQ,
  LT,
  LTE,
  GT,
  GTE,
};
