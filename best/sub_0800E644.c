extern u8 gMenuState[];
extern u8 gGameStatus[];
extern u8 gCameraState[];
extern u32 gMenuScriptCallback;
extern u32 gMainObjTimerCallbacks;
void playSound(u32);
void sub_0800F4D4(u32, u32, u32);
void sub_0800F6BC(void);
void resetMapRender(void);
void setLayerTilemap(u32, u32);
void sub_080C31E8(void *, void *, u32, u32);
void sub_080C31E4(void *, void *, u32);

void sub_0800E644(u8 *arg0)
{
    u8 *b;
    int old9;
    int oldA;
    u16 flags_1;
    u16 flags_2;
    u16 flags_3;
    u16 flags_4;
    u16 temp;
    b = gGameStatus;
    old9 = (s8)gMenuState[0xF9];
    oldA = (s8)gMenuState[0xFA];

    {
        u8 *base;
        u16 *hp;
        u16 mask;
        base = gCameraState;
        hp = (u16 *)(base + 0x1470);

        flags_1 = *hp;
        do { mask = flags_1 & 0xC0; } while (0);
        if (mask != 0xC0 && mask != 0) {
            playSound(0xA0 << 1);
            gMenuState[0xF9] = (gMenuState[0xF9] + 1) & 1;
        }
    }
    {
        u8 *base;
        u16 *hp;
        u16 mask;
        base = gCameraState;
        hp = (u16 *)(base + 0x1470);

        flags_2 = *hp;
        do { { mask = flags_2 & 0x30; } } while (0);
        if (mask != 0x30) {
            if (mask != 0) playSound(0x139);
            flags_3 = *hp;
            do { if (flags_3 & 0x20) gMenuState[0xFA] = gMenuState[0xFA] - 1; } while (0);
            if (flags_3 & 0x10) gMenuState[0xFA] = gMenuState[0xFA] + 1;
            if ((s8)gMenuState[0xFA] <= 0) gMenuState[0xFA] = 0x0A;
            if ((s8)gMenuState[0xFA] > 0x0A) gMenuState[0xFA] = 1;
        }
    }
    if (old9 != (s8)gMenuState[0xF9] || oldA != (s8)gMenuState[0xFA]) {
        sub_0800F4D4(gMenuState[0xF9], gMenuState[0xFA], 0x84 << 2);
        sub_0800F6BC();
    }
    {
        u8 *base;
        u16 mask;
        base = gCameraState;

        temp = *(u16 *)(base + 0x146C);
        flags_4 = temp;
        do { mask = flags_4 & 2; } while (0);
        if (mask != 0) {
            playSound(0x14F);
            gMenuState[0x64] = 0;
            arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x17] = 0;
            { const u32 *gMenuScriptCallback_ptr = &gMenuScriptCallback; sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x0E, *gMenuScriptCallback_ptr); }
            return;
        }
        if ((flags_4 & 1) == 0) return;
        if (b[0x30C + ((s8)gMenuState[0xFA] + ((((s8)gMenuState[0xF9] + 1) & 1) * 10 - 1))] == 0) return;
        playSound(0x13B);
        resetMapRender();
        setLayerTilemap(0, 2);
        arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x19] = (u8)mask;
        { const u32 *gMainObjTimerCallbacks_ptr = &gMainObjTimerCallbacks; sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *gMainObjTimerCallbacks_ptr); }
    }
}
