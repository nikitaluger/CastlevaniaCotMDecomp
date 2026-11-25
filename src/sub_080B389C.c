extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Set the current sub-state's timer to 0x78, rewind the action script, then
 * bump the sub-state's step counter and dispatch its handler. */
void sub_080B389C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *control = *(u8 **)(self + 0x3C) + 0x48;
    u8 zero = 0;
    void *script;
    const u32 *eventPtr;
    *(u16 *)(control + 0x1C) = 0x78;
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    eventPtr = (const u32 *)0x08671BB0;
    script = self + 0x18;
    sub_080C31E4(script, self + 0x22, *eventPtr);
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    script = (u8 *)script + (s32)*(s16 *)(self + 0x22) * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)script * 4));
}
