#pragma once

#include <core/typedefs.hpp>

//! @brief Generate x86_64 machine code from binary input
Buf compile_x86_64(const byte* binary_tokens);

/*!
 * @brief Generate x86_64 machine code from binary input
 *
 * Uses passed buf as output.
 * If buf capacity is not enough, it will be extended.
 * Function returns either the extended or previously
 * passed buf.
 */
Buf compile_x86_64(const byte* binary_tokens, Buf output);
