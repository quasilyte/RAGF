#pragma once

#include <cxx_dsl/ternary_op.hpp>
#include <core/token.hpp>

namespace priv {
  template<class T1, class T2, class T3>
  auto make_ternary(Token t, T1 dst, T2 a, T3 b) {
    auto op = TernaryOp<T1, T2, T3>{t, dst, a, b};
    return op.get_binary_value();
  }

  template<class T1, class T2>
  auto make_binary(Token t, T1 dst, T2 src) {
    auto op = BinaryOp<T1, T2>{t, dst, src};
    return op.get_binary_value();
  }
}

byte end() noexcept {
  return static_cast<byte>(Token::END);
}

template<class T1, class T2, class T3>
auto op_add(T1 dst, T2 a, T3 b) noexcept {
  return priv::make_ternary(Token::ADD, dst, a, b);
}

template<class T1, class T2, class T3>
auto op_sub(T1 dst, T2 a, T3 b) {
  return priv::make_ternary(Token::SUB, dst, a, b);
}

template<class T1, class T2>
auto op_assign(T1 dst, T2 src) {
  return priv::make_binary(Token::ASSIGN, dst, src);
}

auto op_ret(Reg r) noexcept {
  return BinaryValue<4>{Token::RETURN, Token::REG, r};
}

auto op_ret() noexcept {
  return BinaryValue<2>{Token::RETURN, Token::NIL};
}
