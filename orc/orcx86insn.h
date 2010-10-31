
#ifndef ORC_ORC_X86_INSN_H_
#define ORC_ORC_X86_INSN_H_

enum {
  ORC_X86_INSN_TYPE_SD,
  ORC_X86_INSN_TYPE_SHIFTIMM,
  ORC_X86_INSN_TYPE_SD2,
  ORC_X86_INSN_TYPE_SDI,
  ORC_X86_INSN_TYPE_SDI_REV,
  ORC_X86_INSN_TYPE_SD_REV
};

enum {
  ORC_X86_punpcklbw,
  ORC_X86_punpcklwd,
  ORC_X86_punpckldq,
  ORC_X86_packsswb,
  ORC_X86_pcmpgtb,
  ORC_X86_pcmpgtw,
  ORC_X86_pcmpgtd,
  ORC_X86_packuswb,
  ORC_X86_punpckhbw,
  ORC_X86_punpckhwd,
  ORC_X86_punpckhdq,
  ORC_X86_packssdw,
  ORC_X86_punpcklqdq,
  ORC_X86_punpckhqdq,
  ORC_X86_movdqa,
  ORC_X86_psraw,
  ORC_X86_psrlw,
  ORC_X86_psllw,
  ORC_X86_psrad,
  ORC_X86_psrld,
  ORC_X86_pslld,
  ORC_X86_psrlq,
  ORC_X86_psllq,
  ORC_X86_psrldq,
  ORC_X86_pslldq,
  ORC_X86_psrlq_reg,
  ORC_X86_pcmpeqb,
  ORC_X86_pcmpeqw,
  ORC_X86_pcmpeqd,
  ORC_X86_paddq,
  ORC_X86_pmullw,
  ORC_X86_psubusb,
  ORC_X86_psubusw,
  ORC_X86_pminub,
  ORC_X86_pand,
  ORC_X86_paddusb,
  ORC_X86_paddusw,
  ORC_X86_pmaxub,
  ORC_X86_pandn,
  ORC_X86_pavgb,
  ORC_X86_pavgw,
  ORC_X86_pmulhuw,
  ORC_X86_pmulhw,
  ORC_X86_psubsb,
  ORC_X86_psubsw,
  ORC_X86_pminsw,
  ORC_X86_por,
  ORC_X86_paddsb,
  ORC_X86_paddsw,
  ORC_X86_pmaxsw,
  ORC_X86_pxor,
  ORC_X86_pmuludq,
  ORC_X86_pmaddwd,
  ORC_X86_psadbw,
  ORC_X86_psubb,
  ORC_X86_psubw,
  ORC_X86_psubd,
  ORC_X86_psubq,
  ORC_X86_paddb,
  ORC_X86_paddw,
  ORC_X86_paddd,
  ORC_X86_pshufb,
  ORC_X86_phaddw,
  ORC_X86_phaddd,
  ORC_X86_phaddsw,
  ORC_X86_pmaddubsw,
  ORC_X86_phsubw,
  ORC_X86_phsubd,
  ORC_X86_phsubsw,
  ORC_X86_psignb,
  ORC_X86_psignw,
  ORC_X86_psignd,
  ORC_X86_pmulhrsw,
  ORC_X86_pabsb,
  ORC_X86_pabsw,
  ORC_X86_pabsd,
  ORC_X86_pmovsxbw,
  ORC_X86_pmovsxbd,
  ORC_X86_pmovsxbq,
  ORC_X86_pmovsxwd,
  ORC_X86_pmovsxwq,
  ORC_X86_pmovsxdq,
  ORC_X86_pmuldq,
  ORC_X86_pcmpeqq,
  ORC_X86_packusdw,
  ORC_X86_pmovzxbw,
  ORC_X86_pmovzxbd,
  ORC_X86_pmovzxbq,
  ORC_X86_pmovzxwd,
  ORC_X86_pmovzxwq,
  ORC_X86_pmovzxdq,
  ORC_X86_pmulld,
  ORC_X86_phminposuw,
  ORC_X86_pminsb,
  ORC_X86_pminsd,
  ORC_X86_pminuw,
  ORC_X86_pminud,
  ORC_X86_pmaxsb,
  ORC_X86_pmaxsd,
  ORC_X86_pmaxuw,
  ORC_X86_pmaxud,
  ORC_X86_pcmpgtq,
  ORC_X86_addps,
  ORC_X86_subps,
  ORC_X86_mulps,
  ORC_X86_divps,
  ORC_X86_sqrtps,
  ORC_X86_addpd,
  ORC_X86_subpd,
  ORC_X86_mulpd,
  ORC_X86_divpd,
  ORC_X86_sqrtpd,
  ORC_X86_cmpeqps,
  ORC_X86_cmpeqpd,
  ORC_X86_cmpltps,
  ORC_X86_cmpltpd,
  ORC_X86_cmpleps,
  ORC_X86_cmplepd,
  ORC_X86_cvttps2dq,
  ORC_X86_cvttpd2dq,
  ORC_X86_cvtdq2ps,
  ORC_X86_cvtdq2pd,
  ORC_X86_cvtps2pd,
  ORC_X86_cvtpd2ps,
  ORC_X86_minps,
  ORC_X86_minpd,
  ORC_X86_maxps,
  ORC_X86_maxpd,
  ORC_X86_psraw_imm,
  ORC_X86_psrlw_imm,
  ORC_X86_psllw_imm,
  ORC_X86_psrad_imm,
  ORC_X86_psrld_imm,
  ORC_X86_pslld_imm,
  ORC_X86_psrlq_imm,
  ORC_X86_psllq_imm,
  ORC_X86_psrldq_imm,
  ORC_X86_pslldq_imm,
  ORC_X86_pshufd,
  ORC_X86_pshuflw,
  ORC_X86_pshufhw,
  ORC_X86_palignr,
  ORC_X86_pinsrw,
  ORC_X86_movd_load,
  ORC_X86_movq_load,
  ORC_X86_movdqa_load,
  ORC_X86_movdqu_load,
  ORC_X86_movhps_load,
  ORC_X86_pextrw,
  ORC_X86_movd_store,
  ORC_X86_movq_store,
  ORC_X86_movdqa_store,
  ORC_X86_movdqu_store,
  ORC_X86_movntdq_store,
};



