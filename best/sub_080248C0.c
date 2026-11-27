extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern s32 getSpriteFacingSign(u8 *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C29E8(u8 *, u8 *, s32, s32);
extern s32 sub_080C36E4(s16, s32);
extern s32 divInt32(s32, s32);
extern void *sub_08024E4C(s32, s32, s32, s32, s32);
extern u32 gTrigFuncTable[];
extern u32 gMenuScriptCallback[];

void sub_080248C0(u8 *self) {
    u8 *sprite;
    u8 *work;
    u16 angle;
    u8 *anim;
    u8 *body;
    s32 temp;
    s32 trig;
    s32 base;
    s32 x;
    s32 y;

    sprite = *(u8 **)(self + 0x38);
    work = *(u8 **)(self + 0x3C);
    anim = work + 0x34;
    body = work + 0x48;
    setAnimationFrame(sprite, anim, 5, 0);
    if ((sub_080C36E4(*(s16 *)body, 10) << 16) == 0) {
        if (getSpriteFacingSign(sprite) < 0) {
            temp = (divInt32(*(s16 *)body, 10) << 16) >> 4;
            angle = (u16)(-0x6400 - temp);
            sprite = (u8 *)gTrigFuncTable;
            trig = sub_080C31E0(angle + (0x80 << 7), *(s32 *)sprite) << 4;
            base = 0xFFEC0000;
        } else {
            angle = (u16)((((u32)(sub_080C36E4(*(s16 *)body, 10) << 28)) + (0xE4 << 24)) >> 16);
            sprite = (u8 *)gTrigFuncTable;
            trig = sub_080C31E0(angle + (0x80 << 7), *(s32 *)sprite) << 4;
            base = 0xA0 << 13;
        }
        x = *(s32 *)(work + 8) + (trig + base);
        y = (sub_080C31E0(angle, *(s32 *)sprite) * 20) + 0xFFD80000;
        y = y + *(s32 *)(work + 0x0C);
        sub_08024E4C(x, y, angle, *(s32 *)(*(u8 **)(body + 8) + 4), *(s16 *)(work + 0x1C));
    }
    *(u16 *)body = *(u16 *)body + 1;
    if ((*(u8 *)anim & 2) != 0) {
        u8 *stepPtr = (u8 *)((s32)(*(s16 *)(self + 0x22)) * 2 + (s32)self);
        *(u8 *)(stepPtr + 0x17) = 0;
        sub_080C29E8(self + 0x18, self + 0x22, 0, (*(s32 *)gMenuScriptCallback));
    }
}
