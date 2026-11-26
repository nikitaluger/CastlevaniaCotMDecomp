extern u8 gMainWorkspace[];
extern void sub_08084994(void);

void sub_08084500(s32 a0, s32 a1, s32 a2, s32 a3)
{
    u8 v = gMainWorkspace[0x14ED];
    unsigned temp;
    gMainWorkspace[0x14EE] = v;
    v = (s32)temp;
    temp = (gMainWorkspace[0x14EE]) - 0x21;
    do { if (v > 0x80) sub_08084994(); } while (0);
    goto *((void **)0x0808454C)[v];
}