#define orc_sse_emit_punpcklbw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_punpcklbw, 0, a, b)
#define orc_sse_emit_punpcklwd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_punpcklwd, 0, a, b)
#define orc_sse_emit_punpckldq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_punpckldq, 0, a, b)
#define orc_sse_emit_packsswb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_packsswb, 0, a, b)
#define orc_sse_emit_pcmpgtb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pcmpgtb, 0, a, b)
#define orc_sse_emit_pcmpgtw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pcmpgtw, 0, a, b)
#define orc_sse_emit_pcmpgtd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pcmpgtd, 0, a, b)
#define orc_sse_emit_packuswb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_packuswb, 0, a, b)
#define orc_sse_emit_punpckhbw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_punpckhbw, 0, a, b)
#define orc_sse_emit_punpckhwd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_punpckhwd, 0, a, b)
#define orc_sse_emit_punpckhdq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_punpckhdq, 0, a, b)
#define orc_sse_emit_packssdw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_packssdw, 0, a, b)
#define orc_sse_emit_punpcklqdq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_punpcklqdq, 0, a, b)
#define orc_sse_emit_punpckhqdq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_punpckhqdq, 0, a, b)
#define orc_sse_emit_movdqa(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_movdqa, 0, a, b)
#define orc_sse_emit_psraw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psraw, 0, a, b)
#define orc_sse_emit_psrlw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psrlw, 0, a, b)
#define orc_sse_emit_psllw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psllw, 0, a, b)
#define orc_sse_emit_psrad(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psrad, 0, a, b)
#define orc_sse_emit_psrld(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psrld, 0, a, b)
#define orc_sse_emit_pslld(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pslld, 0, a, b)
#define orc_sse_emit_psrlq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psrlq, 0, a, b)
#define orc_sse_emit_psllq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psllq, 0, a, b)
#define orc_sse_emit_psrldq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psrldq, 0, a, b)
#define orc_sse_emit_pslldq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pslldq, 0, a, b)
#define orc_sse_emit_psrlq_reg(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psrlq_reg, 0, a, b)
#define orc_sse_emit_pcmpeqb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pcmpeqb, 0, a, b)
#define orc_sse_emit_pcmpeqw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pcmpeqw, 0, a, b)
#define orc_sse_emit_pcmpeqd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pcmpeqd, 0, a, b)
#define orc_sse_emit_paddq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_paddq, 0, a, b)
#define orc_sse_emit_pmullw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmullw, 0, a, b)
#define orc_sse_emit_psubusb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psubusb, 0, a, b)
#define orc_sse_emit_psubusw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psubusw, 0, a, b)
#define orc_sse_emit_pminub(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pminub, 0, a, b)
#define orc_sse_emit_pand(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pand, 0, a, b)
#define orc_sse_emit_paddusb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_paddusb, 0, a, b)
#define orc_sse_emit_paddusw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_paddusw, 0, a, b)
#define orc_sse_emit_pmaxub(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmaxub, 0, a, b)
#define orc_sse_emit_pandn(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pandn, 0, a, b)
#define orc_sse_emit_pavgb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pavgb, 0, a, b)
#define orc_sse_emit_pavgw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pavgw, 0, a, b)
#define orc_sse_emit_pmulhuw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmulhuw, 0, a, b)
#define orc_sse_emit_pmulhw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmulhw, 0, a, b)
#define orc_sse_emit_psubsb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psubsb, 0, a, b)
#define orc_sse_emit_psubsw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psubsw, 0, a, b)
#define orc_sse_emit_pminsw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pminsw, 0, a, b)
#define orc_sse_emit_por(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_por, 0, a, b)
#define orc_sse_emit_paddsb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_paddsb, 0, a, b)
#define orc_sse_emit_paddsw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_paddsw, 0, a, b)
#define orc_sse_emit_pmaxsw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmaxsw, 0, a, b)
#define orc_sse_emit_pxor(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pxor, 0, a, b)
#define orc_sse_emit_pmuludq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmuludq, 0, a, b)
#define orc_sse_emit_pmaddwd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmaddwd, 0, a, b)
#define orc_sse_emit_psadbw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psadbw, 0, a, b)
#define orc_sse_emit_psubb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psubb, 0, a, b)
#define orc_sse_emit_psubw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psubw, 0, a, b)
#define orc_sse_emit_psubd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psubd, 0, a, b)
#define orc_sse_emit_psubq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psubq, 0, a, b)
#define orc_sse_emit_paddb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_paddb, 0, a, b)
#define orc_sse_emit_paddw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_paddw, 0, a, b)
#define orc_sse_emit_paddd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_paddd, 0, a, b)
#define orc_sse_emit_pshufb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pshufb, 0, a, b)
#define orc_sse_emit_phaddw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_phaddw, 0, a, b)
#define orc_sse_emit_phaddd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_phaddd, 0, a, b)
#define orc_sse_emit_phaddsw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_phaddsw, 0, a, b)
#define orc_sse_emit_pmaddubsw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmaddubsw, 0, a, b)
#define orc_sse_emit_phsubw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_phsubw, 0, a, b)
#define orc_sse_emit_phsubd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_phsubd, 0, a, b)
#define orc_sse_emit_phsubsw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_phsubsw, 0, a, b)
#define orc_sse_emit_psignb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psignb, 0, a, b)
#define orc_sse_emit_psignw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psignw, 0, a, b)
#define orc_sse_emit_psignd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psignd, 0, a, b)
#define orc_sse_emit_pmulhrsw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmulhrsw, 0, a, b)
#define orc_sse_emit_pabsb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pabsb, 0, a, b)
#define orc_sse_emit_pabsw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pabsw, 0, a, b)
#define orc_sse_emit_pabsd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pabsd, 0, a, b)
#define orc_sse_emit_pmovsxbw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovsxbw, 0, a, b)
#define orc_sse_emit_pmovsxbd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovsxbd, 0, a, b)
#define orc_sse_emit_pmovsxbq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovsxbq, 0, a, b)
#define orc_sse_emit_pmovsxwd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovsxwd, 0, a, b)
#define orc_sse_emit_pmovsxwq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovsxwq, 0, a, b)
#define orc_sse_emit_pmovsxdq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovsxdq, 0, a, b)
#define orc_sse_emit_pmuldq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmuldq, 0, a, b)
#define orc_sse_emit_pcmpeqq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pcmpeqq, 0, a, b)
#define orc_sse_emit_packusdw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_packusdw, 0, a, b)
#define orc_sse_emit_pmovzxbw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovzxbw, 0, a, b)
#define orc_sse_emit_pmovzxbd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovzxbd, 0, a, b)
#define orc_sse_emit_pmovzxbq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovzxbq, 0, a, b)
#define orc_sse_emit_pmovzxwd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovzxwd, 0, a, b)
#define orc_sse_emit_pmovzxwq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovzxwq, 0, a, b)
#define orc_sse_emit_pmovzxdq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmovzxdq, 0, a, b)
#define orc_sse_emit_pmulld(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmulld, 0, a, b)
#define orc_sse_emit_phminposuw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_phminposuw, 0, a, b)
#define orc_sse_emit_pminsb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pminsb, 0, a, b)
#define orc_sse_emit_pminsd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pminsd, 0, a, b)
#define orc_sse_emit_pminuw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pminuw, 0, a, b)
#define orc_sse_emit_pminud(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pminud, 0, a, b)
#define orc_sse_emit_pmaxsb(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmaxsb, 0, a, b)
#define orc_sse_emit_pmaxsd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmaxsd, 0, a, b)
#define orc_sse_emit_pmaxuw(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmaxuw, 0, a, b)
#define orc_sse_emit_pmaxud(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pmaxud, 0, a, b)
#define orc_sse_emit_pcmpgtq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pcmpgtq, 0, a, b)
#define orc_sse_emit_addps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_addps, 0, a, b)
#define orc_sse_emit_subps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_subps, 0, a, b)
#define orc_sse_emit_mulps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_mulps, 0, a, b)
#define orc_sse_emit_divps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_divps, 0, a, b)
#define orc_sse_emit_sqrtps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_sqrtps, 0, a, b)
#define orc_sse_emit_addpd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_addpd, 0, a, b)
#define orc_sse_emit_subpd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_subpd, 0, a, b)
#define orc_sse_emit_mulpd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_mulpd, 0, a, b)
#define orc_sse_emit_divpd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_divpd, 0, a, b)
#define orc_sse_emit_sqrtpd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_sqrtpd, 0, a, b)
#define orc_sse_emit_cmpeqps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cmpeqps, 0, a, b)
#define orc_sse_emit_cmpeqpd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cmpeqpd, 0, a, b)
#define orc_sse_emit_cmpltps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cmpltps, 0, a, b)
#define orc_sse_emit_cmpltpd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cmpltpd, 0, a, b)
#define orc_sse_emit_cmpleps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cmpleps, 0, a, b)
#define orc_sse_emit_cmplepd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cmplepd, 0, a, b)
#define orc_sse_emit_cvttps2dq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cvttps2dq, 0, a, b)
#define orc_sse_emit_cvttpd2dq(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cvttpd2dq, 0, a, b)
#define orc_sse_emit_cvtdq2ps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cvtdq2ps, 0, a, b)
#define orc_sse_emit_cvtdq2pd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cvtdq2pd, 0, a, b)
#define orc_sse_emit_cvtps2pd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cvtps2pd, 0, a, b)
#define orc_sse_emit_cvtpd2ps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_cvtpd2ps, 0, a, b)
#define orc_sse_emit_minps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_minps, 0, a, b)
#define orc_sse_emit_minpd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_minpd, 0, a, b)
#define orc_sse_emit_maxps(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_maxps, 0, a, b)
#define orc_sse_emit_maxpd(p,a,b) orc_sse_emit_sysinsn(p, ORC_X86_maxpd, 0, a, b)
#define orc_sse_emit_psraw_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_psraw_imm, imm, 0, b)
#define orc_sse_emit_psrlw_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_psrlw_imm, imm, 0, b)
#define orc_sse_emit_psllw_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_psllw_imm, imm, 0, b)
#define orc_sse_emit_psrad_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_psrad_imm, imm, 0, b)
#define orc_sse_emit_psrld_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_psrld_imm, imm, 0, b)
#define orc_sse_emit_pslld_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_pslld_imm, imm, 0, b)
#define orc_sse_emit_psrlq_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_psrlq_imm, imm, 0, b)
#define orc_sse_emit_psllq_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_psllq_imm, imm, 0, b)
#define orc_sse_emit_psrldq_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_psrldq_imm, imm, 0, b)
#define orc_sse_emit_pslldq_imm(p,imm,b) orc_sse_emit_sysinsn(p, ORC_X86_pslldq_imm, imm, 0, b)
#define orc_sse_emit_pshufd(p,imm,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pshufd, imm, a, b)
#define orc_sse_emit_pshuflw(p,imm,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pshuflw, imm, a, b)
#define orc_sse_emit_pshufhw(p,imm,a,b) orc_sse_emit_sysinsn(p, ORC_X86_pshufhw, imm, a, b)
#define orc_sse_emit_palignr(p,imm,a,b) orc_sse_emit_sysinsn(p, ORC_X86_psalignr, imm, a, b)
#define orc_sse_emit_movdqu(p,offset,a,b) orc_sse_emit_sysinsn(p, ORC_X86_movdqu_load, 0, a, b)

