extern u16 gFixedEffectLayerAttrs[];
s32 getSpriteFacingSign(void);
s32 fixedPointDistance(s32, s32);
void sub_080146D0(void *, s32, s32);

/* Picks the speed-table entry for the object's mode (0x2D/0x2E) and copies its
 * four values into the block at obj->0x28 + 6. */
void sub_08019ED4(void *self, void *source) {
    u8 *obj = *(u8 **)((u8 *)self + 0x3C);
    u16 *speeds = gFixedEffectLayerAttrs;
    u16 mode = *(u16 *)((u8 *)source + 0x28);
    switch (mode) {
    case 0x2D: speeds += 8; break;
    case 0x2E: speeds += 4; break;
    }
    *(vu16 *)(*(vu16 **)(obj + 0x28) + 6) = speeds[0];
    *(vu16 *)(*(vu16 **)(obj + 0x28) + 8) = speeds[1];
    *(vu16 *)(*(vu16 **)(obj + 0x28) + 0xA) = speeds[2];
    *(vu16 *)(*(vu16 **)(obj + 0x28) + 0xC) = speeds[3];
}

/* Steps the value at pos+0x10 by step, in the direction given by self's facing
 * bit, clamping it at the limit on the far side and returning 1 when it hits. */
s32 sub_08014AE0(s32 self, void *pos, s32 step, s32 limit) {
    s32 value;
    if (getSpriteFacingSign() < 0) {
        value = *(s32 *)((u8 *)pos + 0x10) + step;
        *(s32 *)((u8 *)pos + 0x10) = value;
        if (value >= -limit) {
            *(s32 *)((u8 *)pos + 0x10) = -limit;
            return 1;
        }
    } else {
        value = *(s32 *)((u8 *)pos + 0x10) - step;
        *(s32 *)((u8 *)pos + 0x10) = value;
        if (value <= limit) {
            *(s32 *)((u8 *)pos + 0x10) = limit;
            return 1;
        }
    }
    return 0;
}

/* Mirror of sub_08014AE0: steps the value at pos+0x10 away from zero toward
 * ±limit in the direction given by self's facing bit, returns 1 on clamping. */
s32 sub_08014AA4(s32 self, void *pos, s32 step, s32 limit) {
    s32 value;
    if (getSpriteFacingSign() < 0) {
        value = *(s32 *)((u8 *)pos + 0x10) - step;
        *(s32 *)((u8 *)pos + 0x10) = value;
        if (value <= -limit) {
            *(s32 *)((u8 *)pos + 0x10) = -limit;
            return 1;
        }
    } else {
        value = *(s32 *)((u8 *)pos + 0x10) + step;
        *(s32 *)((u8 *)pos + 0x10) = value;
        if (value >= limit) {
            *(s32 *)((u8 *)pos + 0x10) = limit;
            return 1;
        }
    }
    return 0;
}

/* Shrinks the polar vector held at out+0x10/+0x14 by step, clamps its radius to
 * limit and rebuilds x/y from angle; returns 1 when the limit is reached. */
s32 sub_08014A6C(void *out, s32 angle, s32 step, s32 limit) {
    s32 radius;
    s32 target;
    s32 length;
    radius = fixedPointDistance(*(s32 *)((u8 *)out + 0x10), *(s32 *)((u8 *)out + 0x14));
    target = radius - step;
    length = limit;
    if (target <= length) {
        sub_080146D0(out, angle, length);
        return 1;
    }
    sub_080146D0(out, angle, target);
    return 0;
}
