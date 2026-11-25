s32 sub_08007EA8(u16 arg0) {
    u32 *base = (u32 *)0x02025368;
    u32 t = (u32)arg0 << 16;
    u32 idx = t >> 21;
    u32 bit = (t & (0xF8 << 13)) >> 16;
    u32 mask = 1 << bit;
    u32 off = idx << 2;
    u32 *p = (u32 *)((u8 *)(base + 3) + off);
    return *p & mask;
}
