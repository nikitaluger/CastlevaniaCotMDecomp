void sub_08011368(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Advance the actor's model animation by 0x1A frames; if its restart flag is
 * set, reload the 0x1E timer, clear the level's repeat counter and run the
 * handler at 0x08671BB0. */
void sub_0801D534(void *arg0) {
    void *model = *(void **)((u8 *)arg0 + 0x38);
    u8 *anim = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *animFlags = anim + 0x34;
    u16 *timer = (u16 *)(anim + 0x48);
    sub_08011368((s32)model, animFlags, 0x1A, 0);
    if (2 & *animFlags) {
        s32 zero = 0;
        void **handlerTable;
        *timer = 0x1E;
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = zero;
        handlerTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*handlerTable);
    }
}
