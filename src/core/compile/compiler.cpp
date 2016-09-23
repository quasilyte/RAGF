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
  encode<Reg, Reg>(&CodeWriter::write_swap);
}

void Compiler::parse_neg() {
  $writer->write_neg($input.read<Reg>());
}

void Compiler::parse_add() {
  switch ($input.read<u16>()) {
  case label(Token::REG, Token::INT8):
    return encode<Reg, i8>(&CodeWriter::write_add);
  case label(Token::REG, Token::INT32):
    return encode<Reg, i32>(&CodeWriter::write_add);

  default:
    throw "add: invalid dst/src token";
  }
}

void Compiler::parse_sub() {
  switch ($input.read<u16>()) {
  case label(Token::REG, Token::INT8):
    return encode<Reg, i8>(&CodeWriter::write_sub);

  default:
    throw "sub: invalid dst/src token";
  }
}

void Compiler::parse_mul() {
  switch ($input.read<u16>()) {
  case label(Token::INT_REG, Token::INT8):
    return encode<IntReg, i8>(&CodeWriter::write_mul);

  default:
    throw "mul: invalid dst/src token";
  }
}

void Compiler::parse_div() {
  switch ($input.read<u16>()) {
  case label(Token::INT_REG, Token::INT_REG):
    return encode<IntReg, IntReg>(&CodeWriter::write_div);

  default:
    throw "div: invalid dst/src token";
  }
}

void Compiler::parse_mod() {
  switch ($input.read<u16>()) {
  case label(Token::INT_REG, Token::INT_REG):
    return encode<IntReg, IntReg>(&CodeWriter::write_mod);

  default:
    throw "mod: invalid dst/src token";
  }
}

void Compiler::parse_bit_and() {
  switch ($input.read<u16>()) {
  case label(Token::REG, Token::REG):
    return encode<Reg, Reg>(&CodeWriter::write_bit_and);

  default:
    throw "bit_and: invalid dst/src token";
  }
}

void Compiler::parse_bit_or() {
  switch ($input.read<u16>()) {
  case label(Token::REG, Token::REG):
    return encode<Reg, Reg>(&CodeWriter::write_bit_or);

  default:
    throw "bit_or: invalid dst/src token";
  }
}

void Compiler::parse_shift_left() {
  encode<Reg, u8>(&CodeWriter::write_shift_left);
}

void Compiler::parse_assign() {
  switch ($input.read<u16>()) {
  case label(Token::REG, Token::REG):
    return encode<Reg, Reg>(&CodeWriter::write_assign);
  case label(Token::REG, Token::INT32):
    return encode<Reg, i32>(&CodeWriter::write_assign);
  case label(Token::REG, Token::INT64):
    return encode<Reg, i64>(&CodeWriter::write_assign);

  default:
    throw "assign: invalid dst/src token";
  }
}

void Compiler::parse_while() {
  switch ($input.read<u32>()) {
  case label(Token::NEQ, Token::REG, Token::INT8, Token::NIL):
    return encode<Reg, i8>(&CodeWriter::write_while_neq);

  default:
    throw "while: invalid header tokens";
  }
}

void Compiler::parse_if() {
  switch ($input.read<u32>()) {
  case label(Token::EQ, Token::REG, Token::INT8, Token::NIL):
    return encode<Reg, i8>(&CodeWriter::write_if_eq);

  default:
    throw "if: invalid header tokens";
  }
}

void Compiler::parse_if_else() {
  switch ($input.read<u32>()) {
  case label(Token::EQ, Token::REG, Token::INT8, Token::NIL):
    return encode<Reg, i8>(&CodeWriter::write_if_else_eq);

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
    PARSER(mul);
    PARSER(div);
    PARSER(mod);
    PARSER(bit_and);
    PARSER(bit_or);
    PARSER(shift_left);
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
