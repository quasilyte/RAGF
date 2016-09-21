#pragma once

#include <core/compile/constants.hpp>
#include <core/io/code_buf.hpp>

class ResourceManager {
public:
  ResourceManager();

  CodeBuf* get_code_buf(int idx) noexcept;
  void reset_code_buf(int idx);

private:
  CodeBuf $code_bufs[MAX_DEPTH];
};
