extern u16 gFixedEffectLayerAttrs[];
s32 getSpriteFacingSign(void);
s32 fixedPointDistance(s32, s32);
void setPolarOffset(void *, s32, s32);

void sub_08019ED4(void *arg0, void *arg1) {
    u8 *r3 = *(u8 **)((u8 *)arg0 + 0x3C);
    u16 *r2 = gFixedEffectLayerAttrs;
    u16 v = *(u16 *)((u8 *)arg1 + 0x28);
    switch (v) {
    case 0x2D: r2 += 8; break;
    case 0x2E: r2 += 4; break;
    }
    *(vu16 *)(*(vu16 **)(r3 + 0x28) + 6) = r2[0];
    *(vu16 *)(*(vu16 **)(r3 + 0x28) + 8) = r2[1];
    *(vu16 *)(*(vu16 **)(r3 + 0x28) + 0xA) = r2[2];
    *(vu16 *)(*(vu16 **)(r3 + 0x28) + 0xC) = r2[3];
}

s32 sub_08014AE0(s32 unused, void *arg1, s32 arg2, s32 arg3) {
    s32 v;
    if (getSpriteFacingSign() < 0) {
        v = *(s32 *)((u8 *)arg1 + 0x10) + arg2;
        *(s32 *)((u8 *)arg1 + 0x10) = v;
        if (v >= -arg3) {
            *(s32 *)((u8 *)arg1 + 0x10) = -arg3;
            return 1;
        }
    } else {
        v = *(s32 *)((u8 *)arg1 + 0x10) - arg2;
        *(s32 *)((u8 *)arg1 + 0x10) = v;
        if (v <= arg3) {
            *(s32 *)((u8 *)arg1 + 0x10) = arg3;
            return 1;
        }
    }
    return 0;
}

/* Move obj's field at +0x10 by step in the direction reported by dirSrc's
 * flag bit, clamping it to +/- limit; return 1 when the clamp is hit. */
s32 sub_08014AA4(s32 dirSrc, void *obj, s32 step, s32 limit) {
    s32 value;
    if (getSpriteFacingSign() < 0) {
        value = *(s32 *)((u8 *)obj + 0x10) - step;
        *(s32 *)((u8 *)obj + 0x10) = value;
        if (value <= -limit) {
            *(s32 *)((u8 *)obj + 0x10) = -limit;
            return 1;
        }
    } else {
        value = *(s32 *)((u8 *)obj + 0x10) + step;
        *(s32 *)((u8 *)obj + 0x10) = value;
        if (value >= limit) {
            *(s32 *)((u8 *)obj + 0x10) = limit;
            return 1;
        }
    }
    return 0;
}

s32 sub_08014A6C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 tmp;
    s32 v;
    s32 lim;
    tmp = fixedPointDistance(*(s32 *)((u8 *)arg0 + 0x10), *(s32 *)((u8 *)arg0 + 0x14));
    v = tmp - arg2;
    lim = arg3;
    if (v <= lim) {
        setPolarOffset(arg0, arg1, lim);
        return 1;
    }
    setPolarOffset(arg0, arg1, v);
    return 0;
}
