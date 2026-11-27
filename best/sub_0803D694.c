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
    u16 *work48;
    s32 facing;
    s32 ax;
    s16 a4a;

    sprite = *(void **)(self + 0x38);
    owner = *(u8 **)(self + 0x3C);
    work34 = owner + 0x34;
    work48 = (u16 *)(owner + 0x48);

    updateFacingFlipTimer(sprite, owner, work48, 0x5A, 0x78);
    setAnimationFrame((s32)sprite, work34, 0, 1);

    if (*(s16 *)(owner + 0x4A) == 0) {
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
                        goto end_store;
                    }
                }
            }
        }
    } else {
        goto L724;
    }

L724:
    {
        u16 v = *(u16 *)(owner + 0x4C);
        v--;
        *(u16 *)(owner + 0x4C) = v;
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
                    goto end_store;
                }
            }
            *(u16 *)(owner + 0x4C) = (u16)(scaleByRandom(0x97) + 0x1E);
        }
    }

    a4a = *(s16 *)(owner + 0x4A);
    if (a4a == 0) {
        if ((*(u16 *)(owner + 2) & 1) && (*(u16 *)(owner + 2) & 4)) {
            if (absXFromFocus(*(s32 *)(owner + 8)) == getSpriteFacingSign(sprite)) {
                *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
                sub_080C31E8(self + 0x18, self + 0x22, 2, *(u32 *)0x08671BD0);
                return;
            }
        }
    }

    ax = absXFromFocus(*(s32 *)(owner + 8));
    if (*(s16 *)(owner + 0x4A) == 0) {
        if (ax > 0x002FFFFF)
            *(s16 *)(owner + 0x4A) = 1;
        else
            goto check2;
    } else {
        if (ax > 0x400000) {
            *(s16 *)(owner + 0x4A) = 0;
        } else {
            if (*(u16 *)(owner + 2) & 1)
                goto check2;
            *(s16 *)(owner + 0x4A) = 0;
        }
    }

check2:
    ax = absXFromFocus(*(s32 *)(owner + 8));
    if (*(s16 *)(owner + 0x4A) == 0) {
        *(u32 *)(owner + 0x10) = (u32)ax << 16;
        return;
    } else {
        if (*(u16 *)(owner + 2) & 4) {
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            sub_080C31E8(self + 0x18, self + 0x22, 2, *(u32 *)0x08671BD0);
            return;
        }
        *(s16 *)(owner + 0x4A) = 0;
        return;
    }

end_store:
    *(s16 *)(owner + 0x4A) = 0;
    return;
}
