void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* While the object's guard flag at +0x4C is set, rewind the current action-script
 * sub-state, bump its step counter and dispatch its handler. */
void sub_080B6208(void *arg0) {
    u8 *self = arg0;
    if (*(u8 *)(self + 0x4C) != 0) {
        u8 *script;
        s32 *eventPtr;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        eventPtr = (s32 *)0x08671BB0;
        script = self + 0x18;
        sub_080C31E4(script, self + 0x22, *eventPtr);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        script = script + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)((u32)*script * 4 + *(u32 *)(self + 0x14)));
    }
}
