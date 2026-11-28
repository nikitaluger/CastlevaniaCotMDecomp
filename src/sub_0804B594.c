extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 getSpriteFacingSign(void *);
extern s32 signOf(s32);
extern s32 absXFromFocus(s32);
extern void *sub_0804BBB4(s32, s32, s16, s16);
extern void sub_080C31E8(void *, void *, s32, s32);

void sub_0804B594(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animState = work + 0x34;
    s16 f;
    u16 facing;
    s32 tx, ty, sign;

    setAnimationFrame((s32)sprite, animState, 0x13, 0);
    if (animState[1] - 1 == 2 && *(u32 *)(animState + 4) == 1) goto spawn;
    if (*(s16 *)(work + 0x1C) == 0x49 || *(s16 *)(work + 0x1C) == 0x6C) {
        if (animState[1] - 1 == 5 && *(u32 *)(animState + 4) == 1) goto spawn;
    }
    goto finish;

spawn:
    f = getSpriteFacingSign(sprite);
    facing = (u16)f;
    if (f < 0)
        tx = *(s32 *)(work + 8) - 0x220000;
    else
        tx = *(s32 *)(work + 8) + 0x220000;
    ty = *(s32 *)(work + 0xC) - 0x40000;
    sub_0804BBB4(tx, ty, *(s16 *)(work + 0x1C), (s16)facing);

finish:
    if (!(animState[0] & 2)) return;
    sign = getSpriteFacingSign(sprite);
    if (sign != signOf(*(s32 *)(work + 8)) || absXFromFocus(*(s32 *)(work + 8)) <= 0x4FFFFF) {
        s32 *table;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        table = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *table);
    } else {
        s32 *table;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        table = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 0, *table);
    }
}
