extern s32 sub_0800583C(s32);
extern void sub_080A5644(s32, s32);
extern u8 D_08101CF4[];

/*
 * Spawns a hit spark at the given position: the spark's offset comes from the
 * per-direction table D_08101CF4 (two 16.16 words per entry), plus a random
 * +-4 px jitter on x.
 */
void sub_080A5670(s32 dir, void *pos) {
    s32 jitter;
    u8 *table, *tableY;
    s32 off;
    s32 x, y;
    jitter = sub_0800583C(0x80 << 11);
    table = (u8 *)D_08101CF4;
    off = dir << 3;
    x = *(s32 *)((u8 *)pos + 8) + *(s32 *)(off + table) + jitter;
    tableY = table + 4;
    y = *(s32 *)((u8 *)pos + 0xC) + *(s32 *)(off + tableY);
    sub_080A5644(x, y);
}
