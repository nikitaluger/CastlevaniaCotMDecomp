extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_08014114(s32, s32, s32, s32, s32, s32);
extern s32 scaleByRandom(s32);
extern s32 getSpriteFacingSign(s32);
extern s32 signOf(s32);
extern s32 absXFromFocus(s32);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gScriptStepCallbacks;

void sub_0804B140(u8 *entity) {
    s32 sprite = *(s32 *)(entity + 0x38);
    u8 *state = *(u8 **)(entity + 0x3C);
    u8 *animTrack = state + 0x34;
    u8 *p48 = state + 0x48;
    s32 t;
    u8 *stepPtr;
    u8 *flagsStepPtr;
    s32 zero;

    setAnimationFrame(sprite, animTrack, 0, 1);
    t = *(u16 *)(p48 + 2) - 1;
    *(u16 *)(p48 + 2) = t;
    if ((t << 16) < 0) {
        *(u16 *)(p48 + 2) = 0xB4;
        if (sub_08014114(*(s32 *)(state + 8), *(s32 *)(state + 0xC), -0x12, 0x12, -0x10, -8) == 1) {
            *(u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity + 0x19) = 0;
            { void **callback = &gScriptStepCallbacks;
              sub_080C31E8(entity + 0x18, entity + 0x22, 2, *callback); }
            return;
        }
    }
    if ((*(u16 *)(state + 2) & 1) == 0) goto timerPath;
    flagsStepPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    zero = 0;
    stepPtr = flagsStepPtr;
    goto setByte;
timerPath:
    t = *(u16 *)p48 - 1;
    *(u16 *)p48 = t;
    if ((t << 16) < 0) {
        *(u16 *)p48 = scaleByRandom(0x5B) + 0x5A;
        if (getSpriteFacingSign(sprite) != signOf(*(s32 *)(state + 8))) {
            *(u16 *)(sprite + 2) = *(u16 *)(sprite + 2) ^ 0x10;
            goto tail;
        }
        if (absXFromFocus(*(s32 *)(state + 8)) > 0x4FFFFF) goto tail;
        stepPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        zero = 0;
setByte:
        *(u8 *)(stepPtr + 0x19) = zero;
        { void **callback = &gScriptStepCallbacks;
          sub_080C31E8(entity + 0x18, entity + 0x22, 1, *callback); }
        return;
    }
tail:
    if (getSpriteFacingSign(sprite) > 0)
        *(s32 *)(state + 0x10) = 0xC0 << 6;
    else
        *(s32 *)(state + 0x10) = -0x3000;
}
