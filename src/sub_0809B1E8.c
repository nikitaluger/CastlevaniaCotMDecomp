extern s32 sub_0801165C(void *, s32);
extern void sub_0808BB54(void);
extern void sub_0809C840(void *, void *);
extern s32 sub_080C31E0(void *, s32);

/* Advance an effect's sprite and counters, reverse its velocity periodically,
 * and drive the sound register or terminate the effect from the script step
 * byte. */
void sub_0809B1E8(u8 *arg0) {
    u8 *sprite = *(u8 **)(arg0 + 0x38);
    u8 *fields = *(u8 **)(arg0 + 0x3C);
    u8 *extra = fields + 0x48;
    s32 count;
    s32 phase;

    sub_0809C840(arg0, sprite);
    *(u16 *)(sprite + 4) = *(u16 *)(sprite + 4) + 0x10;
    *(u16 *)(sprite + 6) = *(u16 *)(sprite + 6) + 0x10;
    sub_0801165C(fields, 0);
    *(u16 *)(extra + 4) = *(u16 *)(extra + 4) + 0x217;
    {
        s32 *tablePtr = (s32 *)0x08671BFC;
        u16 index = *(u16 *)(extra + 4);
        *(s32 *)(fields + 0x0C) = *(s32 *)(fields + 0x48) - (sub_080C31E0((void *)index, *tablePtr) << 3);
    }
    count = *(u8 *)(extra + 6) + 1;
    *(u8 *)(extra + 6) = count;
    if ((count & 0x7F) == 0)
        *(s32 *)(fields + 0x10) = -*(s32 *)(fields + 0x10);
    if (!(1 & *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19))) {
        phase = *(u8 *)(extra + 7) + 1;
        *(u8 *)(extra + 7) = phase;
        if ((u8)phase == 0x0C) {
            sub_0808BB54();
            *(u8 *)(*(u8 **)(arg0 + 0x28) + 0x4C) = 1;
            sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
        } else {
            u8 *soundReg = (u8 *)0x03000830;
            u8 phaseVal = *(u8 *)(extra + 7);
            *(u16 *)(soundReg + 6) = ((phaseVal + 5) << 8) | (0x0B - phaseVal);
        }
    }
}
