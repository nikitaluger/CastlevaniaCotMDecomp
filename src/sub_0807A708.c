extern u8 gMainWorkspace[];
extern s32 sub_08003740(s32, void *);
extern s32 sub_0806D450(void *, void *, void *);
extern s32 sub_0806D588(void *, void *);
extern void sub_08005E80(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Update an actor: bail out on the early condition, copy a global value into
 * its sprite, count down a timer and reset its motion when it expires, then
 * refresh graphics and dispatch the current state. */
void sub_0807A708(u8 *self) {
    u8 *object = *(u8 **)(self + 0x6C);
    u8 *state = object + 4;
    void *sprite = *(void **)(self + 0x38);
    if (sub_0806D450(self, sprite, state) > 0) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
        return;
    }
    {
        u8 *gGame = gMainWorkspace;
        s32 timer;
        *(u16 *)sprite = *(u16 *)(gGame + 0x18C2);
        timer = *(s32 *)(state + 0x10) - 1;
        *(s32 *)(state + 0x10) = timer;
        if (timer == 0) {
            *(s32 *)(state + 0x08) = timer;
            timer = 0xFFF80000;
            *(s32 *)(state + 0x0C) = timer;
            *(s32 *)(state + 0x10) = 0x10;
            *(u8 *)(*(u8 **)(state + 0x2C) + 1) = 1 & *(u8 *)(gGame + 0x1510);
            sub_08005E80(0x146);
            *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
            {
                const u32 *animCmd = (const u32 *)0x08671BB0;
                sub_080C31E4(self + 0x18, self + 0x22, *animCmd);
            }
        }
        sub_08003740((s32)object + 0x20, sprite);
        sub_0806D588(sprite, state);
        if (*(u8 *)(gGame + 0x173A) == 0x1C || (*(u8 *)(gGame + 0x14ED) == 0 && *(s32 *)(gGame + 0x10) != 0)) {
            sub_080C31E0(self, *(s32 *)(self + 0x24));
        }
    }
}
