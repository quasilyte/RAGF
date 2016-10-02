#pragma once

#include <core/typedefs.hpp>

//! @brief Generate x86_64 machine code from binary input
Buf compile_x86_64(const byte* binary_tokens);
