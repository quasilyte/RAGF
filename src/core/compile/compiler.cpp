#include <core/compile/compiler.hpp>

#include <core/codegen/code_writer.hpp>
#include <core/compile/parsers_macro.hpp>
#include <core/compile/helpers.hpp>

Compiler::Compiler(TokenStream& tokens):
$input{tokens} {}

void Compiler::set_writer(CodeWriter* writer) {
  $writer = writer;
}

void Compiler::parse_return() {
  $writer->write_return();
}

void Compiler::parse_swap() {
  encode<RegIndex, RegIndex>(&CodeWriter::write_swap);
}

void Compiler::parse_neg() {
  $writer->write_neg($input.read<RegIndex>());
}

void Compiler::parse_add() {
  switch ($input.read<u16>()) {
  case label(Token::REG, Token::I8):
    return encode<RegIndex, i8>(&CodeWriter::write_add);
  case label(Token::REG, Token::I32):
    return encode<RegIndex, i32>(&CodeWriter::write_add);

  default:
    throw "add: invalid dst/src token";
  }
}

void Compiler::parse_sub() {
  switch ($input.read<u16>()) {
  case label(Token::REG, Token::I8):
    return encode<RegIndex, i8>(&CodeWriter::write_sub);

  default:
    throw "sub: invalid dst/src token";
  }
}

void Compiler::parse_assign() {
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

void Compiler::parse_while() {
  switch ($input.read<u32>()) {
  case label(Token::NEQ, Token::REG, Token::I8, Token::NIL):
    return encode<RegIndex, i8>(&CodeWriter::write_while_neq);

  default:
    throw "while: invalid header tokens";
  }
}

void Compiler::parse_if() {
  switch ($input.read<u32>()) {
  case label(Token::EQ, Token::REG, Token::I8, Token::NIL):
    return encode<RegIndex, i8>(&CodeWriter::write_if_eq);

  default:
    throw "if: invalid header tokens";
  }
}

void Compiler::parse_if_else() {
  switch ($input.read<u32>()) {
  case label(Token::EQ, Token::REG, Token::I8, Token::NIL):
    return encode<RegIndex, i8>(&CodeWriter::write_if_else_eq);

  default:
    throw "if/else: invalid header tokens";
  }
}

Buf Compiler::compile() {
  BEGIN_PARSERS;
    TERMINATING_PARSER(end_of_input);
    PARSER(return);
    PARSER(add);
    PARSER(sub);
    PARSER(assign);
    PARSER(swap);
    PARSER(neg);
    PARSER(while);
    PARSER(if);
    PARSER(if_else);
  END_PARSERS;
}

Buf Compiler::get_result() {
  return $writer->get_buf();
}
