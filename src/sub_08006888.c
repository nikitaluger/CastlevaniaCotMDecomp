extern u8 D_02021E90[];

/* Set a field in each 0x48-byte record of a table in the graphics workspace:
 * for every index in [start,end], write value to the word at
 * D_02021E90 + 0x99C + index*0x48. */
void sub_08006888(s32 start, s32 end, s32 value) {
    s32 i = start;
    if (i > end) return;
    {
        u8 *base = D_02021E90;
        u32 off = 0x99C;
        s32 *p = (s32 *)(i*0x48 + off + base);
        do {
            *p = value;
            p = (s32 *)((u8 *)p + 0x48);
            i++;
        } while (i <= end);
    }
}
