extern s32 createChildObject(void *, s32);
extern s32 sub_08061C9C(u32, s32);
extern u8 gGameStatus[];
extern u8 D_02027A00[];
extern u8 D_080D9B3C[];
extern u8 D_080DABDC[];
extern u32 gMapTileRows[];

/* Copy the two signed map-cell offsets of the current metatile set (selected
 * by gGameStatus[0x94], gGameStatus[0x95]) into the OAM buffer's bytes 0x12 and
 * 0x13, adding the high byte of arg1/arg2 to them. */
void sub_08061B4C(void *arg0, s32 arg1, s32 arg2) {
    u8 *base = gGameStatus;
    u32 *table = gMapTileRows;
    u8 *out;
    u8 *p;
    u32 idx = base[0x94] * 4;
    p = (u8 *)(table[idx] + base[0x95] * 2);
    out = D_02027A00;
    out[0x12] = (s8)((arg1 >> 24) + p[0]);
    out[0x13] = (s8)((arg2 >> 24) + p[1]);
    createChildObject(arg0, 0x12);
}

/* Is tile (col,row) solid? The tile attribute byte in D_080D9B3C (64 cells
 * per row) must be non-zero and the collision bitset bit (col&31 of word
 * (col>>5)*4 + row) must be set. */
s32 sub_08061C9C(u32 arg0, s32 arg1) {
    u8 *base = gGameStatus;
    u8 *tblbase = D_080D9B3C;
    u8 *tbl = tblbase + (arg0 + (arg1 << 6));
    if ((tbl[0] & 0xF0) == 0)
        return 0;
    {
        u32 bit = 1 << (arg0 & 0x1F);
        u32 idx = ((arg0 >> 5) << 2) + (arg1 << 3);
        u32 *bits = (u32 *)((base + 0xC0) + idx);
        if ((*bits & bit) != 0)
            return 1;
    }
    return 0;
}

/* Classify tile (col,row) for movement: 2 when it is solid (see
 * sub_08061C9C), 1 when the alternate attribute map D_080DABDC is active and
 * marks it, 0 when the tile may be walked on. */
s32 sub_08061CE8(u32 arg0, s32 arg1) {
    u8 *base = gGameStatus;
    if (sub_08061C9C(arg0, arg1) != 0)
        return 2;
    if (*(u8 *)(base + 0x2C0) != 0) {
        u8 *tblbase = D_080DABDC;
        u8 *tbl = tblbase + (arg0 + (arg1 << 6));
        if (tbl[0] & 0xF0)
            return 1;
    }
    return 0;
}

/* Mark tile (col,row) solid: set its bit in the collision bitset when its
 * attribute byte in D_080D9B3C is non-zero. */
void sub_08061D30(u32 arg0, s32 arg1) {
    u8 *base = gGameStatus;
    u8 *tblbase = D_080D9B3C;
    u8 *tbl = tblbase + (arg0 + (arg1 << 6));
    if (tbl[0] & 0xF0) {
        u32 bit = 1 << (arg0 & 0x1F);
        u32 idx = ((arg0 >> 5) << 2) + (arg1 << 3);
        u32 *bits = (u32 *)((base + 0xC0) + idx);
        *bits |= bit;
    }
}
