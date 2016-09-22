#include <core/compile/compile.hpp>

#include <core/io/token_stream.hpp>
#include <core/io/code_buf.hpp>
#include <core/codegen/code_writer.hpp>
#include <core/arch/x86_64/code_writer.hpp>

#include <core/compile/constants.hpp>
#include <core/compile/helpers.hpp>
#include <core/compile/parsers_macro.hpp>

#include <cstdlib>
#include <cstdio>

class Compiler {
public:
  Compiler(TokenStream& tokens):
  $input{tokens} {}

  void set_writer(CodeWriter* writer) {
    $writer = writer;
  }

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
    case label(Token::REG, Token::REG):
      return encode<RegIndex, RegIndex>(&CodeWriter::write_assign);
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

//  void parse_loop() {
//    auto block = compile_block();

//    $writer->write_loop(block.size);
//    $writer->write_block(block);

//    switch ($input.read<Token>()) {
//    case Token::WHILE:
//      return parse_while(block.size);

//    default:
//      throw "loop: invalid type token";
//    }
//  }

//  void parse_while(i32 offset) {
//    switch ($input.read<u32>()) {
//    case label(Token::NEQ, Token::REG, Token::I8, Token::NIL): {
//      RegIndex a = $input.read<RegIndex>();
//      i8 b = $input.read<i8>();
//      return $writer->write_while_neq(offset, a, b);
//    }

//    default:
//      throw "while: invalid token combination";
//    }
//  }

  Buf compile();

private:
  TokenStream& $input;
  CodeWriter* $writer;

//  Buf compile_block() {
//    Compiler compiler{$depth + 1, $input, $writer};
//    auto block = compiler.compile();

//    return block;
//  }

  Buf get_result() {
    return $writer->get_buf();
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
  END_PARSERS;
}

Buf compile_i86_64(const byte* input) {
  TokenStream tokens{input};

  CodeBuf output{Buf{static_cast<byte*>(calloc(64, 1)), 64}};
  x86_64::CodeWriter writer{output};
  Compiler compiler{tokens};

  writer.set_compiler(&compiler);
  compiler.set_writer(&writer);

  return compiler.compile();
}
