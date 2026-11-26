extern u8 gGameStatus[];
extern u8 D_080D9B3C[];

/* Room tile state: report whether the flag bit for tile (col,row) is set,
 * but only when that tile has a tile entry (nonzero high nibble) in the map. */
s32 sub_08061C9C(u32 col, s32 row) {
    u8 *state = gGameStatus;
    u8 *tileMap = D_080D9B3C;
    u8 *flags;
    u8 *tile = tileMap + (col + (row << 6));
    if ((tile[0] & 0xF0) == 0)
        return 0;
    {
        u32 bit = 1 << (col & 0x1F);
        u32 idx = ((col >> 5) << 2) + (row << 3);
        flags = state + 0xC0;
        if ((*(u32 *)(flags + idx) & bit) != 0)
            return 1;
    }
    return 0;
}
