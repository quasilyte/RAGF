#pragma once

#include <core/typedefs.hpp>

namespace priv {
  constexpr uint label(int step, Token t) {
    return (static_cast<uint>(t) << (step * 8));
  }

  template<class... ARGS>
  constexpr uint label(int step, Token head, ARGS... tail) {
    return label(step, head) + label(step + 1, tail...);
  }
}

template<class... ARGS>
constexpr uint label(ARGS... tokens) {
  return priv::label(0, tokens...);
}

#define T1(A) \
  Token::A
#define T2(A, B) \
  label(Token::A, Token::B)
#define T3(A, B, C) \
  label(Token::A, Token::B, Token::C)
#define T4(A, B, C, D) \
  label(Token::A, Token::B, Token::C, Token::D)
