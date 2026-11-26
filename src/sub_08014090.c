struct S_02025FF0 {
    u8 _0[0x14EC];
    u8 mode;
    u8 _1[0x189C - 0x14ED];
    u32 blockMask;
};
extern struct S_02025FF0 gMainWorkspace;

struct Entry { s16 kind; u8 _[38]; };
extern struct Entry gEffectGfxTable[];

/* Look up an entry's kind by index and, according to the global mode, return
 * whether it is available: 0 when blocked by the mode, mask or kind, else 1. */
s32 sub_08014090(u16 index)
{
    s32 value = 0;

    switch (gMainWorkspace.mode) {
    case 0:
        goto ret_zero;
    case 1:
        value = gEffectGfxTable[(s16)index].kind;
        break;
    case 2:
        value = gEffectGfxTable[(s16)index].kind - 1;
        break;
    }
    if (value == 1) goto mask_check;
    if (value != 2) return 1;
ret_zero:
    return 0;
mask_check:
    if (gMainWorkspace.blockMask & value) goto ret_zero;
    return 1;
}
