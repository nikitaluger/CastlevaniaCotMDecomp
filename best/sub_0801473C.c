extern void sub_080C31E4(void *, void *, u32);
extern s32 sub_08014114(s32, s32, s32, s32, s32, s32);
extern u32 D_08671BB0;

void sub_0801F484(u8 *arg0) {
    u8 *r1 = *(u8 **)(arg0 + 0x3C);
    if (((s16 *)(r1 + 0x48))[5] != 0) {
        if (sub_08014114(*(s32 *)(r1 + 8), *(s32 *)(r1 + 0xC), -0x30, 0x30, -0x30, 0x30) != 0) {
            s16 idx = *(s16 *)(arg0 + 0x22);
            *(u8 *)(arg0 + idx * 2 + 0x19) = 0;
            {
                u32 v = D_08671BB0;
                sub_080C31E4(arg0 + 0x18, arg0 + 0x22, v);
            }
        }
    }
}

s32 sub_080147A4(u32 a0, u32 a1, u32 a2) {
    u32 m = 0xFFFF;
    a2 &= m;
    a0 &= m;
    a1 &= m;
    if (a0 > a1) {
        if (a2 < a0) {
            if (a2 <= a1) return 1;
        } else {
            return 1;
        }
    } else {
        if (a2 >= a0) {
            if (a2 <= a1) return 1;
        }
    }
    return 0;
}

s32 sub_0801476C(u32 a0, u32 a1, u32 a2) {
    u32 m = 0xFFFF;
    u32 lo;
    u32 hi;
    a2 &= m;
    lo = (a0 - a1) & m;
    hi = (a0 + a1) & m;
    if (lo > hi) {
        if (a2 < lo) {
            if (a2 <= hi) return 1;
        } else {
            return 1;
        }
    } else {
        if (a2 >= lo) {
            if (a2 <= hi) return 1;
        }
    }
    return 0;
}

s32 sub_0801473C(u32 a0, u32 a1) {
    u32 m = 0xFFFF;
    u32 d1;
    u32 d0;
    a0 &= m;
    a1 &= m;
    if (a0 == a1) {
        return 0;
    }
    d1 = (a0 - a1) & m;
    d0 = (a1 - a0) & m;
    if ((s32)d1 > (s32)d0) {
        return 1;
    }
    return -1;
}
