extern void sub_08011368(s32, void *, s32, s32);
extern s32 sub_080C36E4(s16, s32);
extern s32 sub_08014990(s32);
extern s32 sub_080C364C(s16, s32);
extern void *sub_08024E4C(s32, s32, s32, s32, s32);
extern s32 (*gTrigFuncTable[])(s32);
extern void (*gMenuScriptCallback)(void *, void *, s32);
extern void sub_080C31E4(void *, void *, u32);
extern s32 gMainObjTimerCallbacks[];

void sub_080245EC(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *state = *(u8 **)(self + 0x3C);
    u8 *anim = state + 0x34;
    u8 *control = state + 0x48;
    s32 a, angle, x, y;
    s16 step;
    s32 *ptr;

    sub_08011368(sprite, anim, 5, 0);
    if ((u16)sub_080C36E4(*(s16 *)control, 10) == 0) {
        if (sub_08014990(sprite) < 0) {
            a = sub_080C364C(*(s16 *)control, 10);
            angle = (u16)(0xFFFFA000 - (((s16)a) << 12));
            x = *(s32 *)(state + 8) + ((gTrigFuncTable[0](angle + 0x4000) << 4) + 0xFFEC0000);
            y = gTrigFuncTable[0](angle) * 20 + 0xFFD80000;
        } else {
            a = sub_080C364C(*(s16 *)control, 10);
            angle = (u16)((((u16)a) << 12) + 0xE000);
            x = *(s32 *)(state + 8) + ((gTrigFuncTable[0](angle + 0x4000) << 4) + 0x140000);
            y = gTrigFuncTable[0](angle) * 20 + 0xFFD80000;
        }
        y += *(s32 *)(state + 0x18);
        sub_08024E4C(y, x, angle, *(s32 *)(control + 4), *(s16 *)(state + 0x1c));
    } else {
        *(u16 *)control = *(u16 *)control + 1;
        if (*(u8 *)anim & 2) {
            *(u16 *)control = 0;
            if (*(u8 *)(state + 0x1c) == 0x45) {
                step = *(s16 *)(self + 0x22);
                *(u8 *)(self + step * 2 + 0x17) = 0;
                gMenuScriptCallback(self + 0x18, self + 0x22, 0);
            } else {
                step = *(s16 *)(self + 0x22);
                *(u8 *)(self + step * 2 + 0x19) = 0;
                ptr = &gMainObjTimerCallbacks;
                sub_080C31E4(self + 0x18, self + 0x22, *ptr);
            }
        }
    }
}
