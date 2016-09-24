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
  void parse_bit_and();
  void parse_bit_or();
  void parse_shift_left();
  void parse_shift_right();
  void parse_swap();
  void parse_neg();
  void parse_while();
  void parse_if();
  void parse_if_else();

  template<class A, class B, class ...FORWARD>
  void encode(void(CodeWriter::*method)(A, B, FORWARD...), FORWARD... args) {
    auto a = $input.read<A>();
    auto b = $input.read<B>();
    ($writer->*method)(a, b, args...);
  }

  Buf get_result();
};
