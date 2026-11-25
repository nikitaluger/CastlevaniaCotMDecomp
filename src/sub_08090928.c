s32 sub_08007EA8(u16);
void _call_via_r2(void *, void *, s32);

/* Scripted-actor step: when the flag test on the actor's movement state reports
 * set, apply the large negative X velocity (-0x8000), mark the state active,
 * clear the current script slot's action byte and dispatch the next command
 * through the script-advance callback at 0x08671BB0. */
void sub_08090928(void *self) {
    void *work = *(void **)((u8 *)self + 0x3C);
    void *moveState = (u8 *)work + 0x48;
    u8 zero;
    if (sub_08007EA8(*(u16 *)((u8 *)*(void **)((u8 *)moveState + 0x14) + 4)) != 0) {
        *(s32 *)((u8 *)work + 0x14) = (s32)0xFFFF8000;
        zero = 0;
        *(s16 *)((u8 *)moveState + 0x10) = 1;
        ((u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22)) * 2))[0x19] = zero;
        {
            s32 *advanceCb;
            advanceCb = (s32 *)0x08671BB0;
            _call_via_r2(self + 0x18, self + 0x22, *advanceCb);
        }
    }
}
