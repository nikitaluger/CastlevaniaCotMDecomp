extern u8 gGameStatus[];
extern u8 D_080D9B3C[];

/* Room tile state: mark the flag bit for tile (col,row) as set, but only when
 * that tile has a tile entry (nonzero high nibble) in the room map. */
void sub_08061D30(u32 col, s32 row) {
    u8 *state = gGameStatus;
    u8 *tileMap = D_080D9B3C;
    u8 *flags;
    u8 *tile = tileMap + (col + (row << 6));
    if (tile[0] & 0xF0) {
        u32 bit = 1 << (col & 0x1F);
        u32 idx = ((col >> 5) << 2) + (row << 3);
        flags = state + 0xC0;
        *(u32 *)(flags + idx) |= bit;
    }
}
