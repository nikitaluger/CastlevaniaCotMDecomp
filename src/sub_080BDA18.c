extern void sub_08011460(s32, void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Script-step callback: issue an action command through sub_08011460, then when
 * the step counter reaches 8 reset it and dispatch the follow-up script. */
void sub_080BDA18(void *arg0) {
    u8 *self = (u8*)arg0;
    s32 component = *(s32*)(self + 0x38);
    u8 *data = *(u8 **)(self + 0x3C);
    s32 *lit;
    sub_08011460(component, data + 0x34, *(s32*)(data + 0x58));
    if (*(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) == 8) {
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
