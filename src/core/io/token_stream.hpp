#pragma once

#include <core/typedefs.hpp>
#include <core/token.hpp>
#include <core/reg_index.hpp>

class TokenStream {
public:
  TokenStream(const byte* input);

  template<class T>
  T read() noexcept;

  byte read_byte() noexcept;
  Token read_token() noexcept;
  RegIndex read_reg_index();
  const byte* read_bytes(int count) noexcept;

private:
  const byte* $input;
  const byte* $pos;
};
