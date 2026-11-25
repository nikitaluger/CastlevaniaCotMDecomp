void sub_0801BBB4(void *arg0) {
    u8 *base = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 **p = (u8 **)(base + 0x80);
    s32 i = 9;
    do {
        u8 *v = *p;
        if (v != NULL) {
            u16 *h = (u16 *)(v + 0x64);
            *h = *h | 1;
            *p = NULL;
        }
        p++;
        i--;
    } while (i >= 0);
}
