extern s32 sub_08011368(s32, u8 *, s32, s32);
extern s32 sub_080113A8(s32, u8 *);
extern s32 sub_08011898(u8 *, s32);
extern s32 sub_08014588(s32, s32);
extern s32 sub_0809856C(s32, u8 *, s32);
extern s32 sub_080B72CC(u8 *);
extern void sub_080C31E4(void *, void *, s32);

/* Script-step callback: plays a periodic sound and updates companion/motion
 * state; when a control flag is set it copies a four-halfword data block onto a
 * target object, sets a timer, resets the step and redirects the script. */
void sub_080B6CCC(u8 *self) {
    u8 *companion = *(u8 **)(self + 0x38);
    u8 *scriptState = *(u8 **)(self + 0x3C);
    u8 *stateArg = scriptState + 0x34;
    s32 *pHelperTable;

    sub_0809856C(0x18C, self + 0x7C, 0x0F);
    sub_08011898(scriptState, 0x4000);
    sub_080113A8(companion, stateArg);
    sub_080B72CC(self);
    if (*(u8 *)stateArg & 0x02) {
        u16 *timerPtr;
        u8 zero;
        u16 duration;
        sub_08011368(companion, stateArg, 0x28, 1);
        sub_08014588(*(s32 *)(scriptState + 0x28), 0x08102D2C);
        timerPtr = (u16 *)(self + 0x74);
        zero = 0;
        duration = 0x12C;
        *timerPtr = duration;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        pHelperTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *pHelperTable);
    }
}
