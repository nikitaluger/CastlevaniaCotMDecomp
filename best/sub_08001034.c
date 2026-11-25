extern u32 D_02021EA8;

u32 *sub_08001034(void) {
    u8 *base = (u8 *)&D_02021EA8;
    u8 *p = base + 8;
    u8 *end = base + 0x100;

    while (p < end) {
        if (*(u32 *)p == 0) {
            return (u32 *)p;
        }
        p += 8;
    }

    return 0;
}
