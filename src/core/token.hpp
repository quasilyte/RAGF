#pragma once

#include <core/typedefs.hpp>

enum class Token: byte {
  //// Top level tokens
  // Special token
  END,

  // Operations
  RETURN,
  PUSH,
  POP,
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  BIT_AND,
  BIT_OR,
  SHIFT_LEFT,
  SHIFT_RIGHT,
  ASSIGN,
  SWAP,
  NEG,
  WHILE,
  IF,
  IF_ELSE,

  //// Context tokens
  NIL,
  DATA,
  COUNTER,

  // Operand types
  REG,
  INT_REG,
  UINT_REG,
  MEM64,
  MEM32,
  MEM8,
  INT64,
  INT32,
  INT8,
  UINT64,
  UINT32,
  UINT8,
  INT,

  // Relation (binary) conditions
  EQ,
  NEQ,
  LT,
  LTE,
  GT,
  GTE,
};
