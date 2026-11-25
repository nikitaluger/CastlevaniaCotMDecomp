extern s32 sub_08005910(s32 dy, s32 dx);
extern void sub_080113A8(s32 sprite, void *moverData);
extern void sub_0801165C(void *mover, s32 accel);
extern void sub_080146D0(void *mover, s32 angle, s32 speed);
extern s32 sub_0801473C(s32 currentAngle, s32 targetAngle);
extern void sub_080C31E4(void *, void *, s32);

struct S_02025FF0_B2034 { u8 _0[0x174C]; s32 f174C; s32 f1750; };
extern struct S_02025FF0_B2034 D_02025FF0;

/* Homing script step: steers the angle at self+0x7C toward the global target
 * point, ramps the speed at self+0x6C, applies the velocity to the mover, and
 * fires the step callback when the step flag reads 0x78. */
void sub_080B2034(u8 *self) {
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *mover = *(u8 **)(self + 0x3C);
    s32 targetAngle;
    s32 *scriptCb;
    s32 angle;
    sub_080113A8(sprite, mover + 0x34);
    angle = *(s32 *)(self + 0x7C);
    targetAngle = sub_08005910(D_02025FF0.f1750 - *(s32 *)(mover + 0xC), D_02025FF0.f174C - *(s32 *)(mover + 8));
    *(s32 *)(self + 0x7C) = *(s32 *)(self + 0x7C) + (sub_0801473C(angle, targetAngle) << 9);
    *(s32 *)(self + 0x6C) = *(s32 *)(self + 0x6C) + (0x80 << 4);
    if (*(s32 *)(self + 0x6C) > (0xC0 << 9)) {
        *(s32 *)(self + 0x6C) = 0xC0 << 9;
    }
    sub_080146D0(mover, *(s32 *)(self + 0x7C), *(s32 *)(self + 0x6C));
    sub_0801165C(mover, 0);
    if (*(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) == 0x78) {
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
        scriptCb = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptCb);
    }
}
