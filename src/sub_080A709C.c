extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);

/* Clear the enemy's +0x144 field, rewind the current action-script sub-state,
 * then bump its step counter and dispatch its handler. */
void sub_080A709C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *script;
    s32 *eventPtr;
    *(u32 *)((u8 *)*(u32 *)(self + 0x3C) + 0x144) = 0;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    eventPtr = (s32 *)0x08671BB0;
    script = self + 0x18;
    sub_080C31E4(script, self + 0x22, *eventPtr);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    script += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)script * 4));
}
