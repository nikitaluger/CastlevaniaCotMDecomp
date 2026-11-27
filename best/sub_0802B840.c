extern u8 gMainWorkspace[];
extern s32 spawnBudgetedEffect(u32 arg0, s32 effect);
extern s32 getSpriteFacingSign(void *sprite);
extern s32 signOf(s32 value);
extern s32 absXFromFocus(void *actor);
extern s32 absYFromFocus(void *actor);
extern s32 divInt32(s32 num, s32 den);

void sub_0802B840(u8 *self) {
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *actor = *(u8 **)(self + 0x3C);
    s32 r6;
    s32 facing, sign, x, y;

    if (*(u8 *)(actor + 0x35) == 3) {
        r6 = spawnBudgetedEffect(*(u32 *)(gMainWorkspace + 0x1870), 0xC5);
        if (r6 != 0) {
            facing = getSpriteFacingSign(sprite);
            sign = signOf(*(s32 *)(actor + 8));
            x = absXFromFocus(actor) / 0x10000;
            y = absYFromFocus(actor) / 0x10000;
            if (x > 0xA0) x = 0xA0;
            if (y > 0x78) y = 0x78;
            if (sign == facing) {
                divInt32(x << 17, 0x60);
            }
        }
    }
}
