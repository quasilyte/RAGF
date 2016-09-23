#pragma once

#include <core/typedefs.hpp>
#include <core/token.hpp>
#include <core/register.hpp>

class TokenStream {
public:
  TokenStream(const byte* input);

  template<class T> T read();

  byte read_byte() noexcept;
  const byte* read_bytes(int count) noexcept;

private:
  const byte* $input;
  const byte* $pos;
};
