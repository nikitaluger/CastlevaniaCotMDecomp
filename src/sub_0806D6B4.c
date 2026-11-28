extern s32 getMapTileAttribute(void *, s32, s32);
extern u8 gMainWorkspace[];
extern u8 gTilemapPages[];

/* Horizontal move with vertical collision resolution: shift x by its 16.16
 * velocity, then, if the new spot is blocked, step y upward until free (return
 * 1 if never free); otherwise step y downward until the floor is hit (return 2
 * if left airborne). Return 0 once y had to be adjusted. */
s32 sub_0806D6B4(u8 *move) {
    s32 dxAbs;
    s32 steps;
    u8 *mapBase;
    s32 x;
    s32 y;
    s32 i;

    dxAbs = *(s32 *)(move + 8);
    if (dxAbs < 0)
        dxAbs = -dxAbs;
    steps = (dxAbs + 0xFFFF) >> 16;

    {
        u32 base = (u32)gMainWorkspace;
        u32 off = 0x18A8;
        mapBase = gTilemapPages + (*(u8 *)(base + off) << 6);
    }

    x = *(s32 *)(move + 0) + *(s32 *)(move + 8);
    *(s32 *)(move + 0) = x;

    if (x < 0)
        return 0;
    if (x >= (*(s16 *)(mapBase + 0x10) << 21))
        return 0;
    y = *(s32 *)(move + 4);
    if (y < 0)
        return 0;
    if (y >= (*(s16 *)(mapBase + 0x12) << 21))
        return 0;

    if (getMapTileAttribute(mapBase, x, y) << 16) {
        i = 0;
        if (i < steps) {
            do {
                y = *(s32 *)(move + 4);
                y += 0xFFFF0000;
                *(s32 *)(move + 4) = y;
                if ((getMapTileAttribute(mapBase, *(s32 *)(move + 0), y) << 16) == 0)
                    return 0;
                i++;
            } while (i < steps);
        }
        return 1;
    } else {
        i = 0;
        if (i < steps + 1) {
            do {
                if (getMapTileAttribute(mapBase, *(s32 *)(move + 0), *(s32 *)(move + 4) + 0x10000) << 16)
                    return 0;
                *(s32 *)(move + 4) += 0x10000;
                i++;
            } while (i < steps + 1);
        }
        return 2;
    }
}
