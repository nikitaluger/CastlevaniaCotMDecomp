void sub_0801FA30(void *arg0) {
    u8 *base = *(u8 **)((u8 *)arg0 + 0x3C);
    s32 i = 0;
    do {
        u32 *slot = (u32 *)(base + 0x58 + i * 4);
        u32 v = *slot;
        if (v != 0) {
            *(u16 *)(v + 0x5C) |= 2;
            *slot = 0;
        }
        i++;
    } while (i <= 5);
}
