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

#define OP0_DECL(NAME) \
  struct NAME { \
    static int size(); \
    static void write(CodeBuf*); \
  }

#define OP1_DECL(NAME, PARAM) \
  struct NAME { SIG1(PARAM); }

#define OP2_DECL(NAME, PARAM1, PARAM2) \
  struct NAME { SIG2(PARAM1, PARAM2); }

#define OP3_DECL(NAME, PARAM1, PARAM2, PARAM3) \
  struct NAME { SIG3(PARAM1, PARAM2, PARAM3); }

OP0_DECL(Nop);
OP0_DECL(Ret);
OP0_DECL(Cqo);

OP1_DECL(Jne, offset);
OP1_DECL(Jmp, offset);
OP1_DECL(Neg, r);
OP1_DECL(Idiv, divider);
OP1_DECL(Call, fn_ptr);
OP1_DECL(Push, r);
OP1_DECL(Pop, r);

OP2_DECL(Add, dst, src);
OP2_DECL(Sub, dst, src);
OP2_DECL(And, dst, src);
OP2_DECL(Xor, dst, src);
OP2_DECL(Or, dst, src);
OP2_DECL(Xchg, a, b);
OP2_DECL(Cmp, a, b);
OP2_DECL(Shl, r, count);
OP2_DECL(Shr, r, count);
OP2_DECL(Sar, r, count);

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
#undef OP0_DECL
#undef OP1_DECL
#undef OP2_DECL
#undef OP3_DECL
