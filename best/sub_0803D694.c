extern void updateFacingFlipTimer(void *, void *, u16 *, u16, s32);
extern void setAnimationFrame(s32, void *, u16, u8);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern s32 signOf(s32);
extern s32 getSpriteFacingSign(void *);
extern void sub_080C31E8(void *, void *, u32, u32);
extern s32 scaleByRandom(s32);

void sub_0803D694(void *obj) {
    u8 *self = (u8 *)obj;
    void *sprite;
    u8 *owner;
    u8 *work34;
    u8 *r7;
    s32 facing;
    s32 ax;

    sprite = *(void **)(self + 0x38);
    owner = *(u8 **)(self + 0x3C);
    work34 = owner + 0x34;
    r7 = owner + 0x48;

    updateFacingFlipTimer(sprite, owner, (u16 *)r7, 0x5A, 0x78);
    setAnimationFrame((s32)sprite, work34, 0, 1);

    if (*(s16 *)(r7 + 2) == 0) {
        if (absXFromFocus(*(s32 *)(owner + 8)) <= 0x300000) {
            if (absYFromFocus(*(s32 *)(owner + 0xC)) <= 0x300000) {
                if (signOf(*(s32 *)(owner + 8)) == getSpriteFacingSign(sprite)) {
                    if (*(u16 *)(owner + 2) & 4) {
                        facing = getSpriteFacingSign(sprite);
                        if (facing > 0)
                            *(u32 *)(owner + 0x10) = 0x8000;
                        else
                            *(u32 *)(owner + 0x10) = 0xFFFF8000;

                        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
                        sub_080C31E8(self + 0x18, self + 0x22, 1, *(u32 *)0x08671BD0);
                        *(s16 *)(r7 + 2) = 0;
                        return;
                    }
                }
            }
        }
        goto L724;
    }

L724:
    {
        u16 v = *(u16 *)(r7 + 4);
        v--;
        *(u16 *)(r7 + 4) = v;
        if ((s16)v < 0) {
            if (*(u16 *)(owner + 2) & 4) {
                if (absXFromFocus(*(s32 *)(owner + 8)) == getSpriteFacingSign(sprite)) {
                    facing = getSpriteFacingSign(sprite);
                    if (facing > 0)
                        *(u32 *)(owner + 0x10) = 0x8000;
                    else
                        *(u32 *)(owner + 0x10) = 0xFFFF8000;

                    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
                    sub_080C31E8(self + 0x18, self + 0x22, 1, *(u32 *)0x08671BD0);
                    *(s16 *)(r7 + 2) = 0;
                    return;
                }
            }
            *(u16 *)(r7 + 4) = (u16)(scaleByRandom(0x97) + 0x1E);
        }
    }

    if (*(s16 *)(r7 + 2) == 0) {
        if ((*(u16 *)(owner + 2) & 1) && (*(u16 *)(owner + 2) & 4)) {
            if (absXFromFocus(*(s32 *)(owner + 8)) == getSpriteFacingSign(sprite)) {
                *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
                goto script2;
            }
        }
    }

    ax = absXFromFocus(*(s32 *)(owner + 8));
    if (*(s16 *)(r7 + 2) == 0) {
        if (ax <= 0x002FFFFF)
            *(s16 *)(r7 + 2) = 1;
    } else {
        if (ax > 0x400000) {
            *(s16 *)(r7 + 2) = 0;
        } else if (*(u16 *)(owner + 2) & 1) {
            *(s16 *)(r7 + 2) = 0;
        }
    }

    ax = absXFromFocus(*(s32 *)(owner + 8));
    if (*(s16 *)(r7 + 2) == 0) {
        *(u32 *)(owner + 0x10) = ((u32)ax) << 16;
        return;
    }

    if (*(u16 *)(owner + 2) & 4) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
script2:
        sub_080C31E8(self + 0x18, self + 0x22, 2, *(u32 *)0x08671BD0);
        return;
    }

    *(s16 *)(r7 + 2) = 0;
}
