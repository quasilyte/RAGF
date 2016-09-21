#include <core/compile/compile.hpp>

#include <core/io/token_stream.hpp>
#include <core/io/code_buf.hpp>
#include <core/codegen/code_writer.hpp>
#include <core/arch/x86_64/code_writer.hpp>

#include <core/compile/helpers.hpp>
#include <core/compile/parsers_macro.hpp>

#include <cstdlib>
#include <cstdio>

class Compiler {
public:
  Compiler(TokenStream& tokens, CodeWriter* writer):
  $input{tokens},
  $writer{writer} {}

  void parse_return() {
    $writer->write_return();
  }

  template<class A, class B>
  void encode(void(CodeWriter::*method)(A, B)) {
    auto a = $input.read<A>();
    auto b = $input.read<B>();
    ($writer->*method)(a, b);
  }

  void parse_assign() {
    switch ($input.read<u16>()) {
    case label(Token::REG, Token::I32):
      return encode<RegIndex, i32>(&CodeWriter::write_assign);
    case label(Token::REG, Token::I64):
      return encode<RegIndex, i64>(&CodeWriter::write_assign);

    default:
      throw "assign: invalid dst/src token";
    }
  }

  void parse_add() {
    switch ($input.read<u16>()) {
    case label(Token::REG, Token::I8):
      return encode<RegIndex, i8>(&CodeWriter::write_add);
    case label(Token::REG, Token::I32):
      return encode<RegIndex, i32>(&CodeWriter::write_add);

    default:
      throw "add: invalid dst/src token";
    }
  }

  void parse_sub() {
    switch ($input.read<u16>()) {
    case label(Token::REG, Token::I8):
      return encode<RegIndex, i8>(&CodeWriter::write_sub);

    default:
      throw "sub: invalid dst/src token";
    }
  }

  void parse_swap() {
    encode<RegIndex, RegIndex>(&CodeWriter::write_swap);
  }

  void parse_neg() {
    $writer->write_neg($input.read<RegIndex>());
  }

  void parse_loop() {
    auto block = compile_block();

    $writer->write_loop(block.size);
    $writer->write_block(block);
    $offsets.push_back(block.size);
  }

  void parse_while() {

    switch ($input.read<u32>()) {
    case label(Token::NEQ, Token::REG, Token::I8, Token::NIL): {
      RegIndex a = $input.read<RegIndex>();
      i8 b = $input.read<i8>();
      i32 offset = $offsets.back();
      $offsets.pop_back();
      return $writer->write_while_neq(offset, a, b);
    }

    default:
      throw "while: invalid token combination";
    }
//    const byte* block = blocks.back();
//    blocks.pop_back();
  }

  Buf compile();

private:
  std::vector<i32> $offsets;
  TokenStream& $input;
  CodeWriter* $writer;

  Buf compile_block() {
    auto writer_clone = $writer->clone();
    Compiler compiler{$input, writer_clone};
    return compiler.compile();
  }
};

Buf Compiler::compile() {
  BEGIN_PARSERS;
    TERMINATING_PARSER(end_of_input);
    PARSER(return);
    PARSER(add);
    PARSER(sub);
    PARSER(assign);
    PARSER(swap);
    PARSER(neg);
    PARSER(loop);
    PARSER(while);
  END_PARSERS;
}

Buf compile_i86_64(const byte* input) {
  try {
    TokenStream tokens{input};
    Compiler compiler{tokens, new x86_64::CodeWriter{}};
    return compiler.compile();
  } catch (const char* err) {
    fprintf(stderr, "error: %s\n", err);
    exit(1);
  }
}
