extern s32 sub_08005820(s32);
extern void sub_08098598(s32, void *, s32, void *);
extern void sub_080A1744(void *, void *);
extern void sub_080A1780(void *, void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Refresh an actor's display flags and animation parameters (including a
 * randomized value), then advance its action script: clear and bump the script
 * counter and dispatch the handler selected by the script. */
void sub_080A0F10(u8 *self) {
    u8 *actor = *(u8 **)(self + 0x38);
    u8 *enemy = *(u8 **)(self + 0x3C);
    u8 *timerPtr = 0x34 + enemy;
    u8 *work = enemy + 0x48;
    u8 *script;
    s32 zero;
    s32 *eventPtr;
    u32 clearOff, stepOff, dispatchOff;

    sub_08098598(0xB8 << 1, enemy + 0x60, 0xA, enemy + 0x64);
    sub_080A1744(actor, enemy);
    zero = 0;
    *(u8 *)(work + 0x16) = 1;
    *(s32 *)(self + 4) = sub_08005820(0xB4) + 0xB4;
    sub_080A1780(actor, timerPtr, work);
    clearOff = *(s16 *)(self + 0x22);
    clearOff <<= 1;
    clearOff += (u32)self;
    *(u8 *)(clearOff + 0x19) = zero;
    eventPtr = (s32 *)0x08671BB0;
    script = self + 0x18;
    sub_080C31E4(script, self + 0x22, *eventPtr);
    stepOff = *(s16 *)(self + 0x22);
    stepOff <<= 1;
    stepOff += (u32)self;
    *(u8 *)(stepOff + 0x19) += 1;
    dispatchOff = *(s16 *)(self + 0x22);
    dispatchOff <<= 1;
    script += dispatchOff;
    sub_080C31E0(self, *(void **)(*(u8 *)script * 4 + *(s32 *)(self + 0x14)));
}
