/*
 * Actor script step: rotate a child offset about the actor using its work
 * angle to obtain a target point, then steer the work body toward it. Once
 * within tolerance, clear this step's flag and run the next-step callback
 * held in gMainObjTimerCallbacks.
 */
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);
extern void sub_08027A4C(void *, s32, s32 *, s32 *);
extern s32 gMainObjTimerCallbacks[];

void sub_0802754C(void *self) {
    s32 targetX;
    s32 targetY;
    void *work;
    s32 *stepCallback;

    work = *(void **)((u8 *)self + 0x3C);
    sub_08027A4C(self, *(s32 *)((u8 *)work + 0x50), &targetX, &targetY);
    if (sub_08014A04(work, targetX, targetY, 0xC0000, 0xC0000) == 1) {
        *(u8 *)((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x19) = 0;
        stepCallback = gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *stepCallback);
        return;
    }
    sub_08014B1C(work, (u8 *)work + 0x74, targetX, targetY);
}
