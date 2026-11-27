extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_080C36E4(s16, s32);
extern s32 divInt32(s16, s32);
extern s32 getSpriteFacingSign(s32);
extern void *sub_08024E4C(s32, s32, s32, s32, s32);
extern s32 (*gTrigFuncTable[])(s32);
extern void sub_080C31E4(void *, void *, u32);

void sub_08024768(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *state = *(u8 **)(self + 0x3C);
    u8 *anim = state + 0x34;
    u8 *control = state + 0x48;
    s32 angle, t, x, y;
    s16 step;

    setAnimationFrame(sprite, anim, 9, 0);
    if ((u16)sub_080C36E4(*(s16 *)control, 10) == 0) {
        if (getSpriteFacingSign(sprite) < 0) {
            angle = (u16)((((u32)divInt32(*(s16 *)control, 10) << 28) + 0x64000000) >> 16);
            t = (gTrigFuncTable[0](angle + 0x4000) << 4) + 0xFFEC0000;
        } else {
            angle = (u16)(0x1C00 - ((divInt32(*(s16 *)control, 10) << 16) >> 4));
            t = (gTrigFuncTable[0](angle + 0x4000) << 4) + 0x140000;
        }
        x = *(s32 *)(state + 8) + t;
        y = gTrigFuncTable[0](angle) * 20 + 0xFFD80000 + *(s32 *)(state + 0xC);
        sub_08024E4C(x, y, angle, *(s32 *)(*(u8 **)(control + 8) + 4), *(s16 *)(state + 0x1c));
    }
    *(u16 *)control = *(u16 *)control + 1;
    if (*(u8 *)anim & 2) {
        *(u16 *)control = 0;
        if (*(s16 *)(state + 0x1c) == 0x46) {
            u32 cb;
            step = *(s16 *)(self + 0x22);
            *(u8 *)(self + step * 2 + 0x17) = 0;
            cb = *(u32 *)0x08671BD8;
            ((void (*)(void *, void *, u32))cb)(self + 0x18, self + 0x22, 0);
        } else {
            s16 step2;
            step2 = *(s16 *)(self + 0x22);
            *(u8 *)(self + step2 * 2 + 0x19) = 0;
            sub_080C31E4(self + 0x18, self + 0x22, *(u32 *)0x08671BB0);
        }
    }
}
