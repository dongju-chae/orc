
#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>

#include <orc/orcprogram.h>
#include <orc/orcarm.h>

#define COND_EQ 0x0
#define COND_NE 0x1
#define COND_CS 0x2
#define COND_HS 0x2
#define COND_CC 0x3
#define COND_LO 0x3
#define COND_MI 0x4
#define COND_PL 0x5
#define COND_VS 0x6
#define COND_VC 0x7
#define COND_HI 0x8
#define COND_LS 0x9
#define COND_GE 0xa
#define COND_LT 0xb
#define COND_GT 0xc
#define COND_LE 0xd
#define COND_AL 0xe

/* shifter operands */
/*    1
 *  1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+
 * |rotimm |   immed_8     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define arm_so_imm(rot,imm) (((rot)<<8)|(imm))
/*    1
 *  1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+
 * |    Si   | St  |0| Rm  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define arm_so_shift_imm(Si,St,Rm) (((Si)<<7)|((St)<<5)|(Rm))
#define SHIFT_LSL  0
#define SHIFT_LSR  1
#define SHIFT_ASR  2
#define SHIFT_ROR  3
#define arm_so_rrx_reg(Rs,Rm) arm_dp_shift_imm(0,SHIFT_ROR,Rm)
#define arm_so_reg(Rm)        (Rm)
/*    1
 *  1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Rs   |0| St  |1| Rm  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define arm_so_shift_reg(Rs,St,Rm) (0x008|((Rs)<<8)|((St)<<5)|(Rm))

/* data processing instructions */
/*    3   2 2 2 2 2     2 2 1     1 1     1   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | cond  |0 0|I| opcode|S|   Rn  |  Rd   |   shifter_operand     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define arm_dp(cond,I,opcode,S,Rn,Rd,So) (((cond)<<28)|((I)<<25)|((opcode)<<21)|((S)<<20)|((Rn)<<16)|((Rd)<<12)|So)
#define arm_dp_reg(cond,opcode,S,Rn,Rd,So) arm_dp (cond,0,opcode,S,Rn,Rd,So)
#define arm_dp_imm(cond,opcode,S,Rn,Rd,So) arm_dp (cond,1,opcode,S,Rn,Rd,So)
#define DP_AND 0x0
#define DP_EOR 0x1
#define DP_SUB 0x2
#define DP_RSB 0x3
#define DP_ADD 0x4
#define DP_ADC 0x5
#define DP_SBC 0x6
#define DP_RSC 0x7
#define DP_TST 0x8
#define DP_TEQ 0x9
#define DP_CMP 0xa
#define DP_CMN 0xb
#define DP_ORR 0xc
#define DP_MOV 0xd
#define DP_BIC 0xe
#define DP_MVN 0xf

#define BINARY_DP(opcode,insn_name,dp_op) \
static void \
arm_rule_ ## opcode (OrcCompiler *p, void *user, OrcInstruction *insn) \
{ \
  uint32_t code;                                                       \
  int src1 = ORC_SRC_ARG (p, insn, 0);                                 \
  int src2 = ORC_SRC_ARG (p, insn, 1);                                 \
  int dest = ORC_DEST_ARG (p, insn, 0);                                \
                                                                       \
  code = arm_dp_reg (COND_AL, dp_op, 0, src1, dest, arm_so_reg (src2));\
  ORC_ASM_CODE(p,"  %s %s, %s, %s\n",                                  \
      insn_name,                                                       \
      orc_arm_reg_name (dest),                                         \
      orc_arm_reg_name (src1),                                         \
      orc_arm_reg_name (src2));                                        \
  orc_arm_emit (p, code);                                              \
}

/* parallel instructions */
/*    3   2 2 2 2 2     2 2 1     1 1     1   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | cond  |      mode     |   Rn  |  Rd   |0 0 0 0|  op   |  Rm   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define arm_code_mm(cond,mode,Rn,Rd,op,Rm) (((cond)<<28)|((mode)<<20)|((src1)<<16)|((dest)<<12)|((op)<<4)|(src2))
#define MM_MODE_S      0x61
#define MM_MODE_Q      0x62
#define MM_MODE_SH     0x63
#define MM_MODE_U      0x65
#define MM_MODE_UQ     0x66
#define MM_MODE_UH     0x67

#define MM_OP_ADD16    0x1
#define MM_OP_ADDSUBX  0x3
#define MM_OP_SUBADDX  0x5
#define MM_OP_SUB16    0x7
#define MM_OP_ADD8     0x9
#define MM_OP_SUB8     0xf

#define BINARY_MM(opcode,insn_name,mm_op,mm_mode) \
static void \
arm_rule_ ## opcode (OrcCompiler *p, void *user, OrcInstruction *insn) \
{ \
  uint32_t code;                                                       \
  int src1 = ORC_SRC_ARG (p, insn, 0);                                 \
  int src2 = ORC_SRC_ARG (p, insn, 1);                                 \
  int dest = ORC_DEST_ARG (p, insn, 0);                                \
                                                                       \
  code = arm_code_mm (COND_AL, mm_mode, src1, dest, mm_op, src2);      \
  ORC_ASM_CODE(p,"  %s %s, %s, %s\n",                                  \
      insn_name,                                                       \
      orc_arm_reg_name (dest),                                         \
      orc_arm_reg_name (src1),                                         \
      orc_arm_reg_name (src2));                                        \
  orc_arm_emit (p, code);                                              \
}

void
orc_arm_loadw (OrcCompiler *compiler, int dest, int src1, int offset)
{
  uint32_t code;

  code = 0xe1d000b0;
  code |= (src1&0xf) << 16;
  code |= (dest&0xf) << 12;
  code |= (offset&0xf0) << 4;
  code |= offset&0x0f;

  ORC_ASM_CODE(compiler,"  ldrh %s, [%s, #%d]\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1), offset);
  orc_arm_emit (compiler, code);
}

void
orc_arm_storew (OrcCompiler *compiler, int dest, int offset, int src1)
{
  uint32_t code;

  code = 0xe1c000b0;
  code |= (dest&0xf) << 16;
  code |= (src1&0xf) << 12;
  code |= (offset&0xf0) << 4;
  code |= offset&0x0f;

  ORC_ASM_CODE(compiler,"  strh %s, [%s, #%d]\n",
      orc_arm_reg_name (src1),
      orc_arm_reg_name (dest), offset);
  orc_arm_emit (compiler, code);
}

#if 0
UNARY_SB(absb, "ORC_ABS(%s)")
#endif
BINARY_MM (addb, "sadd8", MM_OP_ADD8, MM_MODE_S);
BINARY_MM (addssb, "qadd8", MM_OP_ADD8, MM_MODE_Q);
BINARY_MM (addusb, "uqadd8", MM_OP_ADD8, MM_MODE_UQ);
BINARY_DP (andX, "and", DP_AND);
BINARY_DP (andnX, "bic", DP_BIC);
static void
arm_rule_avgsb (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_dp_reg (COND_AL, DP_ADD, 0, src1, dest, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  add %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_dp_imm (COND_AL, DP_ADD, 0, dest, dest, arm_so_imm (0,1));
  ORC_ASM_CODE(p,"  add %s, %s, #1\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (dest));
  orc_arm_emit (p, code);

  code = COND_AL << 28;
  code |= 0x6a << 20;
  code |= 0xf << 16;
  code |= dest << 12;
  code |= 0x7 << 4;
  code |= dest;
  ORC_ASM_CODE(p,"  sxtb %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (dest));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_AL, DP_MOV, 0, 0, dest, arm_so_shift_imm (1,SHIFT_LSR,dest));
  ORC_ASM_CODE(p,"  mov %s, %s, LSR #1\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (dest));
  orc_arm_emit (p, code);
}
static void
arm_rule_avguX (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_dp_reg (COND_AL, DP_ADD, 0, src1, dest, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  add %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_dp_imm (COND_AL, DP_ADD, 0, dest, dest, arm_so_imm (0,1));
  ORC_ASM_CODE(p,"  add %s, %s, #1\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (dest));

  code = arm_dp_reg (COND_AL, DP_MOV, 0, 0, dest, arm_so_shift_imm (1,SHIFT_LSR,dest));
  ORC_ASM_CODE(p,"  mov %s, %s, LSR #1\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (dest));
}
#if 0
BINARY_SB(cmpeqb, "(%s == %s) ? (~0) : 0")
BINARY_SB(cmpgtsb, "(%s > %s) ? (~0) : 0")
#endif
static void
arm_rule_copyX (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_dp_reg (COND_AL, DP_MOV, 0, 0, dest, arm_so_reg (src1));
  ORC_ASM_CODE(p,"  mov %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1));
  orc_arm_emit (p, code);
}

static void
arm_rule_maxsb (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_code_mm (COND_AL, MM_MODE_S, src1, dest, MM_OP_SUB8, src2);
  ORC_ASM_CODE(p,"  ssub8 %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_code_mm (COND_AL, 0x68, src1, dest, 0xb, src2);
  ORC_ASM_CODE(p,"  sel %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);
}
static void
arm_rule_maxub (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_code_mm (COND_AL, MM_MODE_U, src1, dest, MM_OP_SUB8, src2);
  ORC_ASM_CODE(p,"  usub8 %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_code_mm (COND_AL, 0x68, src1, dest, 0xb, src2);
  ORC_ASM_CODE(p,"  sel %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);
}
static void
arm_rule_minsb (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_code_mm (COND_AL, MM_MODE_S, src1, dest, MM_OP_SUB8, src2);
  ORC_ASM_CODE(p,"  ssub8 %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_code_mm (COND_AL, 0x68, src2, dest, 0xb, src1);
  ORC_ASM_CODE(p,"  sel %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src2),
      orc_arm_reg_name (src1));
  orc_arm_emit (p, code);
}
static void
arm_rule_minub (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_code_mm (COND_AL, MM_MODE_U, src1, dest, MM_OP_SUB8, src2);
  ORC_ASM_CODE(p,"  usub8 %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_code_mm (COND_AL, 0x68, src2, dest, 0xb, src1);
  ORC_ASM_CODE(p,"  sel %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src2),
      orc_arm_reg_name (src1));
  orc_arm_emit (p, code);
}

#if 0
BINARY_SB(mullb, "(%s * %s) & 0xff")
BINARY_SB(mulhsb, "(%s * %s) >> 8")
BINARY_UB(mulhub, "((uint32_t)(uint8_t)%s * (uint32_t)(uint8_t)%s) >> 8")
#endif
BINARY_DP (orX, "orr", DP_ORR);
#if 0
BINARY_SB(shlb, "%s << %s")
BINARY_SB(shrsb, "%s >> %s")
BINARY_UB(shrub, "((uint8_t)%s) >> %s")
UNARY_SB(signb, "ORC_CLAMP(%s,-1,1)")
#endif
BINARY_MM (subb, "ssub8", MM_OP_SUB8, MM_MODE_S);
BINARY_MM (subssb, "qsub8", MM_OP_SUB8, MM_MODE_Q);
BINARY_MM (subusb, "uqsub8", MM_OP_SUB8, MM_MODE_UQ);
BINARY_DP (xorX, "eor", DP_EOR);

#if 0
UNARY_SW(absw, "ORC_ABS(%s)")
#endif
BINARY_MM (addw, "sadd16", MM_OP_ADD16, MM_MODE_S);
BINARY_MM (addssw, "qadd16", MM_OP_ADD16, MM_MODE_Q);
BINARY_MM (addusw, "uqadd16", MM_OP_ADD16, MM_MODE_UQ);
static void
arm_rule_avgsw (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_dp_reg (COND_AL, DP_ADD, 0, src1, dest, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  add %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_dp_imm (COND_AL, DP_ADD, 0, dest, dest, arm_so_imm (0,1));
  ORC_ASM_CODE(p,"  add %s, %s, #1\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (dest));
  orc_arm_emit (p, code);

  code = COND_AL << 28;
  code |= 0x6b << 20;
  code |= 0xf << 16;
  code |= dest << 12;
  code |= 0x7 << 4;
  code |= dest;
  ORC_ASM_CODE(p,"  sxth %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (dest));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_AL, DP_MOV, 0, 0, dest, arm_so_shift_imm (1,SHIFT_LSR,dest));
  ORC_ASM_CODE(p,"  mov %s, %s, LSR #1\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (dest));
  orc_arm_emit (p, code);
}
#if 0
BINARY_SW(cmpeqw, "(%s == %s) ? (~0) : 0")
BINARY_SW(cmpgtsw, "(%s > %s) ? (~0) : 0")
#endif
static void
arm_rule_maxsw (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_code_mm (COND_AL, MM_MODE_S, src1, dest, MM_OP_SUB16, src2);
  ORC_ASM_CODE(p,"  ssub16 %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_code_mm (COND_AL, 0x68, src1, dest, 0xb, src2);
  ORC_ASM_CODE(p,"  sel %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);
}
static void
arm_rule_maxuw (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_code_mm (COND_AL, MM_MODE_U, src1, dest, MM_OP_SUB16, src2);
  ORC_ASM_CODE(p,"  usub16 %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_code_mm (COND_AL, 0x68, src1, dest, 0xb, src2);
  ORC_ASM_CODE(p,"  sel %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);
}
static void
arm_rule_minsw (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_code_mm (COND_AL, MM_MODE_S, src1, dest, MM_OP_SUB16, src2);
  ORC_ASM_CODE(p,"  ssub16 %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_code_mm (COND_AL, 0x68, src2, dest, 0xb, src1);
  ORC_ASM_CODE(p,"  sel %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src2),
      orc_arm_reg_name (src1));
  orc_arm_emit (p, code);
}
static void
arm_rule_minuw (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_code_mm (COND_AL, MM_MODE_U, src1, dest, MM_OP_SUB16, src2);
  ORC_ASM_CODE(p,"  usub16 %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_code_mm (COND_AL, 0x68, src2, dest, 0xb, src1);
  ORC_ASM_CODE(p,"  sel %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src2),
      orc_arm_reg_name (src1));
  orc_arm_emit (p, code);
}

static void
arm_rule_mullw (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  /* BINARY_SW(mullw, "(%s * %s) & 0xffff") */
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = 0xe0000090;
  code |= (dest & 0xf) << 16;
  code |= (src1 & 0xf) << 0;
  code |= (src2 & 0xf) << 8;

  ORC_ASM_CODE(p,"  mul %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);
}
#if 0
BINARY_SW(mulhsw, "(%s * %s) >> 16")
BINARY_UW(mulhuw, "((uint32_t)((uint16_t)%s) * (uint32_t)((uint16_t)%s)) >> 16")
BINARY_SW(shlw, "%s << %s")
#endif
static void
arm_rule_shrsw (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  /* BINARY_SW(shrsw, "%s >> %s") */
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = 0xe1a00050;
  code |= (dest & 0xf) << 16;
  code |= (src1 & 0xf) << 0;
  code |= (src2 & 0xf) << 8;

  ORC_ASM_CODE(p,"  asr %s, %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);
}
#if 0
BINARY_UW(shruw, "((uint16_t)%s) >> %s")
UNARY_SW(signw, "ORC_CLAMP(%s,-1,1)")
#endif
BINARY_MM (subw, "ssub16", MM_OP_SUB16, MM_MODE_S);
BINARY_MM (subssw, "qsub16", MM_OP_SUB16, MM_MODE_Q);
BINARY_MM (subusw, "uqsub16", MM_OP_SUB16, MM_MODE_UQ);
#if 0
UNARY_SL(absl, "ORC_ABS(%s)")
#endif
BINARY_DP (addl, "add", DP_ADD);
BINARY_MM (addssl, "qadd", 0x5, 0x10);
#if 0
BINARY_UL(addusl, "ORC_CLAMP_UL((int64_t)(uint32_t)%s + (int64_t)(uint32_t)%s)")
BINARY_SL(avgsl, "((int64_t)%s + (int64_t)%s + 1)>>1")
BINARY_UL(avgul, "((uint64_t)(uint32_t)%s + (uint64_t)(uint32_t)%s + 1)>>1")
BINARY_SL(cmpeql, "(%s == %s) ? (~0) : 0")
BINARY_SL(cmpgtsl, "(%s > %s) ? (~0) : 0")
#endif
static void
arm_rule_maxsl (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_dp_reg (COND_AL, DP_CMP, 1, src1, 0, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  cmp %s, %s\n",
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_GE, DP_MOV, 0, 0, dest, arm_so_reg (src1));
  ORC_ASM_CODE(p,"  movge %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_LT, DP_MOV, 0, 0, dest, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  movlt %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);
}
static void
arm_rule_maxul (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_dp_reg (COND_AL, DP_CMP, 1, src1, 0, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  cmp %s, %s\n",
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_CS, DP_MOV, 0, 0, dest, arm_so_reg (src1));
  ORC_ASM_CODE(p,"  movcs %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_CC, DP_MOV, 0, 0, dest, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  movcc %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);
}
static void
arm_rule_minsl (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_dp_reg (COND_AL, DP_CMP, 1, src1, 0, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  cmp %s, %s\n",
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_GE, DP_MOV, 0, 0, dest, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  movge %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_LT, DP_MOV, 0, 0, dest, arm_so_reg (src1));
  ORC_ASM_CODE(p,"  movlt %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1));
  orc_arm_emit (p, code);
}
static void
arm_rule_minul (OrcCompiler *p, void *user, OrcInstruction *insn)
{
  uint32_t code;
  int src1 = ORC_SRC_ARG (p, insn, 0);
  int src2 = ORC_SRC_ARG (p, insn, 1);
  int dest = ORC_DEST_ARG (p, insn, 0);

  code = arm_dp_reg (COND_AL, DP_CMP, 1, src1, 0, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  cmp %s, %s\n",
      orc_arm_reg_name (src1),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_CS, DP_MOV, 0, 0, dest, arm_so_reg (src2));
  ORC_ASM_CODE(p,"  movcs %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src2));
  orc_arm_emit (p, code);

  code = arm_dp_reg (COND_CC, DP_MOV, 0, 0, dest, arm_so_reg (src1));
  ORC_ASM_CODE(p,"  movcc %s, %s\n",
      orc_arm_reg_name (dest),
      orc_arm_reg_name (src1));
  orc_arm_emit (p, code);
}

#if 0
BINARY_SL(mulll, "(%s * %s) & 0xffffffff")
BINARY_SL(mulhsl, "((int64_t)%s * (int64_t)%s) >> 32")
BINARY_UL(mulhul, "((uint64_t)%s * (uint64_t)%s) >> 32")
BINARY_SL(shll, "%s << %s")
BINARY_SL(shrsl, "%s >> %s")
BINARY_UL(shrul, "((uint32_t)%s) >> %s")
UNARY_SL(signl, "ORC_CLAMP(%s,-1,1)")
#endif
BINARY_DP (subl, "sub", DP_SUB);
BINARY_MM (subssl, "qsub", 0x5, 0x12);
#if 0
BINARY_UL(subusl, "ORC_CLAMP_UL((int64_t)(uint32_t)%s - (int64_t)(uint32_t)%s)")

UNARY_BW(convsbw, "%s")
UNARY_BW(convubw, "(uint8_t)%s")
UNARY_WL(convswl, "%s")
UNARY_WL(convuwl, "(uint16_t)%s")
UNARY_WB(convwb, "%s")
UNARY_WB(convssswb, "ORC_CLAMP_SB(%s)")
UNARY_WB(convsuswb, "ORC_CLAMP_UB(%s)")
UNARY_WB(convusswb, "ORC_CLAMP_SB((uint16_t)%s)")
UNARY_WB(convuuswb, "ORC_CLAMP_UB((uint16_t)%s)")
UNARY_LW(convlw, "%s")
UNARY_LW(convssslw, "ORC_CLAMP_SW(%s)")
UNARY_LW(convsuslw, "ORC_CLAMP_UW(%s)")
UNARY_LW(convusslw, "ORC_CLAMP_SW((uint32_t)%s)")
UNARY_LW(convuuslw, "ORC_CLAMP_UW((uint32_t)%s)")

BINARY_BW(mulsbw, "%s * %s")
BINARY_BW(mulubw, "(uint8_t)%s * (uint8_t)%s")
BINARY_WL(mulswl, "%s * %s")
BINARY_WL(muluwl, "(uint16_t)%s * (uint16_t)%s")

BINARY_WL(mergewl, "((uint16_t)%s) | ((uint16_t)%s << 16)")
BINARY_BW(mergebw, "((uint8_t)%s) | ((uint8_t)%s << 8)")
UNARY_WB(select0wb, "(uint16_t)%s & 0xff")
UNARY_WB(select1wb, "((uint16_t)%s >> 8)&0xff")
UNARY_LW(select0lw, "(uint32_t)%s & 0xffff")
UNARY_LW(select1lw, "((uint32_t)%s >> 16)&0xffff")
UNARY_UW(swapw, "ORC_SWAP_W(%s)")
UNARY_UL(swapl, "ORC_SWAP_L(%s)")
#endif

void
orc_compiler_orc_arm_register_rules (OrcTarget *target)
{
  OrcRuleSet *rule_set;

  rule_set = orc_rule_set_new (orc_opcode_set_get("sys"), target, 0);

  orc_rule_register (rule_set, "addb", arm_rule_addb, NULL);
  orc_rule_register (rule_set, "addssb", arm_rule_addssb, NULL);
  orc_rule_register (rule_set, "addusb", arm_rule_addusb, NULL);
  orc_rule_register (rule_set, "andb", arm_rule_andX, NULL);
  orc_rule_register (rule_set, "andnb", arm_rule_andnX, NULL);
  orc_rule_register (rule_set, "avgsb", arm_rule_avgsb, NULL);
  orc_rule_register (rule_set, "avgub", arm_rule_avguX, NULL);
  orc_rule_register (rule_set, "copyb", arm_rule_copyX, NULL);
  orc_rule_register (rule_set, "maxsb", arm_rule_maxsb, NULL);
  orc_rule_register (rule_set, "maxub", arm_rule_maxub, NULL);
  orc_rule_register (rule_set, "minsb", arm_rule_minsb, NULL);
  orc_rule_register (rule_set, "minub", arm_rule_minub, NULL);
  orc_rule_register (rule_set, "orb", arm_rule_orX, NULL);
  orc_rule_register (rule_set, "subb", arm_rule_subb, NULL);
  orc_rule_register (rule_set, "subssb", arm_rule_subssb, NULL);
  orc_rule_register (rule_set, "subusb", arm_rule_subusb, NULL);
  orc_rule_register (rule_set, "xorb", arm_rule_xorX, NULL);

  orc_rule_register (rule_set, "addw", arm_rule_addw, NULL);
  orc_rule_register (rule_set, "addssw", arm_rule_addssw, NULL);
  orc_rule_register (rule_set, "addusw", arm_rule_addusw, NULL);
  orc_rule_register (rule_set, "andw", arm_rule_andX, NULL);
  orc_rule_register (rule_set, "andnw", arm_rule_andnX, NULL);
  orc_rule_register (rule_set, "avgsw", arm_rule_avgsw, NULL);
  orc_rule_register (rule_set, "avguw", arm_rule_avguX, NULL);
  orc_rule_register (rule_set, "copyw", arm_rule_copyX, NULL);
  orc_rule_register (rule_set, "maxsw", arm_rule_maxsw, NULL);
  orc_rule_register (rule_set, "maxuw", arm_rule_maxuw, NULL);
  orc_rule_register (rule_set, "minsw", arm_rule_minsw, NULL);
  orc_rule_register (rule_set, "minuw", arm_rule_minuw, NULL);
  orc_rule_register (rule_set, "orb", arm_rule_orX, NULL);
  orc_rule_register (rule_set, "subw", arm_rule_subw, NULL);
  orc_rule_register (rule_set, "subssw", arm_rule_subssw, NULL);
  orc_rule_register (rule_set, "subusw", arm_rule_subusw, NULL);
  orc_rule_register (rule_set, "xorw", arm_rule_xorX, NULL);
  orc_rule_register (rule_set, "mullw", arm_rule_mullw, NULL);
  orc_rule_register (rule_set, "shrsw", arm_rule_shrsw, NULL);

  orc_rule_register (rule_set, "addl", arm_rule_addl, NULL);
  orc_rule_register (rule_set, "addssl", arm_rule_addssl, NULL);
  orc_rule_register (rule_set, "andl", arm_rule_andX, NULL);
  orc_rule_register (rule_set, "andnl", arm_rule_andnX, NULL);
  orc_rule_register (rule_set, "copyl", arm_rule_copyX, NULL);
  orc_rule_register (rule_set, "maxsl", arm_rule_maxsl, NULL);
  orc_rule_register (rule_set, "maxul", arm_rule_maxul, NULL);
  orc_rule_register (rule_set, "minsl", arm_rule_minsl, NULL);
  orc_rule_register (rule_set, "minul", arm_rule_minul, NULL);
  orc_rule_register (rule_set, "orb", arm_rule_orX, NULL);
  orc_rule_register (rule_set, "subl", arm_rule_subl, NULL);
  orc_rule_register (rule_set, "subssl", arm_rule_subssl, NULL);
  orc_rule_register (rule_set, "xorl", arm_rule_xorX, NULL);

}

