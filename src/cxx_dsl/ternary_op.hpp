#pragma once

#include <core/io/binary_value.hpp>
#include <cxx_dsl/utils.hpp>

template<class T1, class T2>
struct BinaryOp {
  byte $opcode;
  u16 $types;
  T1 $dst;
  T2 $src;

  BinaryOp(Token opcode, T1 dst, T2 src):
  $opcode{static_cast<byte>(opcode)},
  $types{pack(dst, src)}, $dst{dst}, $src{src} {}

  auto get_binary_value() const noexcept {
    return BinaryValue<ceil_size(sizeof(BinaryOp))>{
      $opcode,
      $types,
      $dst,
      $src
    };
  }
};

template<class T1, class T2, class T3>
struct TernaryOp {
  byte $opcode;
  u32 $types;
  T1 $dst;
  T2 $a;
  T3 $b;

  TernaryOp(Token opcode, T1 dst, T2 a, T3 b):
  $opcode{static_cast<byte>(opcode)},
  $types{pack(dst, a, b, Token::NIL)}, $dst{dst}, $a{a}, $b{b} {}

  auto get_binary_value() const noexcept {
    return BinaryValue<ceil_size(sizeof(TernaryOp))>{
      $opcode,
      $types,
      $dst,
      $a,
      $b
    };
  }
} __attribute__((packed));
