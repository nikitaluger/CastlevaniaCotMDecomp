extern void sub_080C31E8(void *, void *, u16, s32);
extern u16 D_08102EC8[];
extern s32 D_08671BD8[];

/* Clear the current script step's flag byte, then advance the script with a
 * value looked up in D_08102EC8 from the work-state field at +0x44. */
void sub_080BA0F4(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *state = *(u8 **)(self + 0x3C) + 0x48;
    s32 *stepTable;
    u8 *script;
    u8 *stepIndex;
    u16 *valueTbl;

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
    stepTable = D_08671BD8;
    script = self + 0x18;
    stepIndex = self + 0x22;
    valueTbl = D_08102EC8;
    sub_080C31E8(script, stepIndex, valueTbl[*(u32 *)(state + 0x44)], *stepTable);
}
