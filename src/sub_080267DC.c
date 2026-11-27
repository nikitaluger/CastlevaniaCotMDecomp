extern s32 fixedPointDistance(s32, s32);
extern s32 sub_08005910(s32, s32);
extern void sub_080269A8(void *, s32);
extern s32 (*gTrigFuncTable[])(s32);
extern void (*gMenuScriptCallback)(void *, void *, s32);

void sub_080267DC(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *box = work + 0x48;
    s32 dx = *(s32 *)(work + 8) - *(s32 *)(box + 0x68);
    s32 dy = *(s32 *)(work + 0xC) - *(s32 *)(box + 0x6C);
    s32 dist = fixedPointDistance(dx, dy);
    s16 step;

    if (dist <= 0x2FFFF) {
        *(s32 *)(box + 0x68) = *(s32 *)(work + 8);
        *(s32 *)(box + 0x6C) = *(s32 *)(work + 0xC);
    } else {
        s32 angle = sub_08005910(dy, dx);
        *(s32 *)(box + 0x68) = gTrigFuncTable[0](angle + 0x4000) * 3 + *(s32 *)(box + 0x68);
        *(s32 *)(box + 0x6C) = gTrigFuncTable[0](angle) * 3 + *(s32 *)(box + 0x6C);
    }

    step = *(s16 *)(self + 0x22);
    if (*(u8 *)(self + step * 2 + 0x19) > 0xA) {
        *(s32 *)(box + 0x70) = 0;
        *(s32 *)(box + 0x74) = 0;
        sub_080269A8(self, 0x20);
        step = *(s16 *)(self + 0x22);
        *(u8 *)(self + step * 2 + 0x17) = 0;
        gMenuScriptCallback(self + 0x18, self + 0x22, 1);
    }
}
