#pragma once

#include <core/typedefs.hpp>
#include <core/reg.hpp>
#include <core/arch/x86_64/constants.hpp>

class CodeBuf;

#define SIG1(PARAM) \
  template<class A> static int size(A); \
  template<class A> \
  static void write(CodeBuf* output, A PARAM)

#define SIG2(PARAM1, PARAM2) \
  template<class A, class B> static int size(A, B); \
  template<class A, class B> \
  static void write(CodeBuf* output, A PARAM1, B PARAM2)

#define SIG3(PARAM1, PARAM2, PARAM3) \
  template<class A, class B, class C> static int size(A, B, C); \
  template<class A, class B, class C> \
  static void write(CodeBuf* output, A PARAM1, B PARAM2, C PARAM3)

#define OP0_STUB(NAME) \
  struct NAME { \
    static int size(); \
    static void write(CodeBuf*); \
  }

#define OP1_STUB(NAME, PARAM) \
  struct NAME { SIG1(PARAM); }

#define OP2_STUB(NAME, PARAM1, PARAM2) \
  struct NAME { SIG2(PARAM1, PARAM2); }

#define OP3_STUB(NAME, PARAM1, PARAM2, PARAM3) \
  struct NAME { SIG3(PARAM1, PARAM2, PARAM3); }

OP0_STUB(Nop);
OP0_STUB(Ret);
OP0_STUB(Cqo);

OP1_STUB(Jne, offset);
OP1_STUB(Jmp, offset);
OP1_STUB(Neg, r);
OP1_STUB(Idiv, divider);

OP2_STUB(Add, dst, src);
OP2_STUB(Sub, dst, src);
OP2_STUB(And, dst, src);
OP2_STUB(Xor, dst, src);
OP2_STUB(Or, dst, src);
OP2_STUB(Xchg, a, b);
OP2_STUB(Cmp, a, b);
OP2_STUB(Shl, r, count);
OP2_STUB(Shr, r, count);
OP2_STUB(Sar, r, count);

struct Imul {
  SIG2(dst, src);
  SIG3(dst, a, b);
};

struct Mov {
  SIG2(dst, src);
  SIG3(dst, mem_src, disp);
};

#undef SIG1
#undef SIG2
#undef SIG3
#undef OP0_STUB
#undef OP1_STUB
#undef OP2_STUB
#undef OP3_STUB
