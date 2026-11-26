extern u8 D_020278D0[];
extern u8 gGameStatus[];
extern u8 gCameraState[];
extern u32 D_08671BD8;
extern u32 gMainObjTimerCallback;
void playSound(u32);
void sub_0800F4D4(u32, u32, u32);
void sub_0800F6BC(void);
void resetMapRender(void);
void setLayerTilemap(u32, u32);
void sub_080C31E8(void *, void *, u32, u32);
void sub_080C31E4(void *, void *, u32);

void sub_0800E644(u8 *arg0)
{
    u8 *b = gGameStatus;
    int old9 = (s8)D_020278D0[0xF9];
    int oldA = (s8)D_020278D0[0xFA];
    u16 flags;
    u16 temp;

    {
        u8 *base = gCameraState;
        u16 *hp = (u16 *)(base + 0x1470);
        u16 mask;

        flags = *hp;
        mask = flags & 0xC0;
        if (mask != 0xC0 && mask != 0) {
            playSound(0xA0 << 1);
            D_020278D0[0xF9] = (D_020278D0[0xF9] + 1) & 1;
        }
    }
    {
        u8 *base = gCameraState;
        u16 *hp = (u16 *)(base + 0x1470);
        u16 mask;

        flags = *hp;
        mask = flags & 0x30;
        if (mask != 0x30) {
            if (mask != 0) playSound(0x139);
            flags = *hp;
            do { if (flags & 0x20) D_020278D0[0xFA] = D_020278D0[0xFA] - 1; } while (0);
            if (flags & 0x10) D_020278D0[0xFA] = D_020278D0[0xFA] + 1;
            if ((s8)D_020278D0[0xFA] <= 0) D_020278D0[0xFA] = 0x0A;
            if ((s8)D_020278D0[0xFA] > 0x0A) D_020278D0[0xFA] = 1;
        }
    }
    if (old9 != (s8)D_020278D0[0xF9] || oldA != (s8)D_020278D0[0xFA]) {
        sub_0800F4D4(D_020278D0[0xF9], D_020278D0[0xFA], 0x84 << 2);
        sub_0800F6BC();
    }
    {
        u8 *base = gCameraState;
        u16 mask;

        temp = *(u16 *)(base + 0x146C);
        flags = temp;
        mask = flags & 2;
        if (mask != 0) {
            playSound(0x14F);
            D_020278D0[0x64] = 0;
            arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x17] = 0;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x0E, D_08671BD8);
            return;
        }
        if ((flags & 1) == 0) return;
        if (b[0x30C + ((s8)D_020278D0[0xFA] + ((((s8)D_020278D0[0xF9] + 1) & 1) * 10 - 1))] == 0) return;
        playSound(0x13B);
        resetMapRender();
        setLayerTilemap(0, 2);
        arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x19] = (u8)mask;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, gMainObjTimerCallback);
    }
}
