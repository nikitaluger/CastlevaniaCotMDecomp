/*
 * Actor script step: stop the actor (velocity, flags, linked object), play
 * animation 3, clear the current action byte, then advance the script and
 * dispatch the handler of the next step from the actor's step table.
 */
extern s32 sub_08011368(s32, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_080B5B10(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite;
    u8 *work;
    u8 *animator;
    u8 zero;
    u8 *scriptEntry;
    const u32 *stepCallback;

    sprite = *(s32 *)(self + 0x38);
    work = *(u8 **)(self + 0x3C);
    animator = work + 0x34;
    zero = 0;
    *(s32 *)(self + 0x7C) = zero;
    *(u8 *)(*(u8 **)(work + 0x28) + 1) = zero;
    *(s32 *)(work + 0x10) = zero;
    *(s32 *)(work + 0x14) = 0xFFFE8000;
    sub_08011368(sprite, (s32)animator, 3, 1);

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;

    stepCallback = (const u32 *)0x08671BB0;
    scriptEntry = self + 0x18;
    sub_080C31E4(scriptEntry, self + 0x22, *stepCallback);

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    scriptEntry += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)scriptEntry * 4));
}
