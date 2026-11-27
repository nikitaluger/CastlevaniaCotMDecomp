extern u8 gMainWorkspace[];
extern s32 spawnBudgetedEffect(u32, s32);
extern s32 getSpriteFacingSign(void *);
extern s32 signOf(s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern s32 signY(s32);
extern s32 divInt32(s32, s32);
extern s32 scaleByRandom(u32);

void sub_0802C4C4(u8 *self) {
    void *sprite = *(void **)(self + 0x38);
    u8 *actor = *(u8 **)(self + 0x3C);
    u8 *track = actor + 0x34;
    u8 *effect;
    s32 facing, sign, x, y;
    s32 tmp;

    if (*(u8 *)(track + 1) != 2)
        return;
    if (*(u32 *)(track + 4) != (u32)(*(u16 *)(track + 2) - 1))
        return;

    effect = (u8 *)spawnBudgetedEffect(*(u32 *)(gMainWorkspace + 0x1870), 0xC8);
    if (effect == 0)
        return;

    facing = getSpriteFacingSign(sprite);
    sign = signOf(*(s32 *)(actor + 8));
    x = absXFromFocus(*(s32 *)(actor + 8));
    if (x < 0)
        x += 0xFFFF;
    x = x >> 16;
    y = absYFromFocus(*(s32 *)(actor + 0xC));
    if (y < 0)
        y += 0xFFFF;
    y = y >> 16;
    if (x > 0xA0)
        x = 0xA0;
    if (y > 0x78)
        y = 0x78;

    if (sign == facing) {
        tmp = divInt32(x << 16, 0x88);
    } else {
        tmp = scaleByRandom(0x1001);
        if (absYFromFocus(*(s32 *)(actor + 0xC)) >= 0) {
            /* placeholder */
        }
    }

    if (getSpriteFacingSign(sprite) >= 0) {
        if (absXFromFocus(*(s32 *)(actor + 8)) >= 0) {
            /* placeholder */
        }
    }

    (void)tmp;
}
