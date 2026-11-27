extern s32 sub_080059DC(s32, s32);
extern void sub_080146D0();
s32 sub_08014A34(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v = sub_080059DC(*(s32 *)((u8 *)arg0 + 0x10), *(s32 *)((u8 *)arg0 + 0x14));
    s32 sum = v;
    s32 res;
    sum = sum + arg2;
    if (sum < arg3) {
        sub_080146D0(arg0, arg1);
        res = 0;
    } else {
        sub_080146D0(arg0, arg1, arg3);
        res = 1;
    }
    return res;
}

/* Axis-aligned proximity test: return 1 only when the object's two position
 * fields (+8, +0xC) are each within maxDx/maxDy of the given point. */
s32 sub_08014A04(void *obj, s32 targetX, s32 targetY, s32 maxDx, s32 maxDy) {
    s32 x = *(s32 *)((u8 *)obj + 8);
    s32 y = *(s32 *)((u8 *)obj + 0xC);
    s32 dy = y - targetY;
    s32 dx = x - targetX;
    s32 absDy;
    if (dx < 0) dx = -dx;
    if (dx > maxDx) return 0;
    absDy = dy;
    if (absDy < 0) absDy = -absDy;
    if (absDy > maxDy) return 0;
    return 1;
}

extern s32 scaleByRandom(s32);
extern s32 signOf(s32);
void sub_080149A4(void *arg0, void *arg1, u16 *arg2, u16 arg3, s32 arg4) {
    u16 r6 = (u16)arg3;
    u16 r7 = (u16)arg4;
    s32 t;
    s16 a, b;
    s32 tmp, diff;
    t = *arg2;
    t = t - 1;
    *arg2 = t;
    if ((s32)((u16)t << 16) <= 0) {
        u16 f;
        if (signOf(*(s32 *)((u8 *)arg1 + 8)) > 0) {
            f = *(u16 *)((u8 *)arg0 + 2);
            f = 0x10 | f;
            *(u16 *)((u8 *)arg0 + 2) = f;
        } else {
            *(u16 *)((u8 *)arg0 + 2) &= 0xFFEF;
        }
        a = (s16)r6;
        b = (s16)r7;
        if (a == b) {
            *arg2 = r6;
        } else {
            tmp = a - 1;
            diff = b - tmp;
            *arg2 = r6 + scaleByRandom(diff);
        }
    }
}
