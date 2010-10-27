
#ifndef _ORC_ORC_SYSINSN_H_
#define _ORC_ORC_SYSINSN_H_

typedef struct _OrcSysInsn OrcSysInsn;
typedef struct _OrcSysOpcode OrcSysOpcode;

struct _OrcSysInsn {
  int opcode;
  int dest_reg;
  int src1_reg;
  int src2_reg;

  int immediate;

  int mem_reg;
  int memoffset;
  int indexreg;
  int shift;
};

struct _OrcSysOpcode {
  char name[16];
  int type;
  int flags;
  orc_uint32 code;
  int code2;
};


#define ORC_SYS_OPCODE_FLAG_FIXED (1<<0)


#endif

