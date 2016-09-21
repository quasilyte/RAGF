#include <core/compile/resource_manager.hpp>

#include <cstdlib>

ResourceManager::ResourceManager() {
  const int initial_buf_size = 64;

  for (int i = 0; i < MAX_DEPTH; ++i) {
    auto mem = static_cast<byte*>(calloc(initial_buf_size, 1));
    $code_bufs[i].set_buf(Buf{mem, initial_buf_size});
  }
}

CodeBuf* ResourceManager::get_code_buf(int idx) noexcept {
  return $code_bufs + idx;
}

void ResourceManager::reset_code_buf(int idx) {
  $code_bufs[idx].set_len(0);
}

