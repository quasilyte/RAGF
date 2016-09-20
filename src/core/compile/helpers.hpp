#pragma once

#include <core/typedefs.hpp>

constexpr uint label(Token a, Token b) noexcept {
  return (
    (static_cast<uint>(a)) +
    (static_cast<uint>(b) << 8)
  );
}

constexpr uint label(Token a, Token b, Token c) noexcept {
  return (
    (static_cast<uint>(a)) +
    (static_cast<uint>(b) << 8) +
    (static_cast<uint>(c) << 16)
  );
}
