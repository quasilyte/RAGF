#pragma once

class CodeBuf;

class CodeBufSlice {
public:
  CodeBufSlice(CodeBuf*, int size, int offset);

  operator CodeBuf*() const noexcept;

private:
  CodeBuf* $origin;
  int $size;
  int $offset;
};
