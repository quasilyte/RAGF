#pragma once

#include <core/args.hpp>
#include <core/token.hpp>

inline Token to_token(Reg) noexcept { return Token::REG; }
inline Token to_token(UintReg) noexcept { return Token::UINT_REG; }
inline Token to_token(IntReg) noexcept { return Token::INT_REG; }
inline Token to_token(PtrReg) noexcept { return Token::MEM; }
inline Token to_token(Token t) noexcept { return t; }
inline Token to_token(i64) noexcept { return Token::INT; }
inline Token to_token(u64) noexcept { return Token::UINT; }

constexpr int ceil_size(int size) {
  int rem = size % 4;
  return rem ? size + (4 - rem) : size;
}

template<class T1, class T2, class T3, class T4>
u32 pack(T1 a, T2 b, T3 c, T4 d) noexcept {
  return (
    (static_cast<u32>(to_token(d)) << 24) +
    (static_cast<u32>(to_token(c)) << 16) +
    (static_cast<u32>(to_token(b)) << 8)  +
    (static_cast<u32>(to_token(a)) << 0)
  );
}

template<class T1, class T2>
u16 pack(T1 a, T2 b) noexcept {
  return (
    (static_cast<u32>(to_token(b)) << 8) +
    (static_cast<u32>(to_token(a)) << 0)
  );
}
