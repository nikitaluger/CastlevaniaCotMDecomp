extern void sub_0801165C(void *, s32);
extern void sub_080146D0(void *, s32, s32);
extern void sub_080B1960(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Move a scripted actor in a curving arc: ramp its speed toward a target,
 * turn it a little each frame, integrate the motion, then dispatch a
 * follow-up script when the current step byte reaches 0x70. */
void sub_080B1534(u8 *self) {
    u8 *body;
    u8 *motion;
    u8 *param;
    s32 speed;

    body = *(u8 **)(self + 0x3C);
    motion = body + 0x48;
    param = *(u8 **)(self + 0x4C);

    if (*(s32 *)(body + 0x14) < 0) {
        sub_080B1960(body, param);
    }

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) <= 0x5F) {
        speed = *(s32 *)(motion + 0x10) + 0x2000;
        *(s32 *)(motion + 0x10) = speed;
        if (speed > 0x20000) {
            *(s32 *)(motion + 0x10) = 0x20000;
        }
    } else {
        speed = *(s32 *)(motion + 0x10) - 0x2000;
        *(s32 *)(motion + 0x10) = speed;
        if (speed < 0) {
            *(s32 *)(motion + 0x10) = 0;
        }
    }

    *(s32 *)(motion + 0x14) = *(s32 *)(motion + 0x14) - ((s8)*(u8 *)(param + 0x35) << 8);
    sub_080146D0(body, *(s32 *)(motion + 0x14), *(s32 *)(motion + 0x10));
    sub_0801165C(body, 0);

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x70) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *nv = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}
