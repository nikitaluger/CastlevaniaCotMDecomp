extern void sub_08000E98(s32, void *, void *, s32, s32);
extern void sub_08001480(void *, s32);
extern void sub_08005E80(s32);
extern s32 sub_080C36E4(s32, s32);
struct S_02025FF0 { u8 pad0[0x50]; u8 b50; u8 b51; u8 pad52[6]; u32 b58; };
extern struct S_02025FF0 D_02025FF0;
extern u8 D_02025368[], D_02021E90[];
extern u8 D_0852F618[], D_0852FA18[], D_0852FE18[], D_08530218[], D_08530618[], D_08530A18[];
extern u8 D_0856B4A8[], D_0856B7A8[], D_085763D0[], D_08576990[];
extern u8 D_0857C500[], D_0857C620[], D_0857C740[], D_0857C860[];
extern u8 D_0858433C[], D_08584E3C[], D_0858593C[];
extern u8 D_085C7198[], D_085C7378[], D_085C7558[], D_085C7738[];
extern u8 D_085D6B90[], D_085D6F70[], D_085D7350[];
extern u8 D_085E2CC8[], D_085E2F28[], D_085E3188[], D_085E33E8[];
extern u8 D_085F08EC[], D_085F09CC[];
extern u8 D_0600B000[], D_0600B400[], D_0600C000[], D_0600D000[], D_0600E000[];
typedef struct { u32 src; u32 dst; u32 cnt; } DMA;
#define REG_DMA3 ((volatile DMA *)0x040000D4)
void sub_0808BBE0(void *arg0, s32 arg1)
{
    s32 r6 = arg1;
    u8 *r3 = D_02025368;
    u8 *r5 = (u8 *)&D_02025FF0;
    s32 v = (r5[0x50] << 8) + r5[0x51];
    s32 r4;
    if (v == 0x605) goto L_BEE0;
    if (v > 0x605) goto L_BC90;
    if (v == 0x50C) goto L_BEA8;
    if (v > 0x50C) goto L_BC58;
    if (v == 0x501) goto L_BDEC;
    if (v > 0x501) goto L_BC40;
    if (v == 0x002) goto L_BD10;
    if (v == 0x105) goto L_BD44;
    goto end;
L_BC40:
    switch (v) { case 0x508: case 0x509: goto L_BEA8; default: goto end; }
L_BC58:
    if (v == 0x518) goto L_BEA8;
    if (v > 0x518) goto L_BC78;
    if (v == 0x50F) goto L_BEA8;
    if (v == 0x512) goto L_BEA8;
    goto end;
L_BC78:
    switch (v) { case 0x600: case 0x601: case 0x602: case 0x603: goto L_BEE0; default: goto end; }
L_BC90:
    if (v > 0xA06) goto L_BCDC;
    switch (v) { case 0xA05: case 0xA06: goto L_BFC0; default: break; }
    if (v == 0x90A) goto L_C098;
    if (v > 0x90A) goto L_BCC4;
    if (v == 0x702) goto L_BF48;
    if (v == 0x714) goto L_BF48;
    goto end;
L_BCC4:
    if (v == 0xA01) goto L_BFC0;
    if (v == 0xA03) goto L_BFC0;
    goto end;
L_BCDC:
    if (v == 0xA0D) goto L_C02C;
    if (v > 0xA0D) goto L_BD00;
    switch (v) { case 0xA09: case 0xA0A: case 0xA0B: goto L_BFC0; default: goto end; }
L_BD00:
    if (v == 0xC01) goto L_C0E8;
    goto end;
L_BD10:
    { u8 *e = D_02021E90; u16 *p; u16 val;
      *(s32 *)(e + 0x125C) = 1;
      p = (u16 *)(e + 0x12E0); val = *p;
      if (val & 0x4000) *p = val | 0x1000; }
    goto end;
L_BD44:
    r4 = sub_080C36E4(r6, 0x18);
    if (*(u32 *)(r5 + 0x58) == 0) {
        if (r4 == 0) { sub_08000E98(1, D_0852F618, D_0600C000, 0x400, 0x10); goto end; }
        if (r4 == 8) { sub_08000E98(1, D_0852FA18, D_0600C000, 0x400, 0x10); goto end; }
        if (r4 == 16) { sub_08000E98(1, D_0852FE18, D_0600C000, 0x400, 0x10); goto end; }
    } else {
        if (r4 == 0) { sub_08000E98(1, D_08530218, D_0600C000, 0x400, 0x10); goto end; }
        if (r4 == 8) { sub_08000E98(1, D_08530618, D_0600C000, 0x400, 0x10); goto end; }
        if (r4 == 16) { sub_08000E98(1, D_08530A18, D_0600C000, 0x400, 0x10); goto end; }
    }
    goto end;
L_BDEC:
    { u8 *e = D_02021E90;
      *(s32 *)(e + 0x125C) = 1; *(s32 *)(e + 0x1308) = 0x10000; *(s32 *)(e + 0x130C) = 0x10000;
      *(u16 *)(e + 0x1314) = 0x100 - *(s16 *)(e + 0x12BA);
      *(u16 *)(e + 0x1316) = 0x58 - *(s16 *)(e + 0x12BE);
      *(u16 *)(e + 0x1310) = 0x40; *(u16 *)(e + 0x1312) = 0x58;
      *(u16 *)(e + 0x1318) = *(u16 *)(e + 0x1318) + 0x10; }
    r4 = sub_080C36E4(r6, 0x12);
    if (r4 == 0) { sub_08000E98(1, D_0856B4A8, D_0600B000, 0x300, 0x10); goto end; }
    if (r4 == 9) { sub_08000E98(1, D_0856B7A8, D_0600B000, 0x300, 0x10); goto end; }
    goto end;
L_BEA8:
    r4 = sub_080C36E4(r6, 0x12);
    if (r4 == 0) { sub_08000E98(1, D_085763D0, D_0600C000, 0x5C0, 0x10); goto end; }
    if (r4 == 9) { sub_08000E98(1, D_08576990, D_0600C000, 0x5C0, 0x10); goto end; }
    goto end;
L_BEE0:
    r4 = sub_080C36E4(r6, 0x28);
    if (r4 == 0) { sub_08000E98(1, D_0857C500, D_0600C000, 0x120, 0x10); goto end; }
    if (r4 == 10) { sub_08000E98(1, D_0857C620, D_0600C000, 0x120, 0x10); goto end; }
    if (r4 == 20) { sub_08000E98(1, D_0857C740, D_0600C000, 0x120, 0x10); goto end; }
    if (r4 == 30) { sub_08000E98(1, D_0857C860, D_0600C000, 0x120, 0x10); goto end; }
    goto end;
L_BF48:
    r4 = sub_080C36E4(r6, 0x130);
    if (r4 == 0x13) sub_08005E80(0x1BB);
    if (r4 == 0 || r4 == 0x26 || r4 == 0x4C || r4 == 0x72 || r4 == 0x98) { sub_08000E98(1, D_0858433C, D_0600D000, 0xB00, 0x10); goto end; }
    if (r4 == 0x13 || r4 == 0x5F) { sub_08000E98(1, D_08584E3C, D_0600D000, 0xB00, 0x10); goto end; }
    if (r4 == 0x39 || r4 == 0x85) { sub_08000E98(1, D_0858593C, D_0600D000, 0xB00, 0x10); goto end; }
    goto end;
L_BFC0:
    if (r3[0x3CF] == 1) { sub_08001480(arg0, 0x84); r3[0x3CF] = 2; }
    r4 = sub_080C36E4(r6, 0x1E);
    if (r4 == 0) { sub_08000E98(1, D_085D6B90, D_0600C000, 0x3E0, 0x10); goto end; }
    if (r4 == 10) { sub_08000E98(1, D_085D6F70, D_0600C000, 0x3E0, 0x10); goto end; }
    if (r4 == 20) { sub_08000E98(1, D_085D7350, D_0600C000, 0x3E0, 0x10); goto end; }
    goto end;
L_C02C:
    r4 = r6; if (r6 < 0) r4 = r6 + 0x1F; r4 >>= 5; r4 = r6 - (r4 << 5);
    if (r4 == 0) { sub_08000E98(1, D_085E2CC8, D_0600B400, 0x260, 0x10); goto end; }
    if (r4 == 8) { sub_08000E98(1, D_085E2F28, D_0600B400, 0x260, 0x10); goto end; }
    if (r4 == 16) { sub_08000E98(1, D_085E3188, D_0600B400, 0x260, 0x10); goto end; }
    if (r4 == 24) { sub_08000E98(1, D_085E33E8, D_0600B400, 0x260, 0x10); goto end; }
    goto end;
L_C098:
    r4 = sub_080C36E4(r6, 0x24);
    if (r4 == 0) { sub_08000E98(1, D_085C7198, D_0600E000, 0x1E0, 0x10); goto end; }
    if (r4 == 9) { sub_08000E98(1, D_085C7378, D_0600E000, 0x1E0, 0x10); goto end; }
    if (r4 == 18) { sub_08000E98(1, D_085C7558, D_0600E000, 0x1E0, 0x10); goto end; }
    if (r4 == 27) { sub_08000E98(1, D_085C7738, D_0600E000, 0x1E0, 0x10); goto end; }
    goto end;
L_C0E8:
    r4 = r6 & 0x3FF;
    if (r4 == 0x186) goto dma_08ec;
    if (r4 > 0x186) goto L_C120;
    if (r4 == 0x180) goto dma_09cc;
    if (r4 > 0x180) goto L_C110;
    if (r4 == 0x100) goto dma_09cc;
    if (r4 == 0x102) goto dma_08ec;
    goto end;
L_C110:
    if (r4 == 0x182) goto dma_08ec;
    if (r4 == 0x184) goto dma_09cc;
    goto end;
L_C120:
    if (r4 == 0x284) goto dma_09cc;
    if (r4 > 0x284) goto L_C136;
    if (r4 == 0x280) goto dma_09cc;
    if (r4 == 0x282) goto dma_08ec;
    goto end;
L_C136:
    if (r4 == 0x340) goto dma_09cc;
    if (r4 > 0x340) { if (r4 == 0x342) goto dma_08ec; goto end; }
    if (r4 == 0x286) goto dma_08ec;
    goto end;
dma_09cc:
    REG_DMA3->src = (u32)D_085F09CC; REG_DMA3->dst = 0x05000120; REG_DMA3->cnt = 0x80000040; (void)REG_DMA3->cnt; goto end;
dma_08ec:
    REG_DMA3->src = (u32)D_085F08EC; REG_DMA3->dst = 0x05000120; REG_DMA3->cnt = 0x80000040; (void)REG_DMA3->cnt; goto end;
end:
    return;
}
