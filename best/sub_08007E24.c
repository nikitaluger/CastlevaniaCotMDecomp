void sub_08007E24(s32 arg0) {
    u32 t = (u32)arg0 << 16;
    u32 idx = t >> 21;
    u32 bit = (t & 0x1F0000) >> 16;
    u32 mask = 1 << bit;
    u32 *base = (u32 *)0x02025368;
    base += 3;
    base[idx] |= mask;
}