#define orc_sse_emit_pinsrw_memoffset(p,imm,offset,a,b) orc_sse_emit_sysinsn_load_memoffset(p, ORC_X86_pinsrw, imm, offset, a, b)
#define orc_sse_emit_movd_load_memoffset(p,offset,a,b) orc_sse_emit_sysinsn_load_memoffset(p, ORC_X86_movd_load, 0, offset, a, b)
#define orc_sse_emit_movq_load_memoffset(p,offset,a,b) orc_sse_emit_sysinsn_load_memoffset(p, ORC_X86_movq_load, 0, offset, a, b)
#define orc_sse_emit_movdqa_load_memoffset(p,offset,a,b) orc_sse_emit_sysinsn_load_memoffset(p, ORC_X86_movdqa_load, 0, offset, a, b)
#define orc_sse_emit_movdqu_load_memoffset(p,offset,a,b) orc_sse_emit_sysinsn_load_memoffset(p, ORC_X86_movdqu_load, 0, offset, a, b)
#define orc_sse_emit_movhps_load_memoffset(p,offset,a,b) orc_sse_emit_sysinsn_load_memoffset(p, ORC_X86_movhps_load, 0, offset, a, b)

#define orc_sse_emit_pextrw_memoffset(p,imm,a,offset,b) orc_sse_emit_sysinsn_store_memoffset(p, ORC_X86_pextrw, imm, a, offset, b)
#define orc_sse_emit_movd_store_memoffset(p,a,offset,b) orc_sse_emit_sysinsn_store_memoffset(p, ORC_X86_movd_store, 0, a, offset, b)
#define orc_sse_emit_movq_store_memoffset(p,a,offset,b) orc_sse_emit_sysinsn_store_memoffset(p, ORC_X86_movq_store, 0, a, offset, b)
#define orc_sse_emit_movdqa_store_memoffset(p,a,offset,b) orc_sse_emit_sysinsn_store_memoffset(p, ORC_X86_movdqa_store, 0, a, offset, b)
#define orc_sse_emit_movdqu_store_memoffset(p,a,offset,b) orc_sse_emit_sysinsn_store_memoffset(p, ORC_X86_movdqu_store, 0, a, offset, b)
#define orc_sse_emit_movntdq_store_memoffset(p,a,offset,b) orc_sse_emit_sysinsn_store_memoffset(p, ORC_X86_movntdq_store, 0, a, offset, b)

#endif

