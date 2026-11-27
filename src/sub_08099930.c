extern void setObjectAnimation(s32, s32, s32, s32);
extern void setSpriteFacingToTarget(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* When the script step byte equals 0x3C, set the mover's field +0x6A to 0x81,
 * update its facing via setSpriteFacingToTarget and emit effect 0 via setObjectAnimation, then
 * reset the step byte and advance the script. */
void sub_08099930(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 a0 = *(s32 *)(self + 0x38);
    u8 *base = *(u8 **)(self + 0x3C);
    u8 *p34 = base + 0x34;
    s16 idx;
    idx = *(s16 *)(self + 0x22);
    if (*(u8 *)(self + idx * 2 + 0x19) == 0x3C) {
        u8 *p6A = base + 0x6A;
        s32 zero = 0;
        *p6A = 0x81;
        do {
            setSpriteFacingToTarget(a0, *(s32 *)(base + 8));
            setObjectAnimation(a0, (s32)p34, 0, 0);
            idx = *(s16 *)(self + 0x22);
        } while (0);
        *(u8 *)(self + idx * 2 + 0x19) = zero;
        {
            s32 *lit = (s32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 2, *lit);
        }
    }
}
