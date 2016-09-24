#pragma once

#include <core/typedefs.hpp>
#include <core/reg.hpp>
#include <core/arch/x86_64/constants.hpp>

class CodeBuf;

#define OP0_STUB(NAME) \
  struct NAME { \
    static int size(); \
    static void write(CodeBuf*); \
  }

#define OP1_STUB(NAME, PARAM) \
  struct NAME { \
     template<class A> static int size(A); \
     template<class A> \
     static void write(CodeBuf* output, A PARAM); \
  }

#define OP2_STUB(NAME, PARAM1, PARAM2) \
  struct NAME { \
     template<class A, class B> static int size(A, B); \
     template<class A, class B> \
     static void write(CodeBuf* output, A PARAM1, B PARAM2); \
  }

#define OP3_STUB(NAME, PARAM1, PARAM2, PARAM3) \
  struct NAME { \
     template<class A, class B, class C> static int size(A, B, C); \
     template<class A, class B, class C> \
     static void write(CodeBuf* output, A PARAM1, B PARAM2, C PARAM3); \
  }

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

OP3_STUB(Imul, dst, a, b);

struct Mov {
  template<class A, class B> static int size(A, B);
  template<class A, class B>
  static void write(CodeBuf* output, A dst, B src);

  template<class A, class B, class C> static int size(A, B, C);
  template<class A, class B, class C>
  static void write(CodeBuf* output, A dst, B mem_src, C disp);
};

#undef OP0_STUB
#undef OP1_STUB
#undef OP2_STUB
#undef OP3_STUB
