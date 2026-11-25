void sub_08007E50(s32 arg0) {
    u32 t, idx, bits, bit, mask;
    u32 *base;
    t = (u32)arg0 << 16;
    idx = t >> 21;
    bits = 0x1F0000;
    bits &= t;
    bit = bits >> 16;
    mask = 1 << bit;
    base = (u32 *)0x02025368;
    base += 3;
    base[idx] &= ~mask;
}
