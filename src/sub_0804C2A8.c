void setAnimationFrame(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Reset the actor's model animation to frame 0; if its restart flag is set,
 * set the timer word at +0x4C (timers[2]) to 6, clear this step's action byte
 * at +0x19 and run the handler at 0x08671BB0. */
void sub_0804C2A8(void *arg0) {
    void *model = *(void **)((u8 *)arg0 + 0x38);
    u8 *anim = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *animFlags = anim + 0x34;
    u16 *timers = (u16 *)(anim + 0x48);
    setAnimationFrame((s32)model, animFlags, 0, 0);
    if (2 & *animFlags) {
        s32 zero = 0;
        void **handlerTable;
        timers[2] = 6;
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = zero;
        handlerTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*handlerTable);
    }
}
