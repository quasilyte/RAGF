#pragma once

#include <core/args.hpp>

/*!
 * @brief Untyped general purpose register
 * Represents special register that can not be
 * accessed directly from the Ragf API.
 * GPRs are used for intermediate results and other
 * bookkeeping tasks
 */
struct Gpr: Reg {
  using Reg::Reg;
};
