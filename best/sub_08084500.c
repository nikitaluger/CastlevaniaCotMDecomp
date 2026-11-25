extern u8 D_02025FF0[];
extern void sub_08084994(void);

void sub_08084500(s32 a0, s32 a1, s32 a2, s32 a3)
{
    u8 v = D_02025FF0[0x14ED];
    D_02025FF0[0x14EE] = v;
    v = D_02025FF0[0x14EE];
    v -= 0x21;
    if (v > 0x80) sub_08084994();
    goto *((void **)0x0808454C)[v];
}
