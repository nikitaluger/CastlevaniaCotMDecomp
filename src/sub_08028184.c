/*
 * Actor script step: play animation frame 0 and move the body toward its
 * target point. Within one unit of the target, clear the step counter and run
 * the next script step; otherwise steer toward the target and update the
 * sprite's facing flag from the movement angle.
 */
extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);
extern void sub_0801468C(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 D_08671BD0;

void sub_08028184(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animator;
    u8 *move;

    animator = work + 0x34;
    move = work + 0x48;  /* move record: target X/Y at +8/+0xC, angle at +0x20 */
    sub_08011368(sprite, animator, 0, 1);
    if (sub_08014A04(work, *(s32 *)(move + 8), *(s32 *)(move + 0x0C), 0x80000, 0x80000) == 1) {
        s32 *stepCallback;
        *(s8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = 0;
        stepCallback = &D_08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *stepCallback);
        return;
    }
    sub_08014B1C(work, work + 0x64, *(s32 *)(move + 8), *(s32 *)(move + 0x0C));
    sub_0801468C(sprite, *(s32 *)(move + 0x20));
}
