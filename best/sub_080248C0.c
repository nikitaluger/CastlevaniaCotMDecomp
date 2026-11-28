extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern s32 getSpriteFacingSign(u8 *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C29E8(u8 *, u8 *, s32, s32);
extern s32 signedRemainder(s16, s32);
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
    do { anim = work + 0x34; } while (0);
    body = work + 0x48;
    setAnimationFrame(sprite, anim, 5, 0);
    if ((signedRemainder(*(s16 *)body, 10) << 16) == 0) {
        if (getSpriteFacingSign(sprite) < 0) {
          s32 base_1;
          s32 trig_1;
            temp = (divInt32(*(s16 *)body, 10) << 16) >> 4;
            angle = (u16)(-0x6400 - temp);
            sprite = (u8 *)gTrigFuncTable;
            trig_1 = sub_080C31E0(angle + (0x80 << 7), *(s32 *)sprite) << 4;
            base_1 = 0xFFEC0000;
          x = *(s32 *)(work + 8) + (trig_1 + base_1);
        } else {
          s32 base_2;
          s32 trig_2;
            angle = (u16)((((u32)(divInt32(*(s16 *)body, 10) << 28)) + (0xE4 << 24)) >> 16);
            sprite = (u8 *)gTrigFuncTable;
            trig_2 = sub_080C31E0(angle + (0x80 << 7), *(s32 *)sprite) << 4;
            base_2 = 0xA0 << 13;
          x = *(s32 *)(work + 8) + (trig_2 + base_2);
        }
        
        y = (sub_080C31E0(angle, *(s32 *)sprite) * 20) + 0xFFD80000;
        y = *(s32 *)(work + 0x0C) + y;
        sub_08024E4C(x, y, angle, *(s32 *)(*(u8 **)(body + 8) + 4), *(s16 *)(work + 0x1C));
    }
    *(u16 *)body = *(u16 *)body + 1;
    if ((*(u8 *)anim & 2) != 0) {
        u8 *stepPtr;
        stepPtr = (u8 *)((s32)(*(s16 *)(self + 0x22)) * 2 + (s32)self);
        *(u8 *)(stepPtr + 0x17) = 0;
        ((void (*)(u8 *, u8 *, s32))(*(s32 *)gMenuScriptCallback))(self + 0x18, self + 0x22, 0);
    }
}
