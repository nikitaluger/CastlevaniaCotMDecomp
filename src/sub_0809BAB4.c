extern void setSpriteFlipForDirection(void *a, s32 b);
extern void sub_080114A8(void *a, void *b, s32 c, s32 d);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Updates an entity's facing and world position from its state byte, then
 * converts that position into camera-relative screen coordinates. */
void sub_0809BAB4(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *parent = *(void **)(self + 0x38);
    u8 *component = (u8 *)*(void **)(self + 0x3C);
    u8 *component34 = component + 0x34;
    u16 flipFlags;
    s8 state;

    *(u32 *)(component + 0x10) = *(u32 *)(self + 0x6C);

    if ((s8)self[0x7C] == 1) {
        *(s32 *)(component + 0x08) = *(s32 *)(self + 0x4C);
        *(s32 *)(component + 0x0C) = *(s32 *)(self + 0x5C) + (s32)0xFFE80000;
        flipFlags = 0x800;
    } else {
        *(s32 *)(component + 0x08) = *(s32 *)(self + 0x4C);
        *(s32 *)(component + 0x0C) = *(s32 *)(self + 0x5C) + (s32)0xFFDC0000;
        flipFlags = 0xFC00;
    }
    *(u16 *)((u8 *)parent + 0x08) = flipFlags;

    setSpriteFlipForDirection(parent, *(s32 *)(component + 0x10));

    if ((s8)self[0x7C] != (s8)self[0x80]) {
        self[0x80] = self[0x7C];
        state = (s8)self[0x7C];
        if (state == 0) {
            *(u8 *)((u8 *)parent + 0x2A) &= 0xBF;
            goto COORD;
        }
        if (state < 0) goto COORD;
        if (state > 2) goto COORD;
        *(u8 *)((u8 *)parent + 0x2A) |= 0x40;
        sub_080114A8(parent, component34, 0x22, 0);
    }

COORD:
    {
        u8 *pt = gCameraState;
        u8 *pb = gMainWorkspace;
        u8 *base1;
        u8 *base2;
        u32 idx;

        pb += 0x18A8;

        idx = ((u32)*pb + 1) * 0x40;
        base1 = pt + 0x1278;
        *(u32 *)((u8 *)parent + 0x14) = *(u32 *)((u8 *)component + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);

        idx = ((u32)*pb + 1) * 0x40;
        base2 = pt + 0x127C;
        *(u32 *)((u8 *)parent + 0x18) = *(u32 *)((u8 *)component + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
