extern u8 D_02021E90[];

void sub_080011D4(void) {
    u32 *base = (u32 *)D_02021E90;
    u32 *a = (u32 *)((u8 *)base + 0x118);
    u32 *p;
    *(u32 *)((u8 *)base + 0x11C) = 0;
    *a = 0;
    p = (u32 *)((u8 *)base + 0x18);
    if (p < a) {
        do {
            *p = 0;
            p = (u32 *)((u8 *)p + 8);
        } while (p < a);
    }
}
