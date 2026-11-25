extern void sub_080C31E4(void *, void *, s32);
extern void sub_080A860C(void *, void *);

/* Script-step callback: update the control block shared with the companion,
 * then, once its trigger flag is set and its trigger counter has reached zero,
 * clear the current script step and advance the script. */
void sub_080A68D8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *scriptState = *(u8 **)(self + 0x3C);
    sub_080A860C(arg0, scriptState + 0x48);
    if (*(u8 *)(scriptState + 0x120) != 0 && *(u32 *)(scriptState + 0x110) == 0) {
        s32 *stepTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        stepTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *stepTable);
    }
}
