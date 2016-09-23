#pragma once

#include <core/typedefs.hpp>
#include <core/io/token_stream.hpp>

class CodeWriter;

class Compiler {
public:
  Compiler(TokenStream& tokens);

  void set_writer(CodeWriter* writer);

  Buf compile();

private:
  TokenStream& $input;
  CodeWriter* $writer;

  void parse_return();
  void parse_assign();
  void parse_add();
  void parse_sub();
  void parse_mul();
  void parse_div();
  void parse_mod();
  void parse_swap();
  void parse_neg();
  void parse_while();
  void parse_if();
  void parse_if_else();

  template<class A, class B>
  void encode(void(CodeWriter::*method)(A, B)) {
    auto a = $input.read<A>();
    auto b = $input.read<B>();
    ($writer->*method)(a, b);
  }

  Buf get_result();
};
